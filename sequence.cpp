#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
#include "sequence.h"
using namespace std;

//Wykorzystano unordered set ze względu na wydajność.
static const unordered_set<char> possible_nucl = {'A','T','G','C','U','R','Y','S','W','K','M','B','D','H','V','N'};
static const unordered_set<char> possible_aa = {'A', 'R', 'N', 'D', 'C','E', 'Q', 'G', 'H', 'I','L', 'K', 'M', 'F', 'P','S', 'T', 'W', 'Y', 'V','X'};

/*
 * Template = 1,
 * Coding = 2,
 * Mrna = 3
*/

Sequence::Sequence(const string& input, int t)
    : seq(input), type(t) {}; //szybka definicja co jest czym.

//Format - works DIRECTLY on sequence to remove any disallowed characters.
void Sequence::Format()
{
    for (char& c: seq)
    {
        c = toupper(static_cast<unsigned char>(c)); // https://www.digitalocean.com/community/tutorials/string-uppercase-lowercase-c-plus-plus
        if (possible_nucl.find(c) == possible_nucl.end()) //Jeżeli nie znajdzie, iteruje do końca i zwraca koniec.
            c = 'N';
    }
}

AASeq::AASeq(const string input, int rf)
{
    if(!input.empty())
    {
        if (input.back() == '!') //Inferujemy na podstawie tego, czy w zwróconej sekwencji na końcu pojawia się !
        {
            seq = input.substr(0, input.size() - 1);
            ended = false;
        }
        else
        {
            seq = input;
            ended = true;
        }
    }
    else
    {
        seq = "";
        ended = false;
    }
    reading_frame = rf;
}

void AASeq::Format()
{
    for (char& c: seq)
    {
        c = toupper(static_cast<unsigned char>(c));
        if (possible_aa.find(c) == possible_aa.end())
            c = 'X';
    }
}

/*
 * A=0,  C=1,  D=2,  E=3,  F=4,  G=5,  H=6,
 * I=7,  K=8,  L=9,  M=10, N=11, P=12, Q=13,
 * R=14, S=15, T=16, V=17, W=18, Y=19, X=20
 */

void AASeq::CountAmino()
{
     static constexpr unsigned char map[26] = { // constexpr - da się obliczyć w czasie kompilacji.
                                              0, 20, 1, 2, 3, 4, 5, 6, 7, 20,
                                              8, 9, 10, 11, 20, 12, 13, 14,
                                              15, 16, 20, 17, 18, 20, 19, 20}; //Dla całego alfabetu - 20 to nieprawidłowe znaki
    for (char c: seq)
        counts[map[c-'A']]++; //od c odejmujemy wartość ASCII dla 'A', co daje nam wartość w map[26], którą możemy zwrócić.
}
