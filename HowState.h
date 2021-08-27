class HowState: public State
{
    public:
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Font spaceFont;
    sf::Text source;
    sf::Text titleText;
    std::vector<Button*> buttonList;
    std::vector<CircleShape> icons;
    
    void createState(Game *game)
    {
        screenW = game->screenWidth;
        screenH = game->screenHeight;
        source = game->source;
        spaceFont.loadFromFile("pirulen.ttf");
        gameFont = game->gameFont;
        
    }
    
    void drawText( const sf::String &str, const int Size, const float xposition, const float yposition, sf::RenderWindow& window)
    {
        source.setString(str);
        source.setCharacterSize(Size);
        source.setPosition(xposition,yposition);
        source.setFillColor(Color::Black);
        window.draw(source);
    }
    
    int Run(sf::RenderWindow &app)
    {
        titleText.setFont(spaceFont);
        titleText.setString("How To Play");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/2, screenH/8);
        
        Button *backButton = new Button;
        backButton->createButton(screenW/2, screenH - screenH/6, 400, 100, &gameFont, "BACK", 20); 
        buttonList.push_back(backButton);
        
        for (int i = 0; i < 5; i++)
        {
            sf::CircleShape playerIcon;
            playerIcon.setRadius(25);
            playerIcon.setOrigin(12.5, 12.5);
            playerIcon.setPointCount(3);
            playerIcon.setRotation(90);
            playerIcon.setOutlineColor(sf::Color::Black);
            playerIcon.setOutlineThickness(2);
            playerIcon.setPosition(0 + screenW/32 + 100, 0 + screenH/5);
            if (i == 0)
            {
                playerIcon.setFillColor(sf::Color::Green);
            }
            else if (i == 1)
            {
                playerIcon.setFillColor(sf::Color::Red);
                playerIcon.move(220, 87);
            }
            else if (i == 2)
            {
                playerIcon.setFillColor(sf::Color::Blue);
                playerIcon.move(180, 174);
            }
            else if (i == 3)
            {
                playerIcon.setFillColor(sf::Color::Red);
                playerIcon.setPointCount(100);
                playerIcon.move(245, 261);
            }
            else if (i == 4)
            {
                playerIcon.setFillColor(sf::Color::Blue);
                playerIcon.setPointCount(105);
                playerIcon.move(270, 348);
            }
            icons.push_back(playerIcon);
        }
        
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
            
            if (backButton->clicked == true)
            {
                backButton->clicked = false;
                return 0;
            
            }

            //draw
            app.clear(Color(255,255,255,255));
            for(auto i:buttonList)
            {
                app.draw(i->rectangle);
                app.draw(i->buttonText);
            }
            drawText("You:\n\n\n\nYour teammates:\n\n\n\nEnemy players:\n\n\n\n"
            "Your teams balls:\n\n\n\nEnemy teams balls:\n\n\n\nMove: WASD\n\nStay: Space\n\nQuit: Q", 20, 0 + screenW/32, 0 + screenH/5, app);
            drawText("Welcome to Cosmoball! The game of the future!\n\n"
            "The objective is to score more points than the other team\n\n"
            "by gathering the other team's balls and bringing them \n\n"
            "to your team's goals. Each teams goals are located on their\n\n"
            "side of the field. Balls are located around the middle. Each\n\n"
            "player is only allowed to carry ONE BALL. Carrying more than\n\n" 
            "one ball is CHEATING! so make sure to NEVER carry more\n\n"
            "than one. If an enemy player spots you (in their \n\n"
            "line of sight), you will be disqualified. The game is turn\n\n"
            "based and the team that makes it to the specified score\n\n" 
            "first wins the match. Good luck and DON'T CHEAT ;)\n\n", 23, 0 + screenW/4, 0 + screenH/5, app);
            for (auto i:icons)
                app.draw(i);
            app.draw(titleText);
            app.display();
        }
    
    
        return 0;
    }
};
