#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <list>
#include <stdlib.h> 
#include <math.h>
#include <cstring>
#include "Entity.h"
#include "Button.h"
#include "Actor.h"
#include "Game.h"
#include "State.h"
#include "MenuState.h"
#include "PlayState.h"
#include "HowState.h"
#include "CreditsState.h"

using namespace sf;
using namespace std;
float DEGTORAD = 0.017453f;
const int screenW = sf::VideoMode::getDesktopMode().width;
const int screenH = sf::VideoMode::getDesktopMode().height;
    
sf::Text source;
sf::Font mainGameFont;

int main() 
{
    cout << to_string(screenW) + "," + to_string(screenH) + "\n";
    srand(time(NULL));
    std::vector<State*> stateList;
    Game *game = new Game;
    int state = 0;
    
    RenderWindow app(VideoMode(screenW, screenH), "Cosmoball!");
    app.setFramerateLimit(60);
    mainGameFont.loadFromFile("pirulen.ttf");
    source.setFont(mainGameFont);
    
    game->startGame(screenW, screenH, source, mainGameFont);
    
    MenuState *menuState = new MenuState;
    menuState -> createState(game);
    stateList.push_back(menuState);

    PlayState *playState = new PlayState;
    playState -> createState(game);
    stateList.push_back(playState);
    
    HowState *howState = new HowState;
    howState -> createState(game);
    stateList.push_back(howState);
    
    CreditsState *creditsState = new CreditsState;
    creditsState -> createState(game);
    stateList.push_back(creditsState);

    game->stateList = stateList;
    
    while (state >= 0)
    {
        state = stateList[state]->Run(app);
        //music.stop();
    }

    return 0;
}
