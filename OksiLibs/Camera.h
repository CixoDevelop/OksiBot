/*
 * This file stores the library responsible for controlling the camera arm.
 *
 * Autor: Cixo
 */

#include <pigpio.h>
#include <string>

using namespace std;

#pragma once

class SaveRange{
	/*
	 * This class is responsible for the zone in which the camera can move,
	 * it will not allow the camera arm to move too left or right
	 */

	public:

		/* Constructor */
			SaveRange(int left, int right)
		{
			/*
			 * Creates an object at the same time lead to a situation where
			 * the value of the right is greater (valid range)
			 */

			if(left > right){
				this->left = left;
				this->right = right;
			}else{
				this->left = right;
				this->right = left;
			}
		}

		int 
			getMiddle()
		{
			/*
			 * This function determines and returns the center of the set range
			 */

			return this->right + ((this->left - this->right) / 2);
		}

		int 
			checkRange(int position)
		{
			/*
			 * This function is a function that normalizes the range in which 
			 * the camera arm can be set, give the desired position and this
			 * will return the value that is within the designated ranges
			 */

			if(position > this->left)
				return this->left;

			if(position < this->right)
				return this->right;

			return position;
		}

	private:
	
		int left;
		int right;
};

class Camera{
	/*
	 * This class is responsible for the representation of the camera arm in 
	 * the program. He is responsible for its positions and will keep the 
	 * frame within maximum limits
	 */

	public:

		/* Constructor */
			Camera(int camera_pin, SaveRange save_range)
				:camera_pin(camera_pin), save_range(save_range)
		{
			/*
			 * This function takes as a parameter the GPIO pin to which the
			 * servo with the camera arm is connected and the SaveRange in 
			 * which the camera can move
			 */

			if(
				camera_pin == 18 or
				camera_pin == 19
			)
				gpioSetMode(camera_pin, PI_ALT5);
			else
				gpioSetMode(camera_pin, PI_ALT0);

			this->position = this->save_range.getMiddle();
			this->updatePosition();
		}

		/* Destructor */
			~Camera()
		{
			/*
			 * Free up resources in the form of the previously set GPIO pin
			 * when cleaning the camera object
			 */

			gpioSetMode(camera_pin, PI_INPUT);
		}

		void 
			rotate(int how_many, string side)
		{
			/*
			 * This function rotates the camera arm by a given position, 
			 * enter the value by which the camera should be rotated and
			 * the page in the form "left" or "right"
			 */

			/* If left then add, else substract */
			if(side == "right")
				how_many = -how_many;

			this->position = this->save_range.checkRange(this->position + how_many);
			this->updatePosition();
		}

		void 
			updatePosition()
		{
			/*
			 * This function sets the current camera position stored in
			 * memory on the servo
			 */

			gpioServo(this->camera_pin, this->position);
		}

		int 
			getRotate()
		{
			/*
			 * This function returns the current camera position from memory
			 */

			return this->position;
		}

	private:

		int camera_pin;
		int position;
		SaveRange save_range;

};
