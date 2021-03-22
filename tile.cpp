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
using namespace std;



Tile::Tile(int _x, int _y) {

	x = _x;

	y = _y;

}

int Tile::CheckTile() {
	return tileType;
}

void Tile::SetTile(int _tileType) {
	//0. Hidden | 1. Revealed
	tileType = _tileType;


}
int Tile::CheckBomb() {
	return bomb;
}
void Tile::SetBomb(int _bomb) {
	//0. No Bomb | 1. Bomb
	bomb = _bomb;
}

void Tile::SetNeighbors(int num, bool bomb) {


	switch (num){
	
	case 1:
		neiOne = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 2:
		neiTwo = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 3:
		neiThree = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 4:
		neiFour = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 5:
		neiFive = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 6:
		neiSix = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 7:
		neiSeven = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	case 8:
		neiEight = bomb;
		if (bomb) {
			++numBombNeighbors;
		}
		break;
	
	
	}


}

int Tile::CheckNeighbors() {



	return numBombNeighbors;
}

int Tile::CheckDebug() {
	return debug;
}

void Tile::SetDebug() {
	debug = debug + 1;
}


void Tile::SetFlag(int _flagType) {
	flag = _flagType;
}
int Tile::CheckFlag() {
	return flag;
}

void Tile::SetPrevFlag(int _flagType) {
	prevFlag = _flagType;
}
int Tile::CheckPrevFlag() {
	return prevFlag;
}

void Tile::SetExplode() {
	explode = 1;
}

int Tile::CheckExplode() {
	return explode;
}