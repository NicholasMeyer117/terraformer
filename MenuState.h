#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Game.h"
#include "State.h"
#include "Button.h"
#include "ParticleSystem.h"

class MenuState: public State
{
    public:
    std::vector<Button*> buttonList;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Font spaceFont;
    sf::Text source;
    sf::Text titleText;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        spaceFont.loadFromFile("pirulen.ttf");
        gameFont = game->gameFont;
        
    }
    
    int Run(sf::RenderWindow &app)
    {
        /*titleText.setFont(spaceFont);
        titleText.setString("Terraformer");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/2, screenH/8);
        
        Button *startButton = new Button;
        startButton->createButton(screenW/2, 350, 400, 100, &gameFont, "START", 20); 
        buttonList.push_back(startButton);
        
        Button *settingsButton = new Button;
        settingsButton->createButton(screenW/2, 500, 400, 100, &gameFont, "HOW TO PLAY", 20); 
        buttonList.push_back(settingsButton);
        
        Button *creditsButton = new Button;
        creditsButton->createButton(screenW/2, 650, 400, 100, &gameFont, "CREDITS", 20); 
        buttonList.push_back(creditsButton);
        
        Button *quitButton = new Button;
        quitButton->createButton(screenW/2, 800, 400, 100, &gameFont, "QUIT", 20); 
        buttonList.push_back(quitButton);*/
        cout << to_string(screenW) + "," + to_string(screenH) + "\n";
        Texture t1;
        t1.loadFromFile("images/mainScreen.png");
        Sprite menuScreen(t1);
        menuScreen.setOrigin(screenW/2, screenH/2);
        menuScreen.setPosition(screenW/2, screenH/2);
        menuScreen.setScale(screenW/menuScreen.getLocalBounds().width, screenH/menuScreen.getLocalBounds().height);
        
        titleText.setFont(spaceFont);
        titleText.setString("TERRAFORMER");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::White);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/1.5, screenH/8);
        
        RectangleShape buttonBacker;
        buttonBacker.setSize(sf::Vector2f(400, screenH));
        buttonBacker.setOutlineColor(sf::Color::Black);
        buttonBacker.setFillColor(Color(105,105,105, 100));
        buttonBacker.setOutlineThickness(1);
        buttonBacker.setOrigin(buttonBacker.getSize().x/2, buttonBacker.getSize().y/2);
        buttonBacker.setPosition(screenW/4, screenH/2);
        
        Button *startButton = new Button;
        startButton->createButton(screenW/4, 0 + screenH/6, 300, 75, &gameFont, "START", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(startButton);
        
        Button *settingsButton = new Button;
        settingsButton->createButton(screenW/4, 0 + 2 * (screenH/6), 300, 75, &gameFont, "SETTINGS", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(settingsButton);
        
        Button *creditsButton = new Button;
        creditsButton->createButton(screenW/4, 0 + 3 * (screenH/6), 300, 75, &gameFont, "CREDITS", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(creditsButton);
        
        Button *quitButton = new Button;
        quitButton->createButton(screenW/4, 0 + 4 * (screenH/6), 300, 75, &gameFont, "QUIT", 20, Color(0, 0, 139, 100)); 
        buttonList.push_back(quitButton);
        
        while (app.isOpen())
        {
            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                    
                else if (event.type == sf::Event::MouseButtonPressed) 
                {
                 
                    for (auto i:buttonList)
                    {
                        if (i -> visible == true and i->rect.contains(Mouse::getPosition(app).x, Mouse::getPosition(app).y) == true)
                        {
                            i->clicked = true;
                        }
                    }   
                }
            }
            
            if (buttonList[0]->clicked == true)
            {
                buttonList[0]->clicked = false;
                return 1;
            
            }
            else if (buttonList[1]->clicked == true)
            {
                buttonList[1]->clicked = false;
                return 2;
            
            }
            else if (buttonList[2]->clicked == true)
            {
                buttonList[2]->clicked = false;
                return 3;
            
            }
            else if (buttonList[3]->clicked == true)
            {
                buttonList[3]->clicked = false;
                return -1;
            
            }

            //draw
            app.draw(menuScreen);
            app.draw(buttonBacker);
            for(auto i:buttonList)
            {
                app.draw(i->rectangle);
                app.draw(i->buttonText);
            }
            app.draw(titleText);
            app.display();
        }
    
    
        return 0;
    }
};
