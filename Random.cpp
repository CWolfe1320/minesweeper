#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <sstream>
#include <vector>
#include "board.h"
#include "tile.h"
#include "Random.h"
#include <ctime>
using namespace std;

std::mt19937 Random::random(time(0));

int Random::Number(int min, int max) {

	std::uniform_int_distribution<int> dist(min, max);

	return dist(random);
}