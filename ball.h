#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

template <typename T>
std::string toString(T arg, T arg1 )
{
    std::stringstream ss;
    ss << arg << " : " << arg1;
    return ss.str();
}

class Ball : public sf::CircleShape
{
public:
    Ball(float setRadius,sf::Vector2f position)
        : sf::CircleShape (setRadius),position_(position){
        setPosition(position_);
    }

        sf::Vector2f  position(){ return position_ ;}

        //speed of ball
        void setSpeed(int x_vel,int y_vel){
                    y_vel_ = y_vel;
                    x_vel_ = x_vel;
        }

        //move of a ball
        void animate(const sf::Time elapsed){

                    move(x_vel_*elapsed.asSeconds(),y_vel_*elapsed.asSeconds());
        }


        //window bounds
        void setBounds(int left,int right,int top,int bottom){
            bottom_ = bottom;
            top_ = top;
            left_ = left;
            right_ = right;
        }


        // window bounce
        void bounce(float top,float height){
                            //top
                            if((top < 0.f) ){
                                y_vel_ = std::abs(y_vel_);
                            }
                            //bottom
                            if(top+height > 600){
                                y_vel_ = -std::abs(y_vel_);
                            }

        }

        //goal
        void goal(float left, float width,sf::Sound &sound){

            //right
            if(left+ width > 800){

                sound.play();
                system( "cls");
                setPosition(400.0,300.0);
                g_left_ ++;
                setSpeed(0,0);
            }
            //left
            if(left < 0.f){

                sound.play();
                system( "cls");
                setPosition(400.0,300.0);
                g_right_ ++;
                setSpeed(0,0);                
            }

        }

        //collisions

            //bounds of pads
            void setPadsBounds(int left,int right){
            left_pad_bound_ = left;
            right_pad_bound_ = right;
            }


            //end of game
            void game_over (sf::RenderWindow &window,sf::Sound &sound)
            {
                if (g_right_ == 5 ||g_left_ == 5){
                    window.close();

                    sound.play();
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << std::endl;
                    std::cout << "                                                     GAME OVER" << std::endl;
                    std::cin.get();
                }
            }

//            if (ball.show_score_l(left_goal) == 5 || ball.show_score_r(right_goal) == 5 ){
//                ;
//                window.draw(end);
//            }


            int show_score_l (int g_left){
                g_left = g_left_;
                return g_left;

            }
            int show_score_r (int g_right){
                g_right = g_right_;
                return g_right;

            }



private:


        void game_over();
        void bounce();

        sf::Vector2f position_;

        int g_right_ = 0;
        int g_left_ = 0;

        float top_;
        float bottom_ ;
        float left_;
        float right_;

        int right_bound_;
        int left_bound_;

        int right_pad_bound_;
        int left_pad_bound_;

        int y_vel_ = 0;
        int x_vel_ = 0;
};
