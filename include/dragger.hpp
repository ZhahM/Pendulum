#ifndef dragger_hpp
#define dragger_hpp
#include<iostream>
#include<SFML/Graphics.hpp>
#include<string>
class dragger
{
private:
    sf::Font butler;
    sf::RectangleShape axis;
    sf::RectangleShape dragBut;
    sf::Text label;
    sf::Vector2f draggerPosi;
    float* length;
    float* damping;
    std::string name;
    float deltaLength;
public:
    dragger(const std::string& labelString, sf::Vector2f dragPos, float* leng, float* damp);
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
};
#endif /* dragger_hpp */
