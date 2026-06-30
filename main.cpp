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
        vector<AASeq> proteins = Translate(transcript);

        cout << "Peptides found: " << proteins.size() << "\n=====\n";

        static constexpr char aanames[] = {
            'A','C','D','E','F','G','H','I','K','L','M',
            'N','P','Q','R','S','T','V','W','Y','X'
        };

        for(AASeq protein: proteins)
        {
            protein.CountAmino();

            cout << "Found peptide:" << endl;
            cout << "Reading frame (n nucleotides from start of sequence): " << protein.reading_frame << endl;
            cout << "Ended correctly (STOP sequence found): ";

            if(protein.ended)
                cout << "Yes\n";
            else
                cout << "No\n";
            cout << "Sequence length: " << protein.seq.length() << endl;
            cout << "Amino acid composition: " << endl;
            for(int i = 0; i < 21; i++)
            {
                cout << aanames[i] << " : "<< protein.counts[i] << "\t";
                if(i%5 == 0)
                {
                    cout << endl;
                }
            }
            cout << "Sequence: \n" << protein.seq << endl;
            cout << "----------" << endl;
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
