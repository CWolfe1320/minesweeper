#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <sstream>
#include <vector>
#include "tile.h"
#include "Board.h"
#include <random>
#include <ctime>
using namespace std;


class Random
{

public:

	static int Number(int min, int max);

private:
	static std::mt19937 random;


};

