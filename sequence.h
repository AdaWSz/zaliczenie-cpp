#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <array>

class Sequence {

public:
    std::string seq;
    int type;
/*    enum Type {
        Template = 1,
        Coding = 2,
        Mrna = 3
    };
    Type type; */
Sequence(const std::string& input, int t);
void Format();
};

class AASeq {
public:
    std::string seq;
    int reading_frame;
    bool ended;

private:
    std::array<char,20> possible_aa;

};

#endif

/*
 * KLASA AASeq
 * Może posiadać wbudowany licznik aminokwasów
 * Interpretować czy białko ma poprawne zakończenie czy nie
 * Posiadać informację z jakiej ramki odczytu pochodzi.
 */
