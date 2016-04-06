//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Accessories.hpp
// Does all the GLUT handling, Simulation handling etc.
//========================================================================


void initialize(void);
void fly (void);
void create_shape(void);
void display(void);
void reshape (int w, int h);
void Key2(int, int, int);

static GLfloat vdata[27][3];

float shape_coord[2]={0.0f};

enum SIM_STATE
{
	SIM_PRERUN,
	SIM_RUN,
	SIM_PAUSE,
	SIM_STOP
} simState;

double elapsedTime = 0;
double lastDisplay = 0;


void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glutIdleFunc(fly);
}	

void display(void)
{
	char title[80];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch(simState)
	{
	case SIM_PRERUN:
		sprintf(title, "Surface Animation    Press F1 to Start") ;
		break;
	case SIM_PAUSE:
		sprintf(title, "Surface Animation    F1 - Continue F3 - Stop    time = %f ",elapsedTime  ) ;
		break;
	case SIM_RUN:
		sprintf(title, "Surface Animation    F2 - Pause F3 - Stop    time = %f ",elapsedTime  ) ;
		break;
	}

	glutSetWindowTitle(title);
	glLoadIdentity();
	glPushMatrix();
		glRotatef(shape_coord[0], 1.0f, 0.0f, 0.0f);
		glRotatef(shape_coord[1], 0.0f, 0.0f, 1.0f);
		glTranslatef(-60, -70 , 0);
		create_shape();
	glPopMatrix();
	glutSwapBuffers();
}

void create_shape(void)
{
	
}

void reshape (int w, int h)
{
	GLfloat nRange = 80.0f;

	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


    if (w <= h) 
		glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    else 
		glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}



void Key2(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
			shape_coord[1] -= 5.0;
			break;

		case GLUT_KEY_RIGHT:	
			shape_coord[1] += 5.0;
			break;

		case GLUT_KEY_UP:	
			shape_coord[0] -= 5.0;
			break;
			
		case GLUT_KEY_DOWN:	
			shape_coord[0] += 5.0;
			break;

		case GLUT_KEY_F1:
			simState = SIM_RUN;
			break;

		case GLUT_KEY_F2:
			simState = SIM_PAUSE;
			break;
			
		case GLUT_KEY_F3:
			simState = SIM_STOP;
			break;
	}
	glutPostRedisplay();	
}


void fly (void)
{
	if (simState == SIM_RUN)
	{
		elapsedTime += g_stepSize;

		if( elapsedTime >= 0.0001 && flag == 0 && elapsedTime <= 0.0002)
		{
			node7.setExternalForce(ext1);
			flag = 1;
		}
		if( elapsedTime >= 0.003 && flag == 1)
		{
			node7.setExternalForce(Vector(0,0,0));
			flag = 0;
		}
		d_assembly->update()
	}

	if(elapsedTime - lastDisplay >= g_displayStep)
	{
		glutPostRedisplay();	/* force update of the display */
		lastDisplay = elapsedTime;
	}
	
	if(simState == SIM_STOP)
	{
		//fclose(fptr);
		exit(0);
	}
}


int main()
{

	
	node1.updateNode();
	node2.updateNode();
	node3.updateNode();
	node4.updateNode();

	node1.relocateNode();
	node2.relocateNode();
	node3.relocateNode();
	node4.relocateNode();
	//spring1.updateSpring();
	//cout << spring1.getForce() << endl;
	myCylinder1.setRadialCommandForce(command);
	//myCylinder2.setRadialCommandForce(188.5);

	//myCylinder1.setModel(2);

	simState = SIM_PRERUN;
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE );
	glutInitWindowSize (1000, 600);
	glutInitWindowPosition (10, 10);
	glutCreateWindow ("Surface Animation : Press F1 to Start Simulation");
	//fptr = fopen("onecyl.txt", "w");
	init ();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutSpecialFunc(Key2);
	glutMainLoop();
	
	return 0;
}




