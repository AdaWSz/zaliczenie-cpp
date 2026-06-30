#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <array>

class Sequence {

public:
    std::string seq; //sama sekwencja
    int type; //typ sekwencji
/*    enum Type {
        Template = 1,
        Coding = 2,
        Mrna = 3
    };
    Type type; */
Sequence(const std::string& input, int t); //builder - wymaga inputu przy tworzeniu obiektu.
void Format();
};

class AASeq {

public:
    std::string seq;
    int reading_frame; //z której ramki odczytu? 0, +1, +2 od początku podanej.
    bool ended; // Czy poprawnie zakończona? Interpretowane na podstawie "!" na końcu.
    std::array<int,26> counts = {}; //nie chce mi się robić wielkiego bloku switchów, wykorzystam tabelę znaków ASCII.

AASeq(const std::string input, int rf);
void Format();
void CountAmino();
};

#endif

/*
 * KLASA AASeq
 * Może posiadać wbudowany licznik aminokwasów
 * Interpretować czy białko ma poprawne zakończenie czy nie
 * Posiadać informację z jakiej ramki odczytu pochodzi.
 */
