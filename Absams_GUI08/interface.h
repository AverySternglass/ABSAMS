#ifndef INCLUDED_Interface_h
#define INCLUDED_Interface_h

#include "absamsV3.3\Simulation\Simulation.hpp"

static Assembly *appendage;
static Command *command;
static Simulation *sim;




#include <GL/gl.h>
#include <GL/glut.h>
/*xg========
GLint gFramesPerSecond2 = 0;


void FPS2(void){
	static GLint Frames = 0;
	static GLuint Clock;
	static GLuint PreviousClock = 0;
	static GLuint NextClock = 0;

	++Frames;
	Clock = glutGet(GLUT_ELAPSED_TIME);
	if(Clock < NextClock)
		return;

	gFramesPerSecond2 = Frames/1;
	PreviousClock = Clock;
	NextClock = Clock+1000;

	Frames = 0;

}


//exg========*/

static void mainDisplay(void)
{
	//display();
	sim->display();
	//SaveImageAs("test1.bmp");
}

static void mainKeyboardFunction1(int key, int x, int y)
{
	//xg
	//sim->onKeyPress1(key,x,y);
	sim->onKeyPress(key,x,y);
}

static void mainKeyboardFunction2(unsigned char key, int x, int y)
{
	//xg
	//sim->onKeyPress2(key,x,y);
	sim->onKeyPress(key,x,y);
}

static void mainWindowFunction(int width, int height)
{
	sim->reshapeWindow(width, height);
}

/*
static int ri;

void timer(int){
	glutPostRedisplay();
	glutTimerFunc(1000/60, timer, 0);
}
*/

static void mainSimulationLoop(void)
{

	sim->simulate();

	//xg
	
	//ri=1000/60;
	//glutPostRedisplay();
	//glutTimerFunc(1000/60, timer, 0);
		
}


static void processMouse(int button, int state, int x, int y)
{

	sim->onMouseClick(button, state, x, y);
		
}

#endif