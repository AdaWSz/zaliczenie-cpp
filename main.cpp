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
    << "-d - Override file input, use string instead\n" <<endl;
}

int main(int argc, char **argv)
{
    if (argc >= 3)
    {
        int seq_type;
        string path;
        string seq_string;
        bool read_directly = false;
        for(int i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-')
            {
                int len = sizeof(&argv[i])/sizeof(&argv[i][0]);
                for (int j = 1; j < len; j++)
                {
                    switch (argv[i][j])
                    {
                        case 't': seq_type = 1;
                        case 'c': seq_type = 2;
                        case 'm': seq_type = 3;
                        case 'd': read_directly = true; //Figure this out later.
                        default: PrintHelp(); return 0;
                    }
                }
            }
            else
            {
                if (!read_directly)
                {
                    seq_string = LoadSequence(argv[i]);
                    if (seq_string.empty())
                        return 0;
                }
                else
                    seq_string = argv[i];

            }

        }

    }


    else
        PrintHelp();

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
