#include "dragger.hpp"
dragger::dragger(const std::string& labelString, sf::Vector2f dragPos, float* leng, float* damp) : length(leng), damping(damp)
{
    draggerPosi = sf::Vector2f(dragPos);
    butler.loadFromFile("butler.otf");
    name = labelString;
    
    label.setFont(butler);
    label.setCharacterSize(50);
    label.setFillColor(sf::Color::White);
    label.setScale(0.7f, 0.6f);
    label.setPosition(dragPos);
    label.setString(labelString);
    
    axis.setSize(sf::Vector2f(200.f, 2.f));
    axis.setFillColor(sf::Color(128, 128, 128));
    axis.setPosition((dragPos.x-5.f), (dragPos.y+50.f));
    
    dragBut.setSize(sf::Vector2f(5.f, 14.f));
    dragBut.setOrigin(sf::Vector2f(2.5f, 7.f));
    dragBut.setPosition((draggerPosi.x+100.f), (draggerPosi.y+49.f));
    
}
sf::Clock clockdr;

void dragger::update(sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if(mousePos.x > 600.f and mousePos.x < 800.f and mousePos.y < draggerPosi.y+60.f and mousePos.y > draggerPosi.y+40.f)
        {
            float dt = clockdr.restart().asSeconds();
            dragBut.setPosition(mousePos.x, draggerPosi.y+49.f);
            deltaLength = -(draggerPosi.x+100.f)+mousePos.x;
            if(name == "Length:")
            {
                *length = 350.f + deltaLength * 5.f; // * dt;
            }
            if (name == "Damping:")
            {
                *damping = 1.f - deltaLength * 0.000003f;
            }
        }
    }
}


void dragger::draw(sf::RenderWindow& window)
{
    window.draw(label);
    window.draw(axis);
    window.draw(dragBut);
}
