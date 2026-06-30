#include <iostream>
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include "sequence.h"
#include "translation.h"

using namespace std;



static inline uint8_t nuc(char c) {  //Funkcja dekodująca kodon - cz. 1
    switch (c) {
        case 'A': return 1;             // 0001 W 4 bitach zapisujemy każdy nukleotyd
        case 'C': return 2;             // 0010 używamy unsigned int 8-bitowego, aby poprawnie
        case 'G': return 4;             // 0100 działały operacje bitwise OR (nie było ujemnych)
        case 'U': return 8;             // 1000 i bez paddingu (też pod bitwise)
        case 'R': return 1 | 4;         // 0101
        case 'Y': return 2 | 8;         // 1010 Robimy bitmasking - łączymy w 4 bitach możliwość
        case 'S': return 2 | 4;         // 0110 występowania wszystkich nukelotydów.
        case 'W': return 1 | 8;         // 1001 Wychodzi kompaktowo.
        case 'K': return 4 | 8;         // 1100
        case 'M': return 1 | 2;         // 0011 8 bitów, bo potem robimy shift i łączymy
        case 'B': return 2 | 4 | 8;     // 1110 3 nukleotydy w kodon
        case 'D': return 1 | 4 | 8;     // 1101 żeby było np. 0100|0010|1100
        case 'H': return 1 | 2 | 8;     // 1011 i na podstawie tego możemy dalej działać.
        case 'V': return 1 | 2 | 4;     // 0111
        case 'N': return 1 | 2 | 4 | 8; // 1111
        default:  return 0;             // 0000
    }
}
/*
static inline uint16_t cid(char codon[3]) {
    uint16_t m0 = nuc(codon[0]), m1 = nuc(codon[1]), m2 = nuc(codon[2]);
    return (uint16_t)(m0 | m1 << 4 | m2 << 16); //Shifting bitów tak, aby powstało coś w stylu 0000|0100|0010|1100
}
*/

static inline array<uint8_t,3> cid(array<char,3> codon) //Codon ID
{
    return {nuc(codon[0]),nuc(codon[1]),nuc(codon[2])}; //Ułatwienie - zwraca w arrayu (nie uint16_t)
}

//Array z zakodowanymi kodonami.
// A - 0, C - 1, G - 2, U - 3
// 16x + 4y + z
static const std::array<char, 64> codon_table = {
    // AAA  AAC  AAG  AAU  ACA  ACC  ACG  ACU
       'K', 'N', 'K', 'N', 'T', 'T', 'T', 'T',
    // AGA  AGC  AGG  AGU  AUA  AUC  AUG  AUU
       'R', 'S', 'R', 'S', 'I', 'I', 'M', 'I',
    // CAA  CAC  CAG  CAU  CCA  CCC  CCG  CCU
       'Q', 'H', 'Q', 'H', 'P', 'P', 'P', 'P',
    // CGA  CGC  CGG  CGU  CUA  CUC  CUG  CUU
       'R', 'R', 'R', 'R', 'L', 'L', 'L', 'L',
    // GAA  GAC  GAG  GAU  GCA  GCC  GCG  GCU
       'E', 'D', 'E', 'D', 'A', 'A', 'A', 'A',
    // GGA  GGC  GGG  GGU  GUA  GUC  GUG  GUU
       'G', 'G', 'G', 'G', 'V', 'V', 'V', 'V',
    // UAA  UAC  UAG  UAU  UCA  UCC  UCG  UCU
       '*', 'Y', '*', 'Y', 'S', 'S', 'S', 'S',
    // UGA  UGC  UGG  UGU  UUA  UUC  UUG  UUU
       '*', 'C', 'W', 'C', 'L', 'F', 'L', 'F'
};


// Rozszerzanie ambiguity przez operacje bitwise AND.
static vector<int> expandAmbiguity(uint8_t mask) {
    // bity: A=0001, C=0010, G=0100, U=1000
    std::vector<int> bases; // indeksy: A=0, C=1, G=2, U=3
    if (mask & 0b0001) bases.push_back(0); // A
    if (mask & 0b0010) bases.push_back(1); // C
    if (mask & 0b0100) bases.push_back(2); // G
    if (mask & 0b1000) bases.push_back(3); // U
    return bases;
}


char GetCodon(array<char,3> codon) {
    array<uint8_t,3> id = cid(codon); //Dla podanego kodonu każdą pozycję "szyfrujemy"

    vector<int> v1 = expandAmbiguity(id[0]); //Wektory, bo nie wiemy ile może być możliwych nt
    vector<int> v2 = expandAmbiguity(id[1]);
    vector<int> v3 = expandAmbiguity(id[2]);

    if (v1.empty() || v2.empty() || v3.empty()) return '?'; //Jak coś po drodze jest nie tak to zwracamy ?

    char first = '\0';
    bool first_set = false;

    for (int x : v1)
        for (int y : v2)
            for (int z : v3) {
                char aa = codon_table[16*x + 4*y + z];
                if (!first_set) {
                    first = aa;
                    first_set = true;
                } else if (aa != first) {
                    return 'X';
                }
            }

    if (first_set)
        return first;
    else
        return '?'; //? oznacza błąd - ułatwienie w debugowaniu.
}

vector<AASeq> Translate(Sequence mrna)
{
    string proteinseq = "";
    array<char,3> codon;
    array<char,3> start = {'A','U','G'};
    char aa;
    bool is_translating = false;
    vector<AASeq> proteins;
    for (int n=0; n < 3; n++) // 3 ramki odczytu
    {
        for (int i=n; i < mrna.seq.size(); i=i+3) // zaczynamy w każdej i skaczemy po 3
        {
            if(i+1 < mrna.seq.size() && i+2 < mrna.seq.size()) //out-of-bounds check
            {
                codon[0] = mrna.seq[i]; codon[1] = mrna.seq[i+1]; codon[2] = mrna.seq[i+2]; //tworzymy kodon
                if (!is_translating)
                {
                    if (codon == start)
                    {
                        is_translating = true;
                        aa = GetCodon(codon);
                        proteinseq = proteinseq + aa;
                    }
                }
                else //jeśli już translacja się zaczęła
                {
                    aa = GetCodon(codon);
                    if (aa == '*') // kodon STOP
                    {
                        is_translating = false;
                        AASeq protein(proteinseq,n);
                        protein.Format();
                        proteins.push_back(protein);
                        proteinseq = "";
                    }
                    else
                    {
                        proteinseq = proteinseq + aa;
                    }
                }
            }
        }
        if (!proteinseq.empty())
        {
            proteinseq = proteinseq + '!'; //! oznacza, że białko nigdy się nie skończyło.
            AASeq protein(proteinseq,n);
            protein.Format();
            proteins.push_back(protein);
        }
    proteinseq = ""; //just in case na samym końcu
    is_translating = false;
    }
    return proteins;
}
