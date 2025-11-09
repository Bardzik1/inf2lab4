#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Paddle.h"
#include <iostream>

int main()
{
	const float width = 640.f;
	const float height = 480.f;
	sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(width), static_cast<unsigned>(height) }), "Arkanoid Test");
	window.setFramerateLimit(60);

    sf::Clock zegar;

	Paddle pal(320.f, 440.f, 100.f, 20.f, 8.f);

	Ball pilka(320.f, 200.f, 8.f, 2.f, 1.f);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }

        // Rest of the main loop
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            pal.moveLeft();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            pal.moveRight();
        }

        pal.clamp(width);
        pilka.move();
        pilka.collideWalls(width, height);
        pilka.collidePaddle(pal);
        
        if (pilka.collidePaddle(pal))
        {
            std::cout << "HIT PADDLE\n";
        };

        if (pilka.getY() - pilka.getRadius() > height)
        {
            std::cout << "GAME LOST";
            break;
        };

        if (zegar.getElapsedTime().asSeconds() >= 2.f)
        {
            std::cout << "x= " << pilka.getX()
                << " y=" << pilka.getY()
                << " vx=" << pilka.getVx()
                << " vy=" << pilka.getVy()
                << std::endl;

            zegar.restart();
        }


        window.clear(sf::Color(20, 20, 20));
        pal.draw(window);
        pilka.draw(window);
        window.display();
    }

	
};





