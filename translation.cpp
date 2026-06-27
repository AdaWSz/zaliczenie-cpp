#include <iostream>
#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include "sequence.h"
#include "translation.h"
using namespace std;

/*TODO:
 * 1. Zapisz tablicę nukleotydów
 *      (Tą rozszerzoną o te nukleotydy spoza 5 kanonicznych)
 * 2. Dla kodonów niezdecydowanych - poszukaj jakichś statystyk, matrycy częstości i na jej podstawie to zrób.
 */

/* K - AAA AAG AAR
 * N - AAU AAC AAY
 * I - AUU AUC AUA AUY AUM AUH AUW
 * M - AUG
 * S - AGU AGC AGY
 * L - CUU CUC CUA CUG CUN CUR CUY CUS CUW CUK CUM CUB CUD CUH CUV UUA UUG UUR YUA YUG
 * P - CCU CCC CCA CCG CCN CCR CCY CCS CCW CCK CCM CCB CCD CCH CCV
 * V - GUU GUC GUA GUG GUN GUR GUY GUS GUW GUK GUM GUB GUD GUH GUV
 * H - CAU CAC CAY
 * D - GAU GAC GAY
 * E - GAA GAG GAR
 * F - UUU UUC UUY
 * G - GGU GGC GGA GGG GGY GGR GGS GGW GGK GGM GGB GGD GGH GGV GGN
 * Q - CAA CAG CAR
 * R - CGU CGC CGA CGG CGY CGR CGS CGW CGK CGM CGD CGB CGH CGV CGN AGA AGG AGR
 * T - ACU ACC ACA ACG ACN ACY ACR ACS ACW ACK ACM ACD ACB ACH ACV
 * W - UGG
 * Y - UAU UAC UAY
 * A - GCU GCC GCA GCG GCN GCY GCR GCS GCW GCK GCM GCD GCB GCH GCV
 * C - UGU UGC UGY
 * STOP - UAA UAG UGA UAR URA
 */

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

static inline uint16_t cid(char codon[3]) {
    uint16_t m0 = nuc(codon[0]), m1 = nuc(codon[1]), m2 = nuc(codon[2]);
    return (uint16_t)(m0 | m1 << 4 | m2 << 16); //Shifting bitów tak, aby powstało coś w stylu 0000|0100|0010|1100
}

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

/*
 * Jak przekonwertować 16 (12) bitów na 6?
 *
 * Oto jak:
 *
 * Podzielić 16-bitowy string na 4 równe części.
 *      cid >> 4, cid >> 16 na 2 przednich nt
 *      ostatni otrzymać przez bitwise AND
 *      czyli cid & 15 (0000010000101100 & 0000000000001111 -> 0000000000001100)
 *
 * Odrzucić niepotrzebne, zrobić logarytm o podstawie 2 z reszty.
 * Tak żeby uzyskać pozycję bitu włączonego.
 *      std::bit_width(index) - 1
 *
 *
 *      Jeśli jest więcej niż 1 bit flipnięty w jedym z 4 równych części
 *      Najpierw należy rozbić na części pierwsze - jak są 2 bity pozytywne, zamienić
 *      na dwa 4-bitowe elementy z 1 bitem.
 *
 * Robisz ewaluację tych otrzymanych bitów przez otrzymanie i sprawdzenie każdego w tabeli kodonów.
 *      Ewaluacja na zasadzie 16x + 4y + z, gdzie x, y, z to pozycje bitów z 1.
 *
 * Jeśli wszystkie mapują do tego samego aa - wstawiamy ten aa.
 * Jeśli nie - wstawiamy X.
 *
 */


char GetCodon(char codon[3]) {
    int id = cid(codon);
    if (id < 0)
        return 'X';
    return codon_table[id];
}

vector<string> Translate(Sequence mrna)
{
    string protein = "";
    char codon[3];
    bool is_translating = false;
    vector<string> proteins;
    for (int n=0; n < 3; n++)
    {
        for (int i=n; i < mrna.seq.size(); i=i+3)
        {
            if(i+1 < mrna.seq.size() and i+2 < mrna.seq.size())
            {
                if(cid(codon) == 14 and !is_translating)
                {
                    is_translating = true;
                    protein = protein + GetCodon(codon);
                }
                else if(protein.back() == '*')
                {
                    is_translating = false;
                    proteins.push_back(protein);
                    protein = "";
                }
                else
                    protein = protein + GetCodon(codon);
            }
        }
    }
    return proteins;
}
