#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <array>
#include <vector>
#include <string>
#include "sequence.h"

char GetCodon(std::array<char,3> codon);
std::vector<AASeq> Translate(Sequence mrna);

#endif

/* TRANSLACJA
 * Tutaj powinno znaleźć się:
 * 1. Funkcja dokonująca translacji.
 *
 * Jak zrobić translację?
 * 1. Wyznaczyć 3 ramki odczytu (i, i+1, i+2)
 * 2. Podzielić sekwencję na 3-znakowe fragmenty (tokenizacja)
 * 3. Zamienić kodony na odpowiadające im aminokwasy
 *      Ponieważ nie ma w C++ie prostego sposobu na zrobienie tego jak dictionary,
 *      zastosujemy array, w którym każdy kodon będzie odpowiednio zakodowany.
 *      A = 0, C = 1, G = 2, T = 3
 *      przy czym jeśli to ma mieć sens to:
 *
 *      Kodon:   A   A  A
 *      Transl: x16 x4 x1
 *
 *      więc: AAA = 0, AAG = 2, ACA = 4, ATA = 12, CAA = 16
 *
 *
 *      Jak to zrobić?
 *      Może tak:
 *      1. Enum dla każdego nukleotydu
 *      2. Podział kodonu na 3
 *      3. Wpakowanie 3 wartości do funkcji zwracającej ID
 *      4. Podanie ID do array zwracającego aminokwas
 *      5. Appending sekwencji aminokwasowej.
 *
 *
 */
