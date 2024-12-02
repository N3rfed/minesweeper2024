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
class Board;

void setText(sf::Text &text, float x, float y);
void runWelcomeScreen(int& columns, int& rows, int& width, int& height, int& mine_count);
void runGameScreen(int& columns, int& rows, int& width, int& height, int& mine_count);
void leaderboardScreen(int& columns, int& rows, Board* board);
void renderWithLayers(const sf::Sprite& background, const sf::Sprite& foreground);

class Button {
private:
    sf::Sprite sprite;
    int width;
    int height;
    float xPosition;
    float yPosition;
public:
    Button(){}
    Button(sf::Sprite sprite, int width, int height, float xPosition, float yPosition) : sprite(sprite), width(width), height(height), xPosition(xPosition), yPosition(yPosition) {}
    void setBtnPosition(float xPosition, float yPosition);
    void setBtnTexture(sf::Texture &texture);
    bool isBtnPressed(float xPosition, float yPosition);
    sf::Sprite& getSprite();
};

struct Player {
    std::string time;
    std::string player;

    Player(){}
    Player(std::string time, std::string player) : time(time), player(player) {}
    int timeToInt(std::string time);
    bool operator<(const Player &other) const;
    bool operator>(const Player &other) const;
};

class Leaderboard {
private:
    int width;
    int height;
    std::vector<Player> players;
    Board* currentGameBoard;
public:
    Leaderboard(){}
    Leaderboard(Board* currentGameBoard, int width, int height) : width(width), height(height), currentGameBoard(currentGameBoard) {}
    void addWinner(int time, std::string name);
};

class Number {
private:
    int number;
    std::vector<sf::Sprite> numberSprites;
public:
    Number(){}
    Number(int number) : number(number) {}
    void getSprite(std::vector<sf::Sprite> numberSprites);
    void setNumberPosition(float xPosition, float yPosition);
};

class Timer {
private:
    int min;
    int sec;
    std::vector <sf::Sprite> minSprites;
    std::vector <sf::Sprite> secSprites;
public:
    Timer(){}
    void printTime();
    int getTime();
    void updateTime(int newTime);
    // potentially unfinished
};

class Tile {
private:
    int type;
    bool shown;
    bool flagged;
    bool debug;
    sf::Sprite foregroundSprite;
    sf::Sprite backgroundSprite;
    sf::Texture texture;
    sf::Texture backgroundTexture;
    bool savedShown;
    bool savedFlagged;
    int savedType;
public:
    Tile(){}
    Tile(int type, bool shown, bool flagged) : type(type), shown(false), flagged(flagged) {}
    void setTile(int type);
    void setTexture(sf::Texture &texture);
    void setBackgroundTexture(sf::Texture &texture);
    void setPosition(float xPosition, float yPosition);
    int getTile();
    sf::Sprite& getSprite();
    sf::Sprite& getBackgroundSprite();
    bool isRevealed();
    bool isFlagged();
    void reveal();
    void hide();
    void flag();
    void unflag();
    void resetTile();
    bool isClicked(float xPosition, float yPosition);
    bool isRightClicked(float mouseXPosition, float mouseYPosition);
    const sf::Vector2f getPosition();
    void toggleDebug();
    bool isDebugged();
    void pause();
    void resume();
};

class Board {
private:
    int width;
    int height;
    int mines;
    int tilesRevealed;
    std::vector <std::vector<Tile>> tiles;
public:
    Board(){}
    Board(int width, int height, int mines) : width(width), height(height), mines(mines) {
        tiles.resize(height, std::vector<Tile>(width));
    }
    void fillBoard(int rows, int columns);
    void numberBoard(int rows, int columns);
    void revealBoard(int rows, int columns);
    int revealTile(int rows, int columns);
    void resetBoard(int rows, int columns);
    void endGame(int rows, int columns);
    void printBoard(int rows, int columns);
    Tile& getBoardTile(int rows, int columns);
    void debugBoard(int rows, int columns, int type);
    void gameLoss(int rows, int columns);
    void gameWon(int rows, int columns);
    int getTilesRevealed();
    void pauseBoard(int rows, int columns);
    void resumeBoard(int rows, int columns);
};

#endif //MINESWEEPER_H


