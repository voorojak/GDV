// GD-Praktikum:   teil_1.cpp  (Teil 1: Start-Programm)
// Hergenroether / Groch    Last Update: 05.07.2014

#include <iostream> 
#include <GL/freeglut.h>         //lädt alles für OpenGL
#include <chrono>

GLfloat X = -1;
GLfloat Y = 0;
GLfloat Z = 0;
bool movingXright = true;
bool movingYup = true;
float angle = 0;

void Init()
{
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	// Hier finden jene Aktionen statt, die zum Programmstart einmalig 
	// durchgeführt werden müssen
}

void RenderScene() //Zeichenfunktion
{
	glClearColor(1.0, 0.6, 0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Hier befindet sich der Code der in jedem Frame ausgefuehrt werden muss
	glLoadIdentity();   // Aktuelle Model-/View-Transformations-Matrix zuruecksetzen
	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(X, Y, Z);
	glBegin(GL_POLYGON);
	glColor4f(0.0, 1.0, 0.0, 1.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -1.0);
	glVertex3f(0.5, 0.5, -1.0);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex3f(-0.5, 0.5, -1.0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glutSwapBuffers();
}

void Reshape(int width, int height)
{
	// Matrix für Transformation: Frustum->viewport 
	glMatrixMode(GL_PROJECTION);
	// Aktuelle Transformations-Matrix zuruecksetzen 
	glLoadIdentity();
	// Viewport definieren 
	glViewport(0, 0, width, height);
	// Frustum definieren (siehe unten) 
	glOrtho(-1., 1., -1., 1., 0.1, 1.9);
	// Matrix für Modellierung/Viewing 
	glMatrixMode(GL_MODELVIEW);
	// Hier finden die Reaktionen auf eine Veränderung der Größe des 
	// Graphikfensters statt
}

void Animate(int value)
{
	if (movingXright) {
		X += 0.01;
		if (X >= 1) movingXright = false;
	}
	else {
		X -= 0.01;
		if (X <= -1) movingXright = true;
	}

	if (movingYup) {
		Y += 0.01;
		if (Y >= 1) movingYup = false;
	}
	else {
		Y -= 0.01;
		if (Y <= -1) movingYup = true;
	}

	angle += 0.1;


	// Hier werden Berechnungen durchgeführt, die zu einer Animation der Szene  
   // erforderlich sind. Dieser Prozess läuft im Hintergrund und wird alle 
   // 1000 msec aufgerufen. Der Parameter "value" wird einfach nur um eins 
   // inkrementiert und dem Callback wieder uebergeben. 
	std::cout << "value=" << value << std::endl;
	// RenderScene aufrufen
	glutPostRedisplay();
	// Timer wieder registrieren - Animate wird so nach 10 msec mit value+=1 aufgerufen.
	int wait_msec = 10;
	glutTimerFunc(wait_msec, Animate, ++value);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);                // GLUT initialisieren
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);         // Fenster-Konfiguration
	glutCreateWindow("Name_1; Name_2");   // Fenster-Erzeugung
	glutDisplayFunc(RenderScene);         // Zeichenfunktion bekannt machen
	glutReshapeFunc(Reshape);
	// TimerCallback registrieren; wird nach 10 msec aufgerufen mit Parameter 0  
	glutTimerFunc(10, Animate, 0);
	Init();
	glutMainLoop();
	return 0;
}
