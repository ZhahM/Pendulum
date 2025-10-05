#ifndef additional_hpp
#define additional_hpp
#include<vector>
#include<cmath>
#include<SFML/Graphics.hpp>
class additional
{
private:
    sf::RenderWindow window;
    bool isOpen;
    //time tracking
    sf::Clock clockGraph;
    sf::Clock totalElapsedTime;
    
    //graph
    
    sf::VertexArray graph;
    
    //Flow
    sf::VertexArray ODEgraph;
    sf::CircleShape ODEpoint;
    
    //pointers
    
    float* Theta;
    float* length;
    float* angularVel;
    float* damping;
    float* angularAcc;
    
    //axis
    
    sf::RectangleShape axisX;
    sf::RectangleShape axisY;
    sf::RectangleShape maxTheta;
    
    
    //labels
    sf::Font labelFont;
    sf::Text labelText;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    
    std::vector<sf::RectangleShape> arrows();
    
/*    sf::RectangleShape axisTenergy;
    sf::RectangleShape axisEenergy;
    sf::VertexArray graphPotEnergy;
    sf::VertexArray graphKinEnergy;*/
    
    sf::RectangleShape KinEnergyBar;
    sf::RectangleShape PotEnergyBar;
    sf::RectangleShape EnergyBarMax;
    
    float initAgnularVel;
    
    float KinEnergyHeight;
    float PotEnergyHeight;
    
    sf::Vector2f KinEnergyBarVec;
    sf::Vector2f PotEnergyBarVec;

    
public:
    additional(float* theta, float* L, float* omega, float* damp, float* epsilon);
    void create();     // Create a new window
    void handleEvents(); // Handle events for the new window
    void update();     // Update new window
    bool getStatus();
    
};
#endif /* additional_hpp */
