#include <GL/freeglut.h>

struct carPos {
	float xPos = 0.0;
	float yPos = 0.0;

	float directionAngle = 0.0;
};


class Car
{
public:
	Car(float R, float G, float B ) : R(R), G(G), B(B){};
	Car(bool driving, float R, float G, float B) : driving(driving), R(R), G(G), B(B) {};
	void moveCar(float distance);
	void turnCar(float angle);
	float getX() { return currentPosition.xPos; }
	float getY() { return currentPosition.yPos; }
	void generateCar();
private:
	float R = 0.0;
	float G = 0.0;
	float B = 0.0;
	void generateWheel();
	bool driving = false;
	int wheelAngle = 0;

	float carLength = 0.6f;
	float carWidth = 0.3f;
	float carHeight = 0.1f;
	float WheelDiameter = 0.1f ;

	carPos currentPosition;
};