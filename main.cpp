#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#define PI 3.14159265359

bool lost; int p1Score, p2Score;
float speed, ballVelX, ballVelY, ballSpeed, dt; 
sf::RectangleShape p1, p2;
sf::CircleShape ball;
sf::RenderWindow window(sf::VideoMode(1024, 640), "Pong");

sf::Clock deltaclock;

void borders()
{
    float x, y;

    x = p1.getPosition().x; y = p1.getPosition().y;
    if (y < 50)
        p1.setPosition(x, 50);
    if (y > 590)
        p1.setPosition(x, 590);

    x = p2.getPosition().x; y = p2.getPosition().y;
    if (y < 50)
        p2.setPosition(x, 50);
    if (y > 590)
        p2.setPosition(x, 590);
}

void controls()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        p1.move(0, -speed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        p1.move(0, speed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        p2.move(0, -speed * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        p2.move(0, speed * dt);
    }
}

void simulateBall()
{
    sf::Vector2f ballPos = ball.getPosition(); 
    sf::Vector2f p1Pos, p2Pos;
    p1Pos = p1.getPosition(); p2Pos = p2.getPosition();

    if (ballPos.x > 1024 || ballPos.x < 0) {lost = true; if (ballPos.x > 1024) p1Score++; else if (ballPos.x < 0) p2Score++; return;}
    if (ballPos.y > 640 || ballPos.y < 0) ballVelY *= -1;

    if (ball.getGlobalBounds().intersects(p1.getGlobalBounds())) ballVelX *= -1;
    if (ball.getGlobalBounds().intersects(p2.getGlobalBounds())) ballVelX *= -1;

    ball.move(ballVelX * dt, ballVelY * dt);
}

void init()
{
    srand(time(NULL));
    window.setFramerateLimit(200);

    speed = 350; ballSpeed = 300;
    
    p1.setSize(sf::Vector2f(10, 100));
    p2.setSize(sf::Vector2f(10, 100));
    p1.setOrigin(10, 50);
    p2.setOrigin(0, 50);
    p1.setPosition(50, 320);
    p2.setPosition(972, 320);

    ball.setRadius(5);
    ball.setOrigin(5, 5);
    ball.setPosition(512, 320);
    
    int choice = rand() % 4 + 1;
    
    if (choice == 1) {ballVelX = ballSpeed * 1; ballVelY = ballSpeed * 1;}
    if (choice == 2) {ballVelX = ballSpeed * 1; ballVelY = ballSpeed * -1;}
    if (choice == 3) {ballVelX = ballSpeed * -1; ballVelY = ballSpeed * 1;}
    if (choice == 4) {ballVelX = ballSpeed * -1; ballVelY = ballSpeed * -1;}
}
int main()
{
    p1Score = p2Score = 0;

    while (window.isOpen())
    {
        std::cout << p1Score << ' ' << p2Score << '\n';

        init();

        lost = false; bool game = false;
        while (!lost)
        {
            sf::Time temp = deltaclock.restart();
            dt = temp.asSeconds();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    break;
                }
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                game = true;
            
            if (game)
            {
                controls();
                borders();
                simulateBall();
            }

            window.clear();
            window.draw(p1);
            window.draw(ball);
            window.draw(p2);
            window.display();
        }
    }

    return 0;
}
