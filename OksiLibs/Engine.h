/*
 * This file stores the class needed to control the robot's motors
 *
 * Autor: Cixo
 */

#include <pigpio.h>

#pragma once

enum Direction{
	/*
	 * This enum is responsible for the direction in which the motor rotates
	 */

	FRONT,
	BACK,
	STOP
};

class Engine{
	/*
	 * This class is responsible for storing and representing the engine in the
	 * program. It allows you to start it in any direction as well as stop. 
	 * During creation it will automatically set GPIO pins and restore these 
	 * pins after destruction
	 */

	public:

		/* Constructor */
			Engine(int pin_a, int pin_b)
				:pin_a(pin_a), pin_b(pin_b)
		{
			/*
			 * This function creates an object in memory, rewrites the given 
			 * values, and sets the GPIO pins accordingly
			 */

			gpioSetMode(pin_a, PI_OUTPUT);
			gpioSetMode(pin_b, PI_OUTPUT);

			stop();
		}

		/* Destructor */
			~Engine()
		{
			/*
			 * This function restores the GPIO pins to the state they were in 
			 * before the creation of this object
			 */

			gpioSetMode(pin_a, PI_INPUT);
			gpioSetMode(pin_b, PI_INPUT);
		}

		void 
			start(Direction direction)
		{
			/*
			 * The function starts the motor by setting the direction of 
			 * rotation given in the parameter
			 */

			stop();

			if(direction == FRONT){
				gpioWrite(pin_a, 1);

				return;
			}

			if(direction == BACK){
				gpioWrite(pin_b, 1);

				return;
			}
		}

		void 
			stop()
		{
			/*
			 * This function stops the engine rotation
			 */

			gpioWrite(pin_a, 0);
			gpioWrite(pin_b, 0);
		}

		Direction 
			getDirection()
		{
			/*
			 * This function returns the current direction of rotation 
			 * of the motor
			 */
			 
			if(gpioRead(pin_a) == 1)
				return FRONT;

			if(gpioRead(pin_b) == 1)
				return BACK;

			return STOP;
		}

	private:

		int pin_a, pin_b;
};
