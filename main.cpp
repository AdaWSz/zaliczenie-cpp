#include <iostream>
#include <string>
#include "transcription.h"
#include "loader.h"
#include "translation.h"
#include "sequence.h"


using namespace std;

int main(int argc, char **argv) {
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
    return 0;
}

/*
 * 1 metoda - 3 przejścia po nici, translacja as-you-go
 * Złożoność czasowa O(3n/3)
 * 2 metoda - Jednokrotne przejście po nici, zaznaczenie wszystkich kodonów AUG, powrót do każdego i translacja aż do kodonu STOP.
 * Złożoność czasowa O(n + (p + q + r + s + ...)/3)
 * Metoda 1 jest szybsza, ale co jeśli w trakcie pojawi się jeszcze jeden AUG?
 */
