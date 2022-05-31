/*
 * This file stores the main API server for the oksi bot. It creates
 * representations of all controllable structures in the robot and provides
 * endpoints to them:
 *
 * - /platform/move (
 * --- PUT, 
 * --- side=(
 * ------ front, 
 * ------ back, 
 * ------ frontLeft, 
 * ------ frontRight, 
 * ------ backLeft, 
 * ------ backRight, 
 * ------ rotateLeft, 
 * ------ rotateRight, 
 * ------ stand
 * --- ),
 * --- time=(OPTIONAL, time in miliseconds)
 * - ) 
 * -- moves the robot in the indicated direction over time, 
 * -- or indefinitely if no time is given
 *
 * - /platform/stop (GET) 
 * -- Polling this endpoint will stop the robot in its place
 * 
 * - /platform/getSide (GET)
 * -- returns the current direction in which the robot is moving
 * 
 * - /camera/rotate (PUT, side=(left, right), how_many=(turnover value))
 * -- It will rotate the camera by the set value in the set direction
 * 
 * - /camera/getRotate (GET)
 * -- Returns the current position of the camera
 *
 * Autor: Cixo
 */

#include <iostream>
#include <string>
#include <pigpio.h>
#include <cstdlib>
#include <memory>

#include "OtherLibs/httplib.h"

#include "OksiLibs/Camera.h"
#include "OksiLibs/Engine.h"
#include "OksiLibs/Platform.h"

using namespace std;
using namespace httplib;

int main(){
	/* Start up GPIO */
	gpioInitialise();

	/* Create objects of hardware */
	Camera main_camera(12, SaveRange(2200, 800));
	Engine left_engine(14, 15);
	Engine right_engine(23, 24);
	Platform main_platform(left_engine, right_engine);

	/* Create REST server */
	Server server;

	/* Endpoints for camera*/
	server.Get("/camera/getRotate", [&](const Request &request, Response &response){
		response.set_content(to_string(main_camera.getRotate()), "text/plain");
	});
	server.Put("/camera/rotate", [&](const Request &request, Response &response){
		string side = "left";
		int how_many = 0;
		
		if(request.has_param("side"))
				side = request.get_param_value("side") ;

		if(request.has_param("how_many"))
			how_many = atoi(request.get_param_value("how_many").c_str());

		main_camera.rotate(how_many, side);
	});

	/* Endpoints for platform */
	server.Get("/platform/getSide", [&](const Request &request, Response &response){
		response.set_content(main_platform.getSide(), "text/plain");
	});
	server.Get("/platform/stop", [&](const Request &request, Response &response){
		main_platform.stop();
	});
	server.Put("/platform/move", [&](const Request &request, Response &response){
		if(!request.has_param("side"))
			return;
		
		if(request.has_param("time")){
			main_platform.moveInTime(
                request.get_param_value("side"), 
                atoi(request.get_param_value("time").c_str())
            );
			return;
		}

		main_platform.move(request.get_param_value("side"));
	});

	/* Initialise server */
	server.listen("0.0.0.0", 80);

	/* Stop GPIO */
	gpioTerminate();

	return 0;
}
