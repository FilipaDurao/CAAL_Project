#include <vector>
#include <queue>
#include <algorithm>
#include <list>
#include <limits>
#include <cfloat>
#include <cmath>
#include <queue>
#include <random>
#include <time.h>
#include <chrono>
#include <iostream>

#include "../stringSearch.h"

using namespace std;

/**
 * @brief A function to randomly generate alphanumeric strings
 * Source: https://stackoverflow.com/a/440240
 * @param length The lenght of the generated string
 * @return std::string 
 */
std::string random_string(size_t length);

/**
 * @brief 
 * 
 */
void compareAlgorithmsIncrementPattern();
void compareAlgorithmsIncrementText();
void compareAlgorithmsIncrementBoth();
void compareAlgorithmsKMP() ;