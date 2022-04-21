#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


class Customrectangleshape : public sf::RectangleShape
{
public:
    Customrectangleshape(sf::Vector2f size,sf::Vector2f position)
                         : sf::RectangleShape (size),position_(position){
                         setPosition(position_);
    }

    sf::Vector2f  position(){ return position_ ;}

    void setSpeed(int y_vel){
                y_vel_ = y_vel;
    }



    // bounds of window
    void setBounds(int top,int bottom){
        bottom_ = bottom;
        top_ = top;

    }
    //bounce of a ball
    void bounce(float top,float height){
                        //top
                        if((top < 0.f) ){
                            y_vel_ = abs(y_vel_);

                        }
                        //bottom
                        if(top+height > 600){
                            y_vel_ = -abs(y_vel_);

                        }

    }

    // Move of pads

    //right
    void moveInDirectionright(const sf::Time &elapsed){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)  && rectangle_bounds.top > 0){
            move(0,-abs(y_vel_)*elapsed.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  && rectangle_bounds.top+rectangle_bounds.height <600){
            move(0,abs(y_vel_)*elapsed.asSeconds());
        }
    }
    //left
    void moveInDirectionleft(const sf::Time &elapsed){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)  && rectangle_bounds.top > 0){
            move(0,-abs(y_vel_)*elapsed.asSeconds());
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)  && rectangle_bounds.top+rectangle_bounds.height <600){
            move(0,abs(y_vel_)*elapsed.asSeconds());
        }
    }




private:

sf::Vector2f position_;

float top_;
float bottom_ ;


int y_vel_ = 0;
int x_vel_ = 0;

};

