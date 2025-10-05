#include "additional.hpp"
#include<SFML/Graphics.hpp>
#include<cmath>
#include<iostream>
const int WIDTH = 600;
const float g = 9.8f*1000;
const float barWidth = 40.f;
const float m = 0.00005f;
const int HEIGHT = 240;
additional::additional(float* theta, float* L, float* omega, float* damp, float* epsilon) : isOpen(false), Theta(theta), length(L), angularVel(omega), damping(damp), angularAcc(epsilon) {}
void additional::create()
{
    if (!isOpen)
    {
        window.create(sf::VideoMode(700, 700), "Graph", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
        isOpen = true;
    }
    // X-Axis
    axisX.setSize(sf::Vector2f(700.f, 2.f));
    axisX.setFillColor(sf::Color::Black);
    axisX.setPosition(32.f, 120.f);

    // Y-Axis
    axisY.setSize(sf::Vector2f(2.f, 240.f));
    axisY.setFillColor(sf::Color::Black);
    axisY.setPosition(30.f, 10.f);
    //maxTheta
    float maxtheta=0.f;
    maxTheta.setSize(sf::Vector2f(700.f, 2.f));
    maxTheta.setFillColor(sf::Color(128.f, 128.f,128.f, 128.f));
    maxTheta.setPosition(12.f, 10.f+120.f-maxtheta);
    
    //energy graph stuff
    
    /*
    minTheta.setSize(sf::Vector2f(700.f, 2.f));
    minTheta.setFillColor(sf::Color(128.f, 128.f,128.f, 128.f));
    minTheta.setPosition(12.f, 119.f+maxtheta);*/
    
    
    if(!backgroundTexture.loadFromFile("bacgroundAddSeven.png"))
    {
        std::cerr << "unable to find the file" << std::endl;
    }
    background.setTexture(backgroundTexture);
    
    
}


sf::Vector2f toScreen(float x, float y)
{
    float scaleX = WIDTH / 12;
    float scaleY = HEIGHT / (1 * M_PI);
    return sf::Vector2f(32.f + scaleX * x, -1*scaleY * y + 120.f);
}
// energy to screen
sf::Vector2f ToScreenEnergy(float x, float y)
{
    float scaleX = WIDTH/12;
    float scaleY = HEIGHT/(5);
    return (sf::Vector2f(32.f+scaleX*x, 300.f-scaleY*y));
}



sf::Vector2f ToScreenEllipse(float x, float y)
{
    float scaleX = WIDTH/(4*M_PI);
    float scaleY = HEIGHT/16;
    return (sf::Vector2f(211.f+scaleX*x, 487.f-scaleY*y));
}

sf::VertexArray graph(sf::LineStrip);


//PhaseVector

sf::Vector2f vectorComputer(float angle, float angVel, float *length, float*damping)
{
    return (sf::Vector2f(angVel, -(*damping/m)-(g/(*length)*sin(angle))));
}


/*sf::VertexArray graphPotEnergy(sf::LineStrip);
sf::VertexArray graphKinEnergy(sf::LineStrip);
*/

sf::VertexArray ODEgraph(sf::LineStrip);
sf::VertexArray ODEgraphAdd1(sf::LineStrip);


void additional::handleEvents()
{
    if (isOpen)
    {
        sf::Event eve;
        while (window.pollEvent(eve))
        {
            if (eve.type == sf::Event::Closed)
            {
                window.close();
                isOpen = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y))
            {
                window.close();
                isOpen = false;
            }
               
        }
        // deltaTime
        sf::Time deltaTime = clockGraph.restart();
        float dt = deltaTime.asSeconds();

        // elapsed time since window opened
        float elapsedTime = totalElapsedTime.getElapsedTime().asSeconds();

        //аppend new point
        float y = *Theta;
        graph.append(sf::Vertex(toScreen(elapsedTime, y), sf::Color::Blue));
        
        sf::Vector2f toscreenVectorElliptic = sf::Vector2f(ToScreenEllipse(*Theta, *angularVel));
        
        
        
        ODEgraph.append(sf::Vertex(toscreenVectorElliptic, sf::Color::Green));
        
        ODEpoint.setRadius(3.f);
        ODEpoint.setOrigin(3.f, 3.f);
        ODEpoint.setPosition(ToScreenEllipse(*Theta, *angularVel));
        ODEpoint.setFillColor(sf::Color(1, 50, 32));
        
//energy stuff
        initAgnularVel = 0.f;
        
        float d = *damping;
        
        float w = *angularVel;
        float leng = *length;
        float h = leng-(leng*cos(y));
        float PotEnergy = m*g*h;
        float Velocity =w*leng;
        float KinEnergy = m*pow(Velocity, 2)/2;
        
        
        //Energy Bar Chart
        
        
        KinEnergyHeight = KinEnergy*3;
        PotEnergyHeight = PotEnergy*3;
        
        KinEnergyBar.setFillColor(sf::Color::Green);
        PotEnergyBar.setFillColor(sf::Color::Red);
        
        KinEnergyBarVec = sf::Vector2f(barWidth, KinEnergyHeight);
        PotEnergyBarVec = sf::Vector2f(barWidth, PotEnergyHeight);
        
        KinEnergyBar.setSize(KinEnergyBarVec);
        PotEnergyBar.setSize(PotEnergyBarVec);
        
        
        KinEnergyBar.setOrigin(40, KinEnergyHeight);
        PotEnergyBar.setOrigin(40 ,PotEnergyHeight);
        
        KinEnergyBar.setPosition(500.f, 657.f);
        PotEnergyBar.setPosition(550.f, 657.f);
    
        
        //Pause button
        
        if(abs(*angularVel) > initAgnularVel)
            initAgnularVel = *angularVel;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
        {
            float t = *angularVel;
            *angularAcc = 0.f;
            *angularVel = t;
        }
        
        //Energy Max
        
        EnergyBarMax.setSize(sf::Vector2f(30.f, 1.f));
        EnergyBarMax.setPosition(440.f, 657.f-(m*(pow(initAgnularVel*leng, 2)/2)+m*g*h)*3);
        EnergyBarMax.setFillColor(sf::Color(128, 128, 128));
        
        
        
        
        //trace of graph
        float scaleX = WIDTH / 12;
        float scaleY = HEIGHT / (1 * M_PI);
        float maxtheta=0.f;
        maxtheta=((*Theta)*scaleY);
        maxTheta.setPosition(32.f, 119.f-(maxtheta));
        maxTheta.setSize(sf::Vector2f(0.f+scaleX*elapsedTime, 2.f));
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        {
            graph.clear();
            ODEgraph.clear();
        }
        
        //energygraph
    /*
        graphPotEnergy.append(sf::Vertex(ToScreenEnergy(elapsedTime, PotEnergy), sf::Color::Red));
        graphKinEnergy.append(sf::Vertex(ToScreenEnergy(elapsedTime, KinEnergy), sf::Color::Green));
    */
        //reset graph every 13 seconds
        if (elapsedTime > 13.f)
        {
            graph.clear();
            totalElapsedTime.restart(); //rset elapsed
        }
    }
}

void additional::update()
{
    if (isOpen)
    {
        window.clear(sf::Color::White);
        window.draw(background);
      //d  window.draw(axisX);
        window.draw(axisY);
        window.draw(maxTheta);
     //   window.draw(minTheta);
       // window.draw(graphKinEnergy);
       // window.draw(graphPotEnergy);
        window.draw(graph);
        window.draw(PotEnergyBar);
        window.draw(KinEnergyBar);
        window.draw(EnergyBarMax);
        window.draw(ODEgraph);
        window.draw(ODEpoint);
        window.display();
        
    }
}

bool additional::getStatus()
{
    return isOpen;
}
