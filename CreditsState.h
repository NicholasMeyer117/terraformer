class CreditsState: public State
{
    public:
    int screenW;
    int screenH;
    sf::Font gameFont;
    sf::Font spaceFont;
    sf::Text source;
    sf::Text titleText;
    std::vector<Button*> buttonList;
    
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
        titleText.setString("Credits");
        titleText.setCharacterSize(70);
        titleText.setFillColor(sf::Color::Black);
        sf::FloatRect textRect = titleText.getLocalBounds();
        titleText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        titleText.setPosition(screenW/2, screenH/8);
        
        Button *backButton = new Button;
        backButton->createButton(screenW/2, screenH - screenH/6, 400, 100, &gameFont, "BACK", 20); 
        buttonList.push_back(backButton);
        
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

            drawText("This game was made by Nick Meyer in 7 days for the\n August 8th-17th 'Major Jam 4: Cosmic' game jam.\n\n\n"
            "The game was coded in C++ using the SFML2 libraries\n\n\n"
            "The font used is pirulen.ttf by Typodermic Fonts\n\n\n"
            "Music and sounds were made by me in Borsa Ceoil\n\n\n"
            "All art was done by me", 24, screenW/4, 0 + screenH/5, app);
            app.draw(titleText);
            app.display();
        }
    
    
        return 0;
    }
};
