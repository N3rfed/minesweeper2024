#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
// sf::CircleShape shape(100.f);
// shape.setFillColor(sf::Color::Red);
// window.draw(shape);
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}


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
    int mine_count = stoi(lines.at(2));
    int width = stoi(lines.at(0)) * 32;
    int height = (stoi(lines.at(1)) * 32) + 100;

    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper");
    sf::Color welcomeBackground(0, 0, 255);
    sf::Font font;
    font.loadFromFile("font.ttf");
    std::string nameInput;
    while(welcomeWindow.isOpen()) {
        sf::Event event;
        while(welcomeWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
        }

        welcomeWindow.clear(welcomeBackground);
        sf::Text welcomeText;
        sf::Text instructionText;
        sf::Text usernameText;
        sf::Event textEvent;

        welcomeText.setString("WELCOME TO MINESWEEPER!");
        instructionText.setString("Enter your name:");
        usernameText.setString("|");

        welcomeText.setFont(font);
        instructionText.setFont(font);
        usernameText.setFont(font);

        welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
        instructionText.setStyle(sf::Text::Bold);
        usernameText.setStyle(sf::Text::Bold);

        welcomeText.setCharacterSize(24);
        instructionText.setCharacterSize(20);
        usernameText.setCharacterSize(18);

        welcomeText.setFillColor(sf::Color(255,255,255));
        instructionText.setFillColor(sf::Color(255,255,255));
        usernameText.setFillColor(sf::Color(255,255,0));


        setText(welcomeText, (width / 2), float((height / 2) - 150));
        setText(instructionText, (width / 2), float((height / 2) - 75));
        // setText(usernameText, (width / 2), float((height / 2) - 45));

        while(welcomeWindow.pollEvent(textEvent)) {
            if(textEvent.type == sf::Event::Closed) {
                welcomeWindow.close();
            }

            if(textEvent.type == sf::Event::TextEntered) {
                if(textEvent.text.unicode < 128) {
                    if(textEvent.text.unicode == 8 && nameInput.size() != 0) {
                        nameInput.pop_back();
                    }
                    else if(textEvent.text.unicode == '\r' && nameInput.size() > 0) {
                        // close welcome window, open game window
                        welcomeWindow.close();
                        break;
                    }
                    else {
                        if(std::isalpha(textEvent.text.unicode) && nameInput.size() < 10) {
                            if(nameInput.size() == 0) {
                                nameInput += std::toupper(static_cast<char>(textEvent.text.unicode));
                            }
                            else if(nameInput.size() > 0) {
                                nameInput += std::tolower(static_cast<char>(textEvent.text.unicode));
                            }
                            else {
                                nameInput += static_cast<char>(textEvent.text.unicode);
                                std::cout << nameInput << " " << nameInput.size() << std::endl;
                            }
                        }
                    }
                }

            }
        }
        usernameText.setString(nameInput + '|');
        setText(usernameText, (width / 2), float((height / 2) - 45));



        // welcomeText.setString()
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(instructionText);
        welcomeWindow.draw(usernameText);
        welcomeWindow.display();


    }
    return 0;
}