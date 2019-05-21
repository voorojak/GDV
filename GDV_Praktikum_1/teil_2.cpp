// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <GL/SOIL.h>
#include <Windows.h>
#include "Car.h"


float angle = 0;
Car* mycar1;
GLUquadric* quad;
GLuint groundTexture;

void Init()	
{
	GLfloat light_ambient[] =
	{ 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] =
	{ 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] =
	{ 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] =
	{ 1.0, 1.0, 1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);


	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	quad = gluNewQuadric();
	groundTexture = SOIL_load_OGL_texture("Textures/boden.jpg", 
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS
		| SOIL_FLAG_INVERT_Y
		| SOIL_FLAG_NTSC_SAFE_RGB
		| SOIL_FLAG_COMPRESS_TO_DXT);
	glBindTexture(GL_TEXTURE_2D, groundTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // Hier finden jene Aktionen statt, die zum Programmstart einmalig 
   // durchgeführt werden müssen
	mycar1 = new Car(true, 0.0, 0.4, 1.0);

}

void RenderScene() //Zeichenfunktion
{
	glClearColor(1.0, 0.6, 0, 1.0);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen

	gluLookAt(mycar1->getX(), 1, mycar1->getY(), 0., 0., 1., 0., 1., 0.);
	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glPushMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON); //GL_QUADS
	glNormal3f(0, 1, 0);
	glTexCoord2f(0,1);
	glVertex3f(-5, -1, -5.);
	glTexCoord2f(0,0);
	glVertex3f(5, -1, -5.);
	glTexCoord2f(1,0);
	glVertex3f(5, -1, 5.);
	glTexCoord2f(1,1);
	glVertex3f(-5, -1, 5.);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//mycar1->moveCar(0.1);
	mycar1->generateCar();

	glPopMatrix();

	glutSwapBuffers();
}

void Reshape(int width,int height)
{
	// Matrix für Transformation: Frustum->viewport 
	glMatrixMode(GL_PROJECTION); 
	// Aktuelle Transformations-Matrix zuruecksetzen 
	glLoadIdentity ();
	// Viewport definieren 
	glViewport(0,0,width,height); 
	// Frustum definieren (siehe unten) 
	glOrtho( -4., 4., -4., 4., 0.0, 20.0); 
	// Matrix für Modellierung/Viewing 
	glMatrixMode(GL_MODELVIEW);
   // Hier finden die Reaktionen auf eine Veränderung der Größe des 
   // Graphikfensters statt
}

void Animate (int value)    
{
	if (GetAsyncKeyState('A')) {
		mycar1->turnCar(6.0f);
	}
	if (GetAsyncKeyState('D')) {
		mycar1->turnCar(-6.0f);
	}
	if (GetAsyncKeyState('K')) {
		mycar1->moveCar(0.2f);
	}
	if (GetAsyncKeyState('L')) {
		mycar1->moveCar(0.2f);
	}
	if (GetAsyncKeyState('W')) {
		mycar1->moveCar(0.05f);
	}
	if (GetAsyncKeyState('S')) {
		mycar1->moveCar(-0.05f);
	}


	
	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
   //std::cout << "value=" << value << std::endl;
   // RenderScene aufrufen
   glutPostRedisplay();
   // Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
   int wait_msec = 10;
   glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
   glutInit( &argc, argv );                // GLUT initialisieren
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
   glutInitWindowSize( 1000, 1000);         // Fenster-Konfiguration
   glutCreateWindow( "Name_1; Name_2" );   // Fenster-Erzeugung
   glutDisplayFunc( RenderScene );         // Zeichenfunktion bekannt machen
   glutReshapeFunc( Reshape );
   // TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
   glutTimerFunc( 10, Animate, 0);
   Init();
   glutMainLoop();
   return 0;
}
