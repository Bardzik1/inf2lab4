#include "Game.h"
#include "Menu.h"
#include <optional>  

enum class GameState { Menu, Playing, Scores, Exiting };

int main()
{
    const float width = 640.f;
    const float height = 480.f;

    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(width), static_cast<unsigned>(height) }), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(width, height);
    Game game;  

    GameState currentState = GameState::Menu;

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();

        while (const std::optional ev = window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = ev->getIf<sf::Event::KeyPressed>())
            {
                
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                {
                    currentState = GameState::Exiting;
                    window.close();
                }

                if (currentState == GameState::Menu)
                {
                    if (key->scancode == sf::Keyboard::Scancode::Up)
                        menu.przesunG();

                    else if (key->scancode == sf::Keyboard::Scancode::Down)
                        menu.przesunD();

                    else if (key->scancode == sf::Keyboard::Scancode::Enter)
                    {
                        int idx = menu.getSelectedItem();

                        if (idx == 0)
                            currentState = GameState::Playing;

                        else if (idx == 1)
                            currentState = GameState::Scores;

                        else if (idx == 2)
                        {
                            currentState = GameState::Exiting;
                            window.close();
                        }
                    }
                }
            }
        }

  
        if (currentState == GameState::Playing)
        {
            game.update();  
        }

        window.clear();

        if (currentState == GameState::Menu)
        {
            menu.draw(window);
        }
        else if (currentState == GameState::Playing)
        {
            game.render(window); 
        }
        else if (currentState == GameState::Scores)
        {
   
        }

        window.display();
    }

    return 0;
}