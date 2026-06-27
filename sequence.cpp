#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
#include "sequence.h"
using namespace std;

//Wykorzystano unordered set ze względu na wydajność.
static const unordered_set<char> possible_nucl = {'A','T','G','C','U'/*,'R','Y','S','W','K','M','B','D','H','V'*/,'N'}; //Zbyt dużo problemów z kodami niejednoznaczności.

/*
 * Template = 1,
 * Coding = 2,
 * Mrna = 3
*/

Sequence::Sequence(const string& input, Type t)
    : seq(input), type(t) {};

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


/*
class Sequence {
public:
    string seq;

    enum Type { //Tworzymy typ enum - coś jak klasa.
        Template = 1,
        Coding = 2,
        Mrna = 3
    };
    Type type;
    Sequence(const string& input, Type t) :seq(input), type(t) {};
        //Constructor - pozwala od razu przypisać wartość sekwencji.
        //Inputowy type kopiujemy, robimy go constant i zapisujemy w publicznym variable.
        //Possible types: '1' - template, '2' - coding, '3' - mrna

    void Format()
    {

        for (char& c: seq)
        {
            c = toupper(static_cast<unsigned char>(c)); // https://www.digitalocean.com/community/tutorials/string-uppercase-lowercase-c-plus-plus
            if (possible_nucl.find(c) == possible_nucl.end()) //Jeżeli nie znajdzie, iteruje do końca i zwraca koniec.
                c = 'N';
        }
    }
    string Transcribe()
    {
        switch (type)
    }

};
*/
