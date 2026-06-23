#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

class Sequence {
private:
    const std::string possible_nucl;

public:
    std::string seq;

    Sequence(const std::string& input);
    void format();
};

#endif
