#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>
using namespace std;

//Wykorzystano unordered set ze względu na wydajność.
static const unordered_set<char> possible_nucl = {'A','T','G','C','U','R','Y','S','W','K','M','B','D','H','V'};

class Sequence {
public:
    string seq;

    Sequence(const string& input) //Constructor - pozwala od razu przypisać wartość sekwencji.
    {
        seq = input;
    }

    void format()
    {

        for (char& c: seq)
        {
            c = toupper(static_cast<unsigned char>(c)); // https://www.digitalocean.com/community/tutorials/string-uppercase-lowercase-c-plus-plus
            if (possible_nucl.find(c) == possible_nucl.end()) //Jeżeli nie znajdzie, iteruje do końca i zwraca koniec.
                c = 'N';
        }
    }
};
