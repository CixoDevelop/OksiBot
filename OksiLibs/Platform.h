/*
 * This file stores the class that is responsible for representing the entire
 * robot chassis. It also allows him to move in a given direction, also for
 * a given amount of time
 *
 * Autor: Cixo
 */

#include <unistd.h>
#include <string>

using namespace std;

#include "Engine.h"

#pragma once

class Platform{
    /*
     * The class responsible for the representation of the robot in the program
     * allows it to move in any direction also for a given amount of time
     */

    public:

        /* Constructor */
            Platform(Engine &left, Engine &right)
                :left(left), right(right)
        {
            /*
             * This function creates an object in the program and stops the
             * motors, which is the default
             */

            stop();
        }

        void 
            moveInTime(string direction, unsigned int time)
        {
            /*
             * It allows the robot to move to the selected side for a given 
             * amount of time in miliseconds
             */

            move(direction);
            usleep(time * 1000U);
            stop();
        }

        void 
            stop()
        {
            /*
             * Stops the robot in place
             */

            left.stop();
            right.stop();

            side = "stand";
        }

        void 
            move(string direction)
        {
            /*
             * It allows the robot to move in the selected direction, given in
             * the parameter as a string. Possible directions are:
             * - "front", 
             * - "back", 
             * - "frontLeft", 
             * - "frontRight", 
             * - "backLeft", 
             * - "backRight", 
             * - "rotateLeft", 
             * - "rotateRight",
             * - "stand". 
             * If something else is given, the robot will stop
             */

            side = direction;

            if(direction == "front"){
                left.start(FRONT);
                right.start(FRONT);

                return;
            }

            if(direction == "back"){
                left.start(BACK);
                right.start(BACK);

                return;
            }

            if(direction == "frontLeft"){
                left.stop();
                right.start(FRONT);

                return;
            }

            if(direction == "frontRight"){
                left.start(FRONT);
                right.stop();

                return;
            }

            if(direction == "backLeft"){
                left.stop();
                right.start(BACK);

                return;
            }

            if(direction == "backRight"){
                left.start(BACK);
                right.stop();

                return;
            }

            if(direction == "rotateLeft"){
                left.start(BACK);
                right.start(FRONT);
            
                return;
            }

            if(direction == "rotateRight"){
                left.start(FRONT);
                right.start(BACK);

                return;
            }

            stop();
        }

        string
            getSide()
        {
            /*
             * This function returns the direction in which the platform
             * is currently moving.
             */

            return side;
        }

    private:

        Engine left;
        Engine right;
        string side;
};
