#ifndef button_hpp
#define button_hpp
#include <SFML/Graphics.hpp>
#include<string>
class Button
{
private:
    sf::RectangleShape Butshape;
    sf::RectangleShape Outline;
    sf::Text Buttext;
    sf::Font Butfont;
public:
    Button(float Butx, float Buty, float Butwidth, float Butheight, const std::string& Butlabel);
    void draw(sf::RenderWindow& window);
    bool IsClicked(sf::RenderWindow& window, sf::Event event);
};

#endif /* button_hpp */
