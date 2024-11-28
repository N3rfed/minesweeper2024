#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include "minesweeper.h"
#include <SFML/Graphics.hpp>

int main() {
    // Reading config.cfg
    std::ifstream configFile("config.cfg");
    std::ifstream fontFile("font.ttf");
    if (!configFile.is_open() || !fontFile.is_open()) {
        std::cerr << "Error opening file(s)" << std::endl;
    }
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(configFile, line)) {
        lines.push_back(line);
        // std::cout << line << std::endl;
    }
    int columns = stoi(lines.at(0));
    int rows = stoi(lines.at(1));
    int mine_count = stoi(lines.at(2));
    int width = columns * 32;
    int height = (rows * 32) + 100;

    runWelcomeScreen(columns, rows, width, height, mine_count);

    return 0;
}