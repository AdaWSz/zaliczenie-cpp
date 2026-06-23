#ifndef LOADER_H_
#define LOADER_H_

#include <string>


std::string Lowercase(const std::string& input);
bool BinaryCheck(std::ifstream& file);
std::string LoadSequence(const std::string& filestring);

#endif
