#pragma once
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
#include "TileMap.h"
#include "ParticleSystem.h"

class PlayState: public State
{
    public:
    std::vector<Button*> buttonList;
    std::vector<Entity*> entities;
    std::vector<Actor*> allActors;
    vector<vector<vector<int>>> levels;
    Actor player;
    
    Game *curGame;
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Text source;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        gameFont = game->gameFont;
        curGame = game;
    
    }
    
    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size);
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::White);
        window.draw(source);
    }
    
    bool levelComplete (int level)
    {
        /*switch(level)
        {
            case 0:
                if (curGame->blueScore >= curGame->winScore)
                    return true;
                else if (curGame->redScore  >= curGame->winScore)
                    return true;
                else
                    break;
            case 1:
                if (curGame->blueScore >= curGame->winScore)
                    return true;
                else if (curGame->redScore  >= curGame->winScore)
                    return true;
                else
                    break; 
            case 2:
                if (curGame->blueScore >= curGame->winScore)
                    return true;
                else if (curGame->redScore  >= curGame->winScore)
                    return true;
                else
                    break;   
        
        }*/
        return false;
    }
    
    void createLevel(TileMap *map)
    {
    
        
        int mapDim = screenW/36 * levels[curGame->level].size();
        map -> createMinimap(levels[curGame->level],mapDim,screenW/2, screenH/2, allActors);
    }
    
    /*bool updatePlayers(TileMap *map)
    {
        for (int i = 1; i < allPlayers.size(); i++)
        {
            TileMap::direction dir = map->nextMove(allPlayers[i]);
            map->updateMinimap(dir, i);
        }
        for (auto i:redPlayers)
        {
            map->checkActor(i);
            if (map->isReturnBalls(i))
            {
                curGame->redGetsPoints(i->balls);
                map->resetBalls(i);
                i->dropBalls();
            }
        }
        for (auto i:bluePlayers)
        {
            map->checkActor(i);
            if (map->checkLineOfSight(i->coords, i->dir))
                if (player.balls > 1)
                {
                    return true;
                }
            if (map->isReturnBalls(i))
            {
                curGame->blueGetsPoints(i->balls);
                map->resetBalls(i);
                i->dropBalls();
            }
        }
        return false;
    }*/
    
    int Run(sf::RenderWindow &app)
    {
    
        bool performTurn = false;
        bool waiting = false;
        bool caught = false;
        bool loseCondition = false;
        bool winGame = false;
        int tick = 0;
        int playerScore = 0;
        int enemyScore = 0;
        TileMap::direction pDirection;
        
        ParticleSystem backParticles1(400, 20000, 10, 100, 4, Color::White, 0, screenH/8, screenH, screenW, 0);
        ParticleSystem backParticles2(800, 20000, 10, 150, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 200);
        ParticleSystem backParticles3(400, 20000, 10, 200, 4, Color::White, 0, screenH/8, screenH, screenW, 0, 100);
        sf::Clock clock;
        
        vector<vector<int>> level1 =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 0, 0, 0, 0, 0, 4, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 1},
            {1, 0, 1, 2, 0, 3, 1, 0, 1},
            {1, 5, 0, 0, 1, 0, 0, 4, 1},
            {1, 0, 1, 2, 0, 3, 1, 0, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 1},
            {1, 5, 0, 0, 0, 0, 0, 4, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1},

        };
        levels.push_back(level1);
        
        vector<vector<int>> level2 =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 2, 1, 0, 1, 0, 1, 3, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 3, 1, 0, 0, 0, 0, 1},
            {1, 5, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4, 1},
            {1, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 2, 1, 0, 1, 0, 1, 3, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
            {1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

        };
        levels.push_back(level2);
        
        vector<vector<int>> level3 =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 0, 2, 1, 0, 0, 0, 1, 3, 0, 4, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 1, 0, 2, 1, 3, 0, 1, 0, 0, 1},
            {1, 5, 0, 0, 0, 1, 1, 1, 0, 0, 0, 4, 1},
            {1, 0, 0, 1, 0, 2, 1, 3, 0, 1, 0, 0, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
            {1, 5, 0, 2, 1, 0, 0, 0, 1, 3, 0, 4, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        };
        levels.push_back(level3);
        
        player.createActor(true, true, Vector2i(7, 4));
        
        sf::Music music;
        if (!music.openFromFile("sounds/cosmoball.wav"))
            return -1; // error
        music.play();
        music.setLoop(true);
        
        TileMap *map = new TileMap();
        createLevel(map);

        while (app.isOpen())
        {

            Event event;
            while (app.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    app.close();
                
            }
	         
	     //Quit Game
	     if (Keyboard::isKeyPressed(Keyboard::Q))
	         return -1;
	   
	    //Player Movement
	     if (Keyboard::isKeyPressed(Keyboard::W) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x, player.coords.y - 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::up; 
	             player.coords = Vector2i(player.coords.x, player.coords.y - 1);
	         }
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::S) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x, player.coords.y + 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::down; 
	             player.coords = Vector2i(player.coords.x, player.coords.y + 1);
	         }            
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::A) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x - 1, player.coords.y)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::left; 
	             player.coords = Vector2i(player.coords.x - 1, player.coords.y);
	         }            
	     }     
	     else if (Keyboard::isKeyPressed(Keyboard::D) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x + 1, player.coords.y)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::right; 
	             player.coords = Vector2i(player.coords.x + 1, player.coords.y);
	         }          
	     } 
	     else if (Keyboard::isKeyPressed(Keyboard::Space) and !waiting and !loseCondition)
	     {
	         performTurn = true;
	         pDirection = TileMap::direction::hold;
	     }
         
             /*if (performTurn and !waiting and !winGame)
             {
                 performTurn = false;
                 waiting = true;
                 tick = 0;
                 map->playerLoc = player.coords;
                 map->updateMinimap(pDirection, 0);
                 if (updatePlayers(map))
                 {
                     loseCondition = true;
                     caught = true;
                 }
                 if (levelComplete(curGame->level))
                 {
                     if (curGame->blueScore < curGame->redScore and curGame->level != 2)
                     {
                         curGame->level++;
                         createLevel(map);
                     }
                     else if (curGame->blueScore < curGame->redScore and curGame->level == 2)
                     {
                         winGame = true;
                     }
                     else
                         loseCondition = true;

                 }
             }*/
             
             if(waiting)
             {
                 tick++;
                 if (tick == 15)
                     waiting = false;
             }
             
             sf::Time elapsed = clock.restart();
             backParticles1.update(elapsed);
             backParticles2.update(elapsed);
             backParticles3.update(elapsed);
             
            app.draw(backParticles3);
            app.draw(backParticles2);
            app.draw(backParticles1);
            
            if (!winGame)
            {
                app.draw(map -> rectangle);
                for(auto i:(map -> tileRectangles)) app.draw(i);
                for(auto i:(map -> playerIcons)) app.draw(i);
            
            }
            if (loseCondition)
            {

            }
            if (winGame)
            {

            }
            app.display();
            app.clear(Color::Black);
        }
    
        return -1;
    }

    
    
};
