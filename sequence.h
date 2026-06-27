#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

class Sequence {

public:
    std::string seq;
    enum Type {
        Template = 1,
        Coding = 2,
        Mrna = 3
    };
    Type type;
Sequence(const std::string& input, Type t);
void Format();
std::string ReverseSeq();
std::string Transcribe();
};

class AASeq {
public:
    std::string seq;

    std::
};

#endif

/*
 * KLASA AASeq
 * Może posiadać wbudowany
 *
 */
