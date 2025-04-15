#ifndef IO_HPP
#define IO_HPP

#include "train.hpp"
#include <vector>

std::vector<Train> LoadAll();
void WriteAll(std::vector<Train> vec = Train::Table);

#endif
