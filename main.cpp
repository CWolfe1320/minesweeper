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
void GetDataFromCFGFile(string filepath, vector<int>& cfg) {
   
    ifstream inFile(filepath);

    if (inFile.is_open()) {

        int numColumns = 0;
        int numRows = 0;
        int windowWidth = 0;
        int windowHeight = 0;
        int tileCount = 0;
        int mineCount = 0;
        inFile >> numColumns;
        inFile >> numRows;
        inFile >> mineCount;
        windowWidth = numColumns * 32;
        windowHeight = (numRows * 32) + 88;
        tileCount = numColumns * numRows;
        cfg.push_back(numColumns);
        cfg.push_back(numRows);
        cfg.push_back(windowWidth);
        cfg.push_back(windowHeight);
        cfg.push_back(tileCount);
        cfg.push_back(mineCount);
    }
}
int main()
{
    vector<int> cfg;
    //0. number of columns | 1. number of rows | 2. window width | 3. window height | 4. tile count | 5. mineCount
    GetDataFromCFGFile("boards/config.cfg", cfg);
    cout << "Program Started :)" << endl;
    Board mineWindow = Board(cfg);
    mineWindow.RenderWindow();
    cout << "Program Ended :(" << endl;
    return 0;
}