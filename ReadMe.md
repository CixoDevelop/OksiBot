# OksiBot

### Po polsku

Oksi bot to robot naukowy stworzony na potrzeby nauki REST api. Api zostało zaimplementowane w C++ za pomocą httplib, posiada następujące endpointy:

 * /platform/move (PUT side=(front, back, frontLeft, frontRight, backLeft, backRight, rotateLeft, rotateRight, stand) time=(opcjonalny, czas w milisekundach)) - porusza robotem przez określony czas lub w nieskonczoność
 * /platform/stop (GET) - zatrzymuje robota
 * /platform/getSide (GET) - zwraca aktualny kierunek
 
 * /camera/rotate (PUT side=(left, right) how_many=(stopnie obrotu)) - obraca ramieniem kamery
 * /camera/getRotate (GET) - zwraca aktualne położenie kamery
 
### In english

Oksi bot is a scientific robot created for the needs of REST api learning. Api was implemented in C ++ using httplib, it has the following endpoints:

 * /platform/move (PUT side=(front, back, frontLeft, frontRight, backLeft, backRight, rotateLeft, rotateRight, stand) time=(optional, time in milliseconds)) - moves the robot for a specified period of time or indefinitely
 * /platform/stop (GET) - stops the robot
 * /platform/getSide (GET) - returns the current direction
 
 * /camera/rotate (PUT side=(left, right) how_many=(degrees of rotation)) - rotates the camera arm
 * /camera/getRotate (GET) - returns the current position of the camera
