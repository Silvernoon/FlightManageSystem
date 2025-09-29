#pragma once

#include "Flight.hpp"
#include <vector>

void LoadAll();
void WriteAll(const std::vector<Flight> vec = Flight::table());
