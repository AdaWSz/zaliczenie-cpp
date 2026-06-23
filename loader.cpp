#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

//ampersand w definicji funkcji oznacza, że używamy zmiennej bezpośrednio zamiast tworzyć kopię.
//Wykorzystujemy const, aby nie zmienić przez przypadek ścieżki czy extension.

string Lowercase(const string& input)
{
    string output = input;
    for (char& c : output)
    {
        c = tolower(c);
    }
    return output;
}

//Czy to jest w ogóle potrzebne?
/*
bool CheckFileExtension(const string& filename, const string& ext)
{
    fs::path filepath(filename);
    return filepath.extension() == ext;
}
*/

//Sprawdzenie czy plik jest binarny przez wyszukanie znaku NULL
//Spadek wydajności dla bardzo dużych plików albo plików tekstowych (bez NUL).
//Mimo to, potrzebne dla walidacji.
bool BinaryCheck(ifstream& file)
{
    if (!file.is_open()) return false;

    char byte;
    while (file.get(byte))
    {
        if (byte == '\0')
        {
            file.seekg(0);
            return true;
        }
    }
    file.clear();
    file.seekg(0);
    return false;
}

//Ładowanie sekwencji - docelowo zwraca całą sekwencję z pliku. Działa tylko dla jednej (może później dodam możliwość operowania na wielu plikach).
string LoadSequence(const string& filestring)
{
    string seq = ""; // Zmodyfikuj do debugowania jak chcesz.
    string line;
    if (fs::exists(filestring))
    {
        const fs::path filepath(filestring); //zamieniamy podany string na path
        const string extn = Lowercase(filepath.extension().string()); // Ekstrakcja rozszerzenia pliku
        ifstream seqfile(filepath.string()); //otwieramy stream
        if (!seqfile.is_open())
        {
            cerr << "Could not open file: " << filepath.string() << endl;
            return "";
        }
        else if (extn == ".fa" or extn == ".fasta")
        {
            cout << "File is fasta, loading" << endl;
            bool passed_header = false;
            while (getline(seqfile, line))
            {
                if (!line.empty() and line[0] == '>') //wykrywanie headerów
                {
                    if (!passed_header) //Na razie dla ułatwienia bierze tylko pierwszą sekwencję z pliku multi-FASTA.
                        passed_header = true;
                    else
                        break;
                }
                else
                {
                    seq = seq + line;
                }
            }
            cout << seq << endl;
        }
        else
        {
            bool is_binary = BinaryCheck(seqfile);
            if (!is_binary)
            {
                while (getline(seqfile, line))
                {
                    seq = seq + line;
                }
            }
            else
            {
                cerr << "File is binary!" << endl;
                return "";
            }

        }
    }
    else
    {
        cerr << "File does not exist!" << endl;
        return "";
    }
    return seq;
}
