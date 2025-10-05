#include"/Users/JoanPaulo/Desktop/PhM/Code/penduluum/penduluum/button.hpp"
Button::Button(float Butx, float Buty, float Butwidth, float Butheight, const std::string& Butlabel)
{
    Butfont.loadFromFile("butler.otf");
    
    //buton shape
    Butshape.setSize(sf::Vector2f(Butwidth, Butheight));
    Butshape.setFillColor(sf::Color(211, 211, 211)); // colour is light grey
    Butshape.setPosition(Butx, Buty);
    
    //outlien
    Outline.setSize(sf::Vector2f(Butwidth+10.f, Butheight+10.f));
    Outline.setFillColor(sf::Color(128, 128, 128));
    Outline.setPosition(Butx-5.f, Buty-5.f);
    
    //text
    Buttext.setFont(Butfont);
    Buttext.setString(Butlabel);
    Buttext.setCharacterSize(42);
    Buttext.setFillColor(sf::Color::Black); // colour is black
    Buttext.setPosition(Butx+Butwidth*0.05, Buty+Butheight*0.3);
}
void Button::draw(sf::RenderWindow& window)
{
    window.draw(Outline);
    window.draw(Butshape);
    window.draw(Buttext);
}

//when button is clicked


bool Button::IsClicked(sf::RenderWindow& window, sf::Event event)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if( Butshape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
            return true;
    }
    return false;
}
