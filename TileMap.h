#pragma once
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include <math.h>
#include <cstring>
#include <queue>
#include "Entity.h"
#include "Actor.h"
//#include "Ball.h"
//#include "TileMap.h"
#include <stdlib.h> 

#define PI 3.14159265

using namespace sf;
using namespace std;

class TileMap
{
    public:
    //std::string tilemap;
    sf::RectangleShape rectangle;
    std::vector<CircleShape> playerIcons;
    std::vector<Sprite*> actorIcons;
    std::vector<RectangleShape> tileRectangles;
    //vector<Ball> balls;
    enum direction {up, down, left, right, hold};
    vector<vector<int>> map;
    int TileDim;
    Vector2i playerLoc = Vector2i(0,0); 
    
    
    void createMinimap(vector<vector<int>> Map, float mapDim, float xPos, float yPos, vector<Actor*> players, int xTiles, int yTiles);
    
    void addTile(int xTile, int yTile, int dim, int num, int mapDim, int tilePiece, int xCoord, int yCoord);
    
    int getTileElement(Vector2i coord);
    
    bool checkCanMove(Vector2i coord, Vector2i dif);
    
    bool isCollidePlayer(Vector2i coords, Actor actor);
    
    //bool isReturnBalls(Actor *person);
    
    //void resetBalls(Actor *person);
    
    void resetMap();
    
    void printMap();
    
    void createIcons(int mapDim, int mapX, int mapY, vector<Actor*> players);
    
    void checkActor(Actor *person);
    
    void moveActor(Vector2i coord, Vector2i dif);
    
    bool checkLineOfSight(Vector2i coord, Actor::direction dir);
    
    //vector<vector<Vector2i>> BFS2D(vector<vector<int>> Graph, int blocksign, int row, int column, Vector2i source, int dest, Vector2i &endCoord);
    
    direction nextMove(Actor *person);
    
    void updateMinimap(direction pDirection, int num);
};
