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
    std::vector<Sprite> spriteList;
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
        
        allActors.clear();
        vector<vector<int>> curLevel = levels[curGame->level];
        
        switch (curGame->level)
        {
            case 0:
            {
                player.coords = Vector2i(6, 5);
                allActors.push_back(&player);
                
                for (int i = 0; i < curLevel[0].size(); i++)
                    for (int j = 0; j < curLevel.size(); j++)
                    {
                        if (curLevel[j][i] == 2)
                        {
                            Actor *box = new Actor;
                            box->settings(spriteList[0], 0, 0, 51, 51);
                            box->createActor(Actor::actorType::box, false, Vector2i(i, j));
                            allActors.push_back(box);
                        }
                        if (curLevel[j][i] == 3)
                        {
                            Actor *redCard = new Actor;
                            redCard->settings(spriteList[1], 0, 0, 51, 51);
                            redCard->createActor(Actor::actorType::redCard, false, Vector2i(i, j));
                            allActors.push_back(redCard);
                        }
                        if (curLevel[j][i] == 6)
                        {
                            Actor *redDoor = new Actor;
                            redDoor->settings(spriteList[4], 0, 0, 51, 51);
                            redDoor->createActor(Actor::actorType::redDoor, false, Vector2i(i, j));
                            allActors.push_back(redDoor);
                        }
                    }

                break;
            }
        }
                 
        int mapDim = screenW/36 * levels[curGame->level].size();
        map -> createMinimap(levels[curGame->level],mapDim,screenW/2, screenH/2, allActors, levels[curGame->level][0].size(), levels[curGame->level].size());
    }
    
    /*bool updateActors(TileMap *map)
    {
        for (int i = 1; i < allActors.size(); i++)
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
    bool isCollideWithActor(Actor actor1, Actor actor2)
    {
      
        if (actor1.coords == actor2.coords)
            return true;
        return false;
    }
    
    void moveActor(TileMap *map, TileMap::direction pDirection, int num)
    {
        
        map->map[allActors[num]->coords.x][allActors[num]->coords.y];
        if (pDirection == TileMap::direction::up)
        {
            allActors[num]->sprite.move(0, -map->TileDim);
            allActors[num]->sprite.setRotation(0);
            allActors[num]->coords += Vector2i(0, -1);
        }
        else if (pDirection == TileMap::direction::down)
        {
            allActors[num]->sprite.move(0, map->TileDim);
            allActors[num]->sprite.setRotation(180);
            allActors[num]->coords += Vector2i(0, 1);
        }
        else if (pDirection == TileMap::direction::left)
        {
            allActors[num]->sprite.move(-map->TileDim, 0);
            allActors[num]->sprite.setRotation(270);
            allActors[num]->coords += Vector2i(-1, 0);
        }
        else if (pDirection == TileMap::direction::right)
        {
            allActors[num]->sprite.move(map->TileDim, 0);
            allActors[num]->sprite.setRotation(90);
            allActors[num]->coords += Vector2i(1, 0);
        }
        for (int i = 1; i < allActors.size(); i++)
        {
            if (i != num and isCollideWithActor(*allActors[i], *allActors[num]))
            {
                moveActor(map, pDirection, i);
            }
        }
    }
    
    
    
    /*void checkActor(Actor *person)
    {
        for (int i = 0; i < balls.size(); i++)
        {
            if (isCollideBall(person->coords, balls[i]) and balls[i].pickedUp == false and balls[i].myTeam == person->myTeam)
            {
                balls[i].pickedUp = true;
                if (balls[i].myTeam)
                    map[person->coords.y][person->coords.x] = 6;
                else
                    map[person->coords.y][person->coords.x] = 7;
                person->ballList.push_back(&balls[i]);
                person->balls++;
                break;
            }
        }
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
        
        Texture t1, t2, t3, t4, t5, t6, t7, t8;
        t1.loadFromFile("images/box.png");
        Sprite boxSprite(t1);
        spriteList.push_back(boxSprite);
        
        t2.loadFromFile("images/redCard.png");
        Sprite redCard(t2);
        spriteList.push_back(redCard);
        
        t3.loadFromFile("images/blueCard.png");
        Sprite blueCard(t3);
        spriteList.push_back(blueCard);
        
        t4.loadFromFile("images/greenCard.png");
        Sprite greenCard(t4);
        spriteList.push_back(greenCard);
        
        t5.loadFromFile("images/redDoor.png");
        Sprite redDoor(t5);
        spriteList.push_back(redDoor);
        
        t8.loadFromFile("images/player.png");
        Sprite playerSprite(t8);
        spriteList.push_back(playerSprite);
        
        vector<vector<int>> level1 =
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 3, 1, 0, 0, 0, 0, 1},
            {1, 0, 0, 2, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 6},
            {1, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1},
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
        
        player.createActor(Actor::actorType::player, true, Vector2i(7, 4));
        player.settings(spriteList[5], 0, 0, 45, 45);
        
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
	         if(map->checkCanMove(Vector2i(player.coords.x, player.coords.y - 1), Vector2i(0, -1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::up; 
	             //player.coords = Vector2i(player.coords.x, player.coords.y - 1);
	         }
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::S) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x, player.coords.y + 1), Vector2i(0, 1)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::down; 
	             //player.coords = Vector2i(player.coords.x, player.coords.y + 1);
	         }            
	     }   
	     else if (Keyboard::isKeyPressed(Keyboard::A) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x - 1, player.coords.y), Vector2i(-1, 0)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::left; 
	             //player.coords = Vector2i(player.coords.x - 1, player.coords.y);
	         }            
	     }     
	     else if (Keyboard::isKeyPressed(Keyboard::D) and !waiting and !loseCondition)
	     {
	         if(map->checkCanMove(Vector2i(player.coords.x + 1, player.coords.y), Vector2i(1, 0)))
	         {
	             performTurn = true;
	             pDirection = TileMap::direction::right; 
	             //player.coords = Vector2i(player.coords.x + 1, player.coords.y);
	         }          
	     } 
	     else if (Keyboard::isKeyPressed(Keyboard::Space) and !waiting and !loseCondition)
	     {
	         performTurn = true;
	         pDirection = TileMap::direction::hold;
	     }
         
             if (performTurn and !waiting and !winGame)
             {
                 map->printMap();
                 performTurn = false;
                 waiting = true;
                 tick = 0;
                 map->playerLoc = player.coords;
                 moveActor(map, pDirection, 0);
                 /*if (updatePlayers(map))
                 {
                     loseCondition = true;
                     caught = true;
                 }*/
             }
             
             if(waiting)
             {
                 tick++;
                 if (tick == 15)
                     waiting = false;
             }

            
            if (!winGame)
            {
                app.draw(map -> rectangle);
                for(auto i:(map -> tileRectangles)) app.draw(i);
                for(auto i:(map -> playerIcons)) app.draw(i);
                for(auto i:allActors) app.draw(i->sprite);
            
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
