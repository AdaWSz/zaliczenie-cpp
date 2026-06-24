#include <iostream>
#include <string>
#include <array>
#include "transcription.h"
#include "sequence.h"

using namespace std;

/* TODO:
 * 1. Funkcja odwracająca DNA
 * 2. Funkcja transkrybująca (wg zasad komplementarności)
 * 3. Funkcja zamienniająca coding strand na mRNA (podmiana T -> U)
 */

static const std::array<char, 256> comp = [] {
    std::array<char, 256> a{}; //funkcja lambda, aby wypełnić wartości.
    a['A'] = 'T'; a['C'] = 'G'; a['G'] = 'C'; a['T'] = 'A';
    a['U'] = 'A'; a['R'] = 'Y'; a['Y'] = 'R'; a['S'] = 'W';
    a['W'] = 'S'; a['K'] = 'M'; a['B'] = 'V'; a['D'] = 'H';
    a['H'] = 'D'; a['V'] = 'B'; a['N'] = 'N';
    return a;
}();

string ReverseString(string input) // Po prostu trawimy input - kopiujemy i zwracamy kopię.
{
    char* s = input.data();
    char* e = input.data() + input.size() - 1;

    while (s < e)
    {
        swap(*s, *e);
        ++s;
        --e;
    }
    return input;
}

//Transcribe - fills the transc string public variable (and returns it if needed)
Sequence Transcribe(Sequence input_sequence)
/*
 * Template = 1,
 * Coding = 2,
 * Mrna = 3
 */
{
    string reverse;
    Sequence transc("",Sequence::Mrna);
    switch (input_sequence.type)
    {
        case 1:
            reverse = ReverseString(input_sequence.seq);
            for (char c: reverse)
            {
                transc.seq += comp[static_cast<unsigned char>(c)];
            }
            break;
        case 2:
            //TODO:
            //For the sake of it, użyj pointerów czy coś.
            //Zamień każde "T" na "A".
            //Może zamień input w array.
        case 3:
            transc.seq = input_sequence.seq;
    }
    return transc;
}

int function(int a)
{
    int b=2*a;
    return b;
}
