//
// Created by jaden on 11/18/2024.
//
#include "minesweeper.h"
void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void runWelcomeScreen(int& columns, int& rows, int& width, int& height, int& mine_count) {
    // Welcome Window

    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper");
    sf::Color welcomeBackground(0, 0, 255);
    sf::Font font;
    font.loadFromFile("font.ttf");
    std::string nameInput;
    while(welcomeWindow.isOpen()) {


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
                        runGameScreen(columns, rows, width, height, mine_count);

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
}

void runGameScreen(int& columns, int& rows, int& width, int& height, int& mine_count) {
    // Game Window
    sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper");
    sf::Color gameBackground(255, 255, 255);

    // Game Textures
    sf::Texture gameTileTexture;
    sf::Texture happyFaceTexture;
    sf::Texture debugTexture;
    sf::Texture pauseTexture;
    sf::Texture leaderboardTexture;

    if(!gameTileTexture.loadFromFile("images\\tile_hidden.png") ||
        !happyFaceTexture.loadFromFile("images\\face_happy.png") ||
        !debugTexture.loadFromFile("images\\debug.png") ||
        !pauseTexture.loadFromFile("images\\pause.png") ||
        !leaderboardTexture.loadFromFile("images\\leaderboard.png")) {
        std::cerr << "ERROR LOADING TILE_FILE" << std::endl;
    }
    else {
        std::cout << "success" << std::endl;
    }
    sf::Sprite gameTileSprite;
    sf::Sprite happyFaceSprite;
    sf::Sprite debugSprite;
    sf::Sprite pauseSprite;
    sf::Sprite leaderboardSprite;

    gameTileSprite.setTexture(gameTileTexture);
    happyFaceSprite.setTexture(happyFaceTexture);
    happyFaceSprite.setPosition((columns / 2.0 * 32) - 32, 32 * (rows + 0.5));
    debugSprite.setTexture(debugTexture);
    debugSprite.setPosition(columns * 32 - 304, 32 * (rows + 0.5));
    pauseSprite.setTexture(pauseTexture);
    pauseSprite.setPosition(columns * 32 - 240, 32 * (rows + 0.5));
    leaderboardSprite.setTexture(leaderboardTexture);
    leaderboardSprite.setPosition(columns * 32 - 176, 32 * (rows + 0.5));


    gameWindow.clear(gameBackground);

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < columns; col++) {
            gameTileSprite.setPosition(col * 32, row * 32);
            gameWindow.draw(gameTileSprite);
        }
    }

    gameWindow.draw(happyFaceSprite);
    gameWindow.draw(debugSprite);
    gameWindow.draw(pauseSprite);
    gameWindow.draw(leaderboardSprite);


    gameWindow.display();


    while(gameWindow.isOpen()) {
        sf::Event gameEvent;
        while(gameWindow.pollEvent(gameEvent)) {
            if(gameEvent.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }
    }
}
