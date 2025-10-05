#include<SFML/Graphics.hpp>
#include<iostream>
#include"include/button.hpp"
#include<cmath>
#include<iomanip>
#include<sstream>
#include"include/dragger.hpp"
#include"include/additional.hpp"
//constants
const float g = 9.8*1000.f;
const float PI = 3.14159;
const sf::Vector2f pivotPos(400.f, 150.f);
int main()
{
    //numbers
    float length = 350.f; //--- 35 cm
    float initTheta = PI/4;
    float Theta = initTheta;
    float angularVel = 0.f;
    float angularAcc = 0.f;
    float damping=1.f;
    
    
    //loading the FONT BUTLER
    
    sf::Font butler;
    butler.loadFromFile("assets/butler.otf");
    
    
    //window
    sf::RenderWindow window(sf::VideoMode(800, 800), "Pendulum", sf::Style::Close | sf::Style::Resize);
    
    
    //grapgwniwd
    additional graphWindow(&Theta, &length, &angularVel, &damping, &angularAcc);
    
    
    // Additional button
    Button newWindButton(595.f, 5.f, 200.f, 100.f, "Additional"); //Button(float Butx, float Buty, float Butwidth, float Butheight, const std::string&)
    
    
    //pivot
    sf::CircleShape pivot(3.5f);
    pivot.setFillColor(sf::Color(123.f, 224.f, 124.f));
    pivot.setOrigin(3.5f, 3.5f);
    pivot.setPosition(pivotPos);
    
    //bob
    sf::CircleShape bob(20.f);
    bob.setOrigin(20.f, 20.f);
    bob.setFillColor(sf::Color(43, 99, 148));

    
// texts

    
    //text of length
    
    sf::Text lengthLabel;
    lengthLabel.setFont(butler);
    lengthLabel.setCharacterSize(30);
    lengthLabel.setPosition(625, 230);
    lengthLabel.setFillColor(sf::Color::White);
    
    //text of theta
    sf::Text thetaLabel;
    thetaLabel.setFont(butler);
    thetaLabel.setCharacterSize(30);
    thetaLabel.setPosition(625, 265);
    thetaLabel.setFillColor(sf::Color::White);
    
    //clock vars
    sf::Clock clock;
    float elapsedTime = 0.f;
    
    
    //texture
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/backoftheclub.png");
    sf::Sprite background(backgroundTexture);
    sf::Texture bobTexture;
    bobTexture.loadFromFile("assets/shar.png");
    bob.setTexture(&bobTexture);
    
    
    sf::RectangleShape panel(sf::Vector2f(400.f, 200.f));
    panel.setOrigin(sf::Vector2f(200.f, 0.f));
    panel.setPosition(sf::Vector2f(790.f, 0.f));
    panel.setFillColor(sf::Color::Black);
    
    //dragger
   /* sf::RectangleShape lengthDraggerAxis(sf::Vector2f(200.f, 2.f));
    lengthDraggerAxis.setFillColor(sf::Color(128, 128, 128));
    lengthDraggerAxis.setPosition(600.f, 200.f);
    
    sf::RectangleShape lengthDraggerItself(sf::Vector2f(10.f, 20.f));
    lengthDraggerItself.setOrigin(5.f, 10.f);
    lengthDraggerItself.setPosition(700.f, 200.f);*/
    
    
    dragger lengLabel("Length:", sf::Vector2f(600.f, 110.f), &length, &damping);
    dragger ThetaLabel("Damping:", sf::Vector2f(600.f, 160.f), &length, &damping);
    
    //window open
    while(window.isOpen())
    {
        //events
        sf::Event ev;
        while(window.pollEvent(ev))
        {
            switch (ev.type)
            {
                    //closeev
                case sf::Event::Closed:
                    window.close();
                    break;
                    //resetting and moving bob mu mouse
                case sf::Event::MouseButtonPressed:
                   /* if(ev.mouseButton.button == sf::Mouse::Left)
                    {
                        angularVel = 0.f;
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        float dx = mousePos.x - pivotPos.x;
                        Theta = asin(dx/length);
                    }*/
            }
            //graph window
            if(newWindButton.IsClicked(window, ev))
            {
                graphWindow.create();
            }
        }
        
        //graph window functions
        
        graphWindow.handleEvents();
                graphWindow.update();
        
        //moving bob
 
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                Theta+=0.0003;
                angularVel = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                Theta-=0.0003;
                angularVel = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0))
            {
                Theta=0.f;
                angularVel = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            {
                length-=0.12f;
                angularVel = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            {
                length+=0.12f;
                angularVel = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
            {
                Theta=M_PI/4;
                angularVel = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                angularVel+=0.003f;
                Theta = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                angularVel-=0.003f;
                Theta = 0.f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
            {
                damping+=0.000003f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
            {
                damping-=0.000003f;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            {
                damping=1.f;
            }
           if(abs(Theta)/(M_PI) > 1.f)
            {
                Theta = Theta- (Theta/(M_PI))*(2*M_PI);
            }
            if(length < 0.0001f)
            {
                length = 350.f;
                angularVel = 0.f;
            }
        }
        
        //time reset
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        
        //physics
        angularAcc = -((g/length))*sin(Theta);
        angularVel = damping*(angularVel + angularAcc*dt);
        Theta += angularVel*dt;
        sf::Vector2f bobPos((pivotPos.x+length*sin(Theta)),(pivotPos.y+length*cos(Theta)));
        
 
        
        //rod up
        sf::VertexArray rod(sf::Lines, 2);
        rod[0].position = pivotPos;
        rod[0].color = sf::Color::White;
        rod[1].position = bobPos;
        rod[1].color = sf::Color(158, 158, 240);
        bob.setPosition(bobPos);
        
        //window ops
        
        //lengthLabel
        std::stringstream ll;
        ll << std::fixed << std::setprecision(0) << (length/10);
        lengthLabel.setString("Length: " + ll.str() + "cm");
        
        std::stringstream tt;
        tt << std::fixed << std::setprecision(0) << (Theta*180/M_PI);
        thetaLabel.setString("Angle: " + tt.str() + "deg");
        
        lengLabel.update(window);
        ThetaLabel.update(window);
        
        //windowcloear
        window.clear();
        //window drawing
        window.draw(background);
        window.draw(rod);
        window.draw(pivot);
        window.draw(bob);
        window.draw(lengthLabel);
        window.draw(thetaLabel);
        
      //  window.draw(panel);
        
        
        newWindButton.draw(window);
        lengLabel.draw(window);
        ThetaLabel.draw(window);
        window.display();
    }
    return 0;
}
