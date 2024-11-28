//
// Created by jaden on 11/18/2024.
//

#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <algorithm>
using namespace std;
void setText(sf::Text &text, float x, float y);
void runWelcomeScreen(int& columns, int& rows, int& width, int& height, int& mine_count);
void runGameScreen(int& columns, int& rows, int& width, int& height, int& mine_count);

class Button {
private:
    sf::Sprite sprite;
    int width;
    int height;
    float xPosition;
    float yPosition;
public:
    Button(sf::Sprite sprite, int width, int height, float xPosition, float yPosition) : sprite(sprite), width(width), height(height), xPosition(xPosition), yPosition(yPosition) {

    };

#endif //MINESWEEPER_H


