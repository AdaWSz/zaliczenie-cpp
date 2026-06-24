#include <iostream>
#include <string>
#include "transcription.h"
#include "sequence.h"

using namespace std;

/* TODO:
 * 1. Funkcja odwracająca DNA
 * 2. Funkcja transkrybująca (wg zasad komplementarności)
 * 3. Funkcja zamienniająca coding strand na mRNA (podmiana T -> U)
 */

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
string Transcribe(Sequence seq)
{
    string transc = "";


}

int function(int a)
{
    int b=2*a;
    return b;
}
