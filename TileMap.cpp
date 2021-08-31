#include "TileMap.h"

    void TileMap::createMinimap(vector<vector<int>> Map, float mapDim, float xPos, float yPos, vector<Actor*>actors, int xTiles, int yTiles)
    {
    resetMap();
    map = Map;
    //rectangle.setSize(sf::Vector2f(mapDim, mapDim));
    
    rectangle.setSize(sf::Vector2f(53 * xTiles, 53 * yTiles));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(-5);
    rectangle.setOrigin(mapDim/2, mapDim/2);
    rectangle.setPosition(xPos, yPos);
    
    createIcons(mapDim, xPos - mapDim/2, yPos - mapDim/2, actors);
    
    int tileXPos = xPos - mapDim/2;
    int tileYPos = yPos - mapDim/2;
    
    int tileNum = 0;
    int tileDim = mapDim/map.size();
    TileDim = tileDim;
    for (auto i = 0; i < xTiles; i++)
        for (auto j = 0; j < yTiles; j++)
        {
            addTile((tileXPos + (i * tileDim)),(tileYPos + (j * tileDim)), tileDim, tileNum, mapDim, map[j][i], i, j); 
            tileNum++;
        }
    }

    void TileMap::resetMap()
    {
        playerIcons.clear();
        //balls.clear();
        tileRectangles.clear();
    }

    vector<vector<Vector2i>> BFS2D(vector<vector<int>> Graph, int blocksign, int row, int column, Vector2i source, int dest, Vector2i &endCoord)
    {
        bool visited[row][column];
        vector<vector<Vector2i>> prev(row, vector<Vector2i> (column));
        queue<Vector2i> Q;
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        Vector2i cur;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                visited[i][j] = false;
                prev[i][j] = Vector2i(-1, -1);
            }
        }
   
        visited[source.x][source.y] = true;
        prev[source.x][source.y] = source;

        Q.push(source);
        while (!Q.empty())
        {
            cur = Q.front();
            Q.pop();
            if (Graph[cur.y][cur.x] == dest)
            {
                endCoord.x = cur.x;
                endCoord.y = cur.y;
                break;
            }
            for (int i = 0; i < 4; i++)
            {
                Vector2i temp;
                temp.x = cur.x + dx[i];
                temp.y = cur.y + dy[i];
                if (Graph[temp.y][temp.x] != 1 and visited[temp.x][temp.y] == false)
                {
                    visited[temp.x][temp.y] = true;
                    prev[temp.x][temp.y] = cur;
                    Q.push(temp);
                }
            }
        }
        if (Q.empty())
        {
            endCoord.x = source.x;
            endCoord.y = source.y;
        } 
        return prev;
    }
    
    void TileMap::addTile(int xTile, int yTile, int dim, int num, int mapDim, int tilePiece, int xCoord, int yCoord)
    {
        sf::RectangleShape tileRectangle;
        tileRectangle.setSize(sf::Vector2f(dim, dim));
        if (tilePiece != 1)
            tileRectangle.setFillColor(sf::Color(160, 160, 160, 255));
        else if (tilePiece == 1)
            tileRectangle.setFillColor(sf::Color(96, 96, 96, 255));
        else if (tilePiece == 2 or tilePiece == 4)
        {
            //tileRectangle.setFillColor(sf::Color(255, 0, 0, 100));
            if (tilePiece == 2)
            {
                /*Ball ball(true, Vector2i(xCoord, yCoord));
                ball.circle.setOrigin(ball.circle.getRadius(), ball.circle.getRadius());
                ball.circle.setPosition(xTile + dim/2, yTile + dim/2);
                balls.push_back(ball);*/
            }
        }
        else if (tilePiece == 3 or tilePiece == 5)
        {
            //tileRectangle.setFillColor(sf::Color(0, 0, 255, 100));
            if (tilePiece == 3)
            {
                /*Ball ball(false, Vector2i(xCoord, yCoord));
                ball.circle.setOrigin(ball.circle.getRadius(), ball.circle.getRadius());
                ball.circle.setPosition(xTile + dim/2, yTile + dim/2);
                balls.push_back(ball);*/
            }
        }
        tileRectangle.setOutlineColor(sf::Color::Black);
        tileRectangle.setOutlineThickness(-2);
        tileRectangle.setPosition(xTile, yTile);
        tileRectangles.push_back(tileRectangle);
    }
    
    /*TileMap::direction TileMap::nextMove(Actor *person)
    {
        Vector2i curPrev = Vector2i(-1, -1);
        int dest = 0;
        if (person->myTeam==true and person->balls == 0)
            dest = 2;
        else if (person->myTeam==true and person->balls != 0)
            dest = 4;
        else if (person->myTeam==false and person->balls == 0)
            dest = 3;
        else if (person->myTeam==false and person->balls != 0)
            dest = 5;
        
        vector<vector<Vector2i>> prev = BFS2D(map, 1, map.size(), map.size(), person->coords, dest, curPrev);
        while(prev[curPrev.x][curPrev.y] != person->coords)
        {
            curPrev = prev[curPrev.x][curPrev.y];
        }
        Vector2i nextDir = Vector2i(curPrev.x - person->coords.x, curPrev.y - person->coords.y);
        person->coords = curPrev;
        if (nextDir == Vector2i(-1, 0))
        {
            person->dir = Actor::direction::left;
            return left;
        }
        else if (nextDir == Vector2i(1, 0))
        {
            person->dir = Actor::direction::right;
            return right;
        }
        else if (nextDir == Vector2i(0, -1))
        {
            person->dir = Actor::direction::up;
            return up;
        }
        else if (nextDir == Vector2i(0, 1))
        {
            person->dir = Actor::direction::down;
            return down;
        }
        else if (nextDir == Vector2i(0, 0))
        {
            return hold;
        }
        
        return up;
    }*/
    
    void TileMap::createIcons(int mapDim, int mapX, int mapY, vector<Actor*> actors)
    {   
        for (int i = 0; i <actors.size(); i ++)
        {
            //actors[i]->sprite.setOrigin(actors[i]->R/2,actors[i]->R/2);
            int tileDim = mapDim/map.size();
            actors[i]->sprite.setPosition(mapX + (actors[i]->coords.x * tileDim) + tileDim/2 + 2, mapY + (actors[i]->coords.y * tileDim) + tileDim/2 + 2);
            //i->sprite.push_back(playerIcon);
        }
        
    }
    
    int TileMap::getTileElement(Vector2i coord)
    {
        return map[coord.x][coord.y];
    }
    
    //checks if the next space is open or if the moved space has something that can move
    bool TileMap::checkCanMove(Vector2i coord, Vector2i dif)
    {
        if (getTileElement(Vector2i(coord.y,coord.x)) == 0 or getTileElement(Vector2i(coord.y,coord.x)) == 3)
        {
            moveActor(coord, dif);
            return true;
        }
        else if (getTileElement(Vector2i(coord.y,coord.x)) == 2)
        {
            if (checkCanMove(coord + dif, dif))
            {
                moveActor(coord, dif);
                return true;//map[coord.y][coord.x] = 0;
                //map[coord.y + dif.y][coord.x + dif.x] = 2;
            }
        }
        return false;
    }
    
    void TileMap::printMap()
    {
        for (int i = 0; i < map.size(); i++)
        {
            for (int j = 0; j < map[0].size(); j++)
            {
                cout<<to_string(map[i][j]) + " ";
            }
            cout<<"\n";
        }
        cout<<"\n\n";
    }
    
    void TileMap::moveActor(Vector2i coord, Vector2i dif)
    {
        int tileNum = map[coord.y - dif.y][coord.x - dif.x];
        map[coord.y][coord.x] = 0;
        map[coord.y][coord.x] = tileNum;
    }
    
    bool TileMap::isCollidePlayer(Vector2i coords, Actor actor)
    {
      
        /*if (coords == ball.ballLoc)
            return true;*/
        return false;
    }
    
    /*bool TileMap::isReturnBalls(Actor *person)
    {
        if (map[person->coords.y][person->coords.x] == 4 and person->myTeam == true and person->balls > 0)
            return true;
        else if(map[person->coords.y][person->coords.x] == 5 and person->myTeam == false and person->balls > 0)
            return true;
        return false;
        
    }*/
    
    /*void TileMap::resetBalls(Actor *person)
    {
        for (int i = 0; i < person->ballList.size(); i++)
        {
            person->ballList[i]->pickedUp = false;
            if (person->ballList[i]->myTeam)
                map[person->ballList[i]->ballLoc.y][person->ballList[i]->ballLoc.x] = 2;
            else
                map[person->ballList[i]->ballLoc.y][person->ballList[i]->ballLoc.x] = 3;
        }
    }*/
    
    void TileMap::checkActor(Actor *person)
    {
        /*for (int i = 0; i < balls.size(); i++)
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
        }*/
    }
    
    bool TileMap::checkLineOfSight(Vector2i coord, Actor::direction dir)
    {
        Vector2i dif;
        if (dir == Actor::direction::left)
            dif = Vector2i(-1, 0);
        else if (dir == Actor::direction::right)
            dif = Vector2i(1, 0);
        else if (dir == Actor::direction::up)
            dif = Vector2i(0, -1);
        else if (dir == Actor::direction::down)
            dif = Vector2i(0, 1);
            
        while (map[coord.y][coord.x]!=1)
        {
            if (coord == playerLoc)
            {
                return true;
            }
            coord+=dif;
        }
        return false;
    }
    
    
    
