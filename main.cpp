#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
// sf::CircleShape shape(100.f);
// shape.setFillColor(sf::Color::Red);
// window.draw(shape);


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
        std::cout << line << std::endl;
    }
    int mine_count = stoi(lines.at(2));
    int width = stoi(lines.at(0)) * 32;
    int height = (stoi(lines.at(1)) * 32)+100;

    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper");
    sf::Color welcomeBackground(0, 0, 255);
    sf::Font font;
    font.loadFromFile("font.ttf");
    while(welcomeWindow.isOpen()) {
        sf::Event event;
        while(welcomeWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
        }

        welcomeWindow.clear(welcomeBackground);
        sf::Text welcomeText;
        welcomeText.setString("WELCOME TO MINESWEEPER!");
        welcomeText.setFont(font);
        welcomeText.setPosition(width / 2, (height / 2) - 150);
        welcomeText.setCharacterSize(24);
        welcomeText.setFillColor(sf::Color(255,255,255));
        welcomeWindow.draw(welcomeText);
        welcomeWindow.display();
    }
    return 0;
}