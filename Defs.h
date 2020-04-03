#ifndef DEF_H
#define DEF_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstring>

typedef std::map<std::string, int> Map;
typedef std::map<std::string, int>::iterator MapIterator;
typedef std::vector<int> Vector;
typedef std::ifstream IFStream;
typedef std::ofstream OFStream;
typedef std::string String;
typedef std::pair<std::string, int> Pair;
typedef std::pair<std::map<std::string, int>::iterator, bool> PairCheck;

auto& Log = std::cout;
auto& Log_E = std::cerr;

enum PrintType {Console, File};

#endif
