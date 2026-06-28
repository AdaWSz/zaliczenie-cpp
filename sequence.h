#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

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
std::string ReverseSeq();
std::string Transcribe();
};

#endif

/*
 * KLASA AASeq
 * Może posiadać wbudowany
 *
 */
