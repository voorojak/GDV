/*
    wuerfel.cpp definiert einen Würfel über seine 6 Seiten
    Last Update:  13.10.2011   W.-D. Groch
*/ 

#define _USE_MATH_DEFINES

#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
#include "Car.h"

void Car::generateCar()
{ 

	glTranslatef(currentPosition.xPos, 0, currentPosition.yPos);

	glRotatef(currentPosition.directionAngle, 0, 1, 0);
	glRotatef(90, -1, 0, 0);

	//RenderTheBody
	glBegin(GL_POLYGON);   //Unterboden
	glNormal3f(0, 0, 1);
	glColor4f(R,G,B,1.0f);	
	glVertex3f(-carLength, carWidth,0.0f);
	glVertex3f(carLength, carWidth,0.0f);
	glVertex3f(carLength,-carWidth,0.0f);
	glVertex3f(-carLength,-carWidth,0.0f);
	glEnd();

	glBegin(GL_POLYGON);   //TopOfBotHalf
	glNormal3f(0, 0, 1);
	glColor4f(R, G, B, 1.0f);
	glVertex3f(-carLength, carWidth, carHeight);
	glVertex3f(carLength, carWidth, carHeight);
	glVertex3f(carLength, -carWidth, carHeight);
	glVertex3f(-carLength, -carWidth, carHeight);
	glEnd();

	glBegin(GL_POLYGON);	//OneSide
	glColor4f(R, G, B, 1.0f);
	glVertex3f(-carLength, carWidth, 0.0f);
	glVertex3f(carLength, carWidth, 0.0f);
	glVertex3f(carLength, carWidth, carHeight);
	glVertex3f(-carLength, carWidth, carHeight);
	glEnd();

	glBegin(GL_POLYGON);	//OneSideTop

	glVertex3f(-carLength * 0.2, carWidth, carHeight + 0.0f);
	glVertex3f(carLength, carWidth, carHeight + 0.0f);
	glVertex3f(carLength - carLength * 0.2, carWidth, carHeight + carHeight);
	glVertex3f(0, carWidth, carHeight + carHeight);
	glEnd();

	glBegin(GL_POLYGON);	//OtherSide
	glColor4f(R, G, B, 1.0f);
	glVertex3f(-carLength, -carWidth, 0.0f);
	glVertex3f(carLength, -carWidth, 0.0f);
	glVertex3f(carLength, -carWidth, carHeight);
	glVertex3f(-carLength, -carWidth, carHeight);
	glEnd();

	glBegin(GL_POLYGON);	//OtherSideTop

	glVertex3f(-carLength * 0.2, -carWidth, carHeight + 0.0f);
	glVertex3f(carLength, -carWidth, carHeight + 0.0f);
	glVertex3f(carLength - carLength * 0.2, -carWidth, carHeight + carHeight);
	glVertex3f(0, -carWidth, carHeight + carHeight);
	glEnd();

	glBegin(GL_POLYGON);	//RearWindow
	glColor4f(0.2, 0.2, 0.2, 0.1);	
	glVertex3f(carLength, -carWidth, carHeight + 0.0f);
	glVertex3f(carLength - carLength * 0.2, -carWidth, carHeight + carHeight);
	glVertex3f(carLength - carLength * 0.2, carWidth, carHeight + carHeight);
	glVertex3f(carLength, carWidth, carHeight + 0.0f);
	glEnd();
	
	glBegin(GL_POLYGON);	//FrontWindow
	glColor4f(0.2, 0.2, 0.2, 0.1);
	glVertex3f(-carLength * 0.2, -carWidth, carHeight + 0.0f);
	glVertex3f(0, -carWidth, carHeight + carHeight);
	glVertex3f(0, carWidth, carHeight + carHeight);
	glVertex3f(-carLength * 0.2, carWidth, carHeight + 0.0f);
	glEnd();


	glBegin(GL_POLYGON);	//Roof
	glNormal3f(0, 0, 1);
	glColor4f(R, G, B, 1.0f);
	glVertex3f(carLength - carLength * 0.2, -carWidth, carHeight + carHeight);
	glVertex3f(0, -carWidth, carHeight + carHeight);
	glVertex3f(0, carWidth, carHeight + carHeight);
	glVertex3f(carLength - carLength * 0.2, carWidth, carHeight + carHeight);
	glEnd();


	glBegin(GL_POLYGON);   //FrontSide
	glColor4f(R, G, B, 1.0f);
	glVertex3f(carLength, -carWidth, 0.0f);
	glVertex3f(carLength, carWidth, 0.0f);
	glVertex3f(carLength, carWidth, carHeight);
	glVertex3f(carLength, -carWidth, carHeight);
	glEnd();

	glBegin(GL_POLYGON);   //FrontSide
	glColor4f(R, G, B, 1.0f);
	glVertex3f(-carLength, -carWidth, 0.0f);
	glVertex3f(-carLength, carWidth, 0.0f);
	glVertex3f(-carLength, carWidth, carHeight);
	glVertex3f(-carLength, -carWidth, carHeight);
	glEnd();
	
	//Lights Front
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glRotatef(90, 0, 1, 0);
	glTranslatef(-carHeight / 2, -carWidth * 0.6 ,-carLength -0.05);
	glutSolidCylinder(carHeight / 2, 0.1, 7, 7);
	
	GLfloat light_specular[] =
	{ 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_specular);


	glTranslatef(0, carWidth*1.2, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_specular);


	glutSolidCylinder(carHeight / 2, 0.1, 7, 7);
	//Rear
	glPopMatrix();
	glPushMatrix();
	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, -carWidth * 0.6, carLength - 0.05);
	glutSolidCylinder(carHeight / 2, 0.1, 7, 7);
	glTranslatef(0, carWidth*1.2, 0);
	glutSolidCylinder(carHeight / 2, 0.1, 7, 7);
	glPopMatrix();

	//Render the Wheels
	glPushMatrix();
	glTranslatef(carLength * 0.6, carWidth + 0.05, 0); // 1 , 0.5
	generateWheel();
	glTranslatef(0, -carWidth * 2 , 0); // 1, -0.5
	generateWheel();
	glTranslatef(-carLength * 1.2, 0, 0); // -1, -0.5
	generateWheel();
	glTranslatef(0, carWidth * 2, 0); // -1, 0.5 
	generateWheel();
	glPopMatrix();

	return;
}

void Car::generateWheel() {
	glPushMatrix();
	glRotatef(90, 1.0, 0, 0);
	glRotatef(wheelAngle, 0, 0, 1);
	glColor4f(0.1f, 0.1f, 0.1f, 1.0f);	//GREY
	glutSolidCylinder(WheelDiameter, 0.1, 7, 7);
	glColor4f(1, 1, 1, 1); //WHITE
	glTranslatef(0, 0, -0.01);
	glutSolidCylinder(WheelDiameter / 2, 0.12, 7, 7);
	glPopMatrix();
}

void Car::moveCar(float distance) {

	float xDistance = 0 - (distance * std::cos(currentPosition.directionAngle * M_PI / 180));
	float yDistance = 0 - (distance * std::sin(currentPosition.directionAngle * M_PI / 180));

	currentPosition.xPos += xDistance;
	currentPosition.yPos -= yDistance;

	std::cout << "Xpos: " << currentPosition.xPos << "    Ypos: " << currentPosition.yPos << "   CurrAng: " << currentPosition.directionAngle << std::endl;

	if (distance > 0) {
		wheelAngle += 5;
	}
	else {
		wheelAngle -= 5;
	}

}

void Car::turnCar(float angle) {
	this->currentPosition.directionAngle += angle;
}