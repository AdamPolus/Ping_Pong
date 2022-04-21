#include "pinghead.h"
#include "ball.h"

#include <time.h>







int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(120);

    //variables
    sf::Clock clock;
    sf::Event event;
    int speed_of_pads = 550;
    std::vector<Customrectangleshape> pads;
    int speed_x = 0;
    int speed_y = 0;
    srand (time(NULL));
    int counter = 2;
    int left_goal = 0;
    int right_goal = 0;





    sf::Font font;
    // Load it from a file
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Font not loaded" << std::endl;
    }

    sf::Text end;
    end.setFont(font);
    end.setString("GAME OVER");
    end.setPosition(350.0,270.0);
    end.setScale(200.0,200.0);



    sf::Music music;
    if (!music.openFromFile("myszojelen.ogg"))
        return -1; // error
//    music.play();
    music.setLoop(true);
    music.setVolume(5.0);

    //oliwia

    sf::SoundBuffer oliwia;
        if (!oliwia.loadFromFile("oliwia.wav")){
            return -1;}

        sf::Sound sound;
        sound.setBuffer(oliwia);

    //rebi
        sf::SoundBuffer rebipanti;
            if (!rebipanti.loadFromFile("rebi.wav")){
                return -1;}

            sf::Sound pantera;
            pantera.setBuffer(rebipanti);

    //end
            sf::SoundBuffer koniec;
                if (!koniec.loadFromFile("lele.wav")){
                    return -1;}

                sf::Sound lolz;
                lolz.setBuffer(koniec);

     //goal
                sf::SoundBuffer gol;
                if (!gol.loadFromFile("goal.wav")){
                    return -1;}

                sf::Sound golik;
                golik.setBuffer(gol);






    // pads
    sf::Vector2f sizer(5.0, 50.0);
    sf::Vector2f positionr(780.0, 300.0);
    Customrectangleshape right_pad(sizer, positionr);
    right_pad.setSpeed(speed_of_pads);
    right_pad.setFillColor(sf::Color(0,191,255));

    sf::Vector2f sizel(5.0, 50.0);
    sf::Vector2f positionl(15.0, 300.0);
    Customrectangleshape left_pad(sizel, positionl);
    left_pad.setSpeed(speed_of_pads);
    left_pad.setFillColor(sf::Color(255,20,147));

    //ball
    float radius = 8.0;
    sf::Vector2f pos_of_ball(400.0,300.0);
    Ball ball(radius,pos_of_ball);
    ball.setSpeed(speed_x,speed_y);
    ball.setFillColor(sf::Color(186,85,211));



    // run the program as long as the window is open
    while (window.isOpen()) {
        //clock restart
        sf::Time elapsed = clock.restart();



        // check all the window's events that were triggered since the last iteration of the loop

        while (window.pollEvent(event)) {
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space && ball.getPosition() == sf::Vector2f(400.0,300.0)){
                    speed_y = rand() % 200 + 200;
                    speed_x = rand() % 200 + 200;


                    if(counter % 2 == 0){
                    ball.setSpeed(std::abs(speed_x),std::abs(speed_y));
                    counter ++;
                    }
                    else{
                        ball.setSpeed(-std::abs(speed_x),-std::abs(speed_y));
                        counter++;
                    }
                }

            }
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);


        sf::FloatRect right_pad_bounds = right_pad.getGlobalBounds();
        right_pad.setBounds(0,window.getSize().y);
        right_pad.bounce(right_pad_bounds.top,right_pad_bounds.height);
        right_pad.moveInDirectionright(elapsed);
        pads.emplace_back(right_pad);

        sf::FloatRect left_pad_bounds = left_pad.getGlobalBounds();
        left_pad.setBounds(0,window.getSize().y);
        left_pad.bounce(left_pad_bounds.top,left_pad_bounds.height);
        left_pad.moveInDirectionleft(elapsed);
        pads.emplace_back(left_pad);

        sf::FloatRect ball_bounds = ball.getGlobalBounds();
        ball.animate(elapsed);
        ball.setBounds(0, window.getSize().x, 0, window.getSize().y);
        ball.bounce(ball_bounds.top,ball_bounds.height);
        ball.goal(ball_bounds.left,ball_bounds.width,golik);

        //bounds of pads for ball
        ball.setPadsBounds(left_pad_bounds.left+left_pad_bounds.width,right_pad_bounds.left);

//            for (auto pad: pads)
//            {
//                sf::FloatRect pad_bounds = pad.getGlobalBounds();
                if (ball_bounds.left+ball_bounds.width >right_pad_bounds.left && ball_bounds.top < right_pad_bounds.top+right_pad_bounds.height && ball_bounds.top+ball_bounds.height > right_pad_bounds.top)
                {
                    sound.play();
                    speed_y = rand() % 200 + 300;
                    speed_x = rand() % 200 + 300;
                    ball.setSpeed(-std::abs(speed_x),-std::abs(speed_y));
//                    break;
                }
                if (ball_bounds.left < left_pad_bounds.left+left_pad_bounds.width && ball_bounds.top < left_pad_bounds.top+left_pad_bounds.height && ball_bounds.top+ball_bounds.height > left_pad_bounds.top)
                {
                    pantera.play();
                    speed_y = rand() % 200 + 300;
                    speed_x = rand() % 200 + 300;
                    ball.setSpeed(std::abs(speed_x),std::abs(speed_y));
//                    break;
                }




                sf::Text left_score(toString<int>(ball.show_score_l(left_goal),ball.show_score_r(right_goal)), font);
                left_score.setPosition(375.0, 5.0);




                ball.game_over(window,lolz);

        // draw everything here...
//        window.draw(back);
        window.draw(right_pad);
        window.draw(left_pad);
        window.draw(ball);
        window.draw(left_score);


        // end the current frame
        window.display();






    }

    return 0;
}
