#include <iostream>
#include <string>
#include "sequence.h"
#include "loader.h"
#include "translation.h"
#include "transcription.h"

using namespace std;

void PrintHelp()
{
    cout << " Usage: translator-cpp [options] file\n"
    << "Options:\n"
    << "-t - Interpret input as DNA template strand\n"
    << "-c - Interpret input as DNA coding strand\n"
    << "-m - Interpret input as transcribed mRNA.\n"
    << "-d - Override file input, use string instead\n"
    << "At least one of -t/-c/-m MUST be included."
    << "Takes only one file/string."<<endl;
}

int main(int argc, char **argv)
{
    if (argc >= 3)
    {
        int seq_type = 0;
        string seq_string;
        bool read_directly = false;
        bool got_input = false;
        string source;

        for (int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                for (int j = 1; argv[i][j] != '\0'; j++)
                {
                    switch (argv[i][j])
                    {
                        case 't':
                        case 'c':
                        case 'm':
                            if (seq_type != 0)
                            {
                                PrintHelp();
                                return 1;
                            }
                            seq_type = (argv[i][j] == 't') ? 1 :
                            (argv[i][j] == 'c') ? 2 : 3;
                            break;
                        case 'd': read_directly = true; break;
                        case 'h': PrintHelp(); return 0;
                        default: PrintHelp(); return 1;
                    }
                }
            }
            else
            {
                if (got_input)
                {
                    PrintHelp();
                    return 1;
                }
                source = argv[i];
                got_input = true;
            }
        }

        if (!got_input) {
            PrintHelp();
            return 1;
        }

        if (!read_directly)
        {
            seq_string = LoadSequence(source); // Already checks if file exists.
            if (seq_string.empty()) return 1;
        }
        else
        {
            seq_string = source;
            if (seq_string.empty()) return 1;
        }

        Sequence sequence(seq_string,seq_type);
        sequence.Format();
        Sequence transcript = Transcribe(sequence);
        vector<string> proteins = Translate(transcript);

        for(string protein: proteins)
        {
            cout << protein << endl;
        }

    }

    else
    {
        PrintHelp();
        return 1;
    }
    return 0;
}
/*
 * Usage: translator-cpp [options] file
 *
 * Options:
 * -t - Interpret input as DNA template strand
 * -c - Interpret input as DNA coding strand
 * -m - Interpret input as transcribed mRNA.
 * -d - Override file input, use string instead
 */


/*
 * 1 metoda - 3 przejścia po nici, translacja as-you-go
 * Złożoność czasowa O(3n/3)
 * 2 metoda - Jednokrotne przejście po nici, zaznaczenie wszystkich kodonów AUG, powrót do każdego i translacja aż do kodonu STOP.
 * Złożoność czasowa O(n + (p + q + r + s + ...)/3)
 * Metoda 1 jest szybsza, ale co jeśli w trakcie pojawi się jeszcze jeden AUG?
 */

/*
 * TODO:
 * 1. Przygotuj argumenty do podawania przy odpalaniu programu:
 *      a. Definicja typu sekwencji:
 *          I. Sekwencja z nici matrycowej (Sens)
 *          II. Sekwencja z nici komplementarnej do matrycowej (Kodująca - antysens)
 *          III. Sekwencja mRNA
 * 2. Obróbka danych
 *      a. Jeśli nić matrycowa - odwrócenie i transkrypcja
 *      b. Jeśli nić kodująca - zamiana T na U.
 * 3. Translacja
 *      1 metoda - 3 przejścia po nici, translacja as-you-go
 *          Złożoność czasowa O(3n/3)
 *      2 metoda - Jednokrotne przejście po nici, zaznaczenie wszystkich kodonów AUG, powrót do każdego i translacja aż do kodonu STOP.
 *          Złożoność czasowa O(n + (q*k)/3)
 *      Metoda 1 jest szybsza, ale co jeśli w trakcie pojawi się jeszcze jeden AUG?
 *          !!! To zależy, czy chcesz napisać ORF finder, czy translator !!!
 *          Właściwie prosi o translator.
 */
