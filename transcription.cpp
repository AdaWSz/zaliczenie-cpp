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
    string holder;
    char* iterator;
    Sequence transc("",3);
    switch (input_sequence.type)
    {
        case 1:
            holder = ReverseString(input_sequence.seq);
            for (char c: holder)
            {
                transc.seq += comp[static_cast<unsigned char>(c)];
            }
            break;
        case 2:
            holder = input_sequence.seq;
            iterator = holder.data();
            while (*iterator != string::npos)
            {
                if (*iterator == 'T')
                {
                    *iterator = 'U';
                }
            }
            transc.seq = holder;
            break;
        case 3:
            transc.seq = input_sequence.seq;
    }
    return transc;
}
