//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Simulation.cpp
// Implementation of the class Simulation.
//========================================================================  


#include "Simulation.hpp"
#include "bmp.hpp"
#include "CollisionResolve.cpp"



//============================================================
// Simulation::Simulation
//============================================================

Simulation :: Simulation(double simulationStep, Assembly *assembly, Command *commands)
			:c_isGraphicSimulation(false),
			 c_collisionDecimation (1),
			 c_displayDecimation (-1),
			 c_imageSaveDecimation (-1),
			 c_simulationStep (simulationStep),
			 c_loggingDecimation (1)
	// Copy Constructor
{
	d_collisionCycles = -1;
	d_displayCycles = -1;
	d_imageSaveCycles = -1;
	d_loggingCycles = -1;
	d_frameCount = 0;
	d_elapsedTime = 0.0;
	d_simulationAssembly = assembly;
	d_simulationCommands = commands;
	d_simState = SIM_PRERUN;
	for(int i = 0; i < 3; i++)
	{
		d_viewPoint[i] = 0.0f;
		d_viewAngle[i] = 0.0f;
	}
	d_collisionZoomFactor = g_collisionZoomFactor;
	d_displayZoomFactor = 1.0f;
	this->d_isInitialized = false;
	//xg
	for(int i = 0; i < 25; i++)
		d_actionPerformed[i] = false;
	
	d_objectList = new List<Object *>();
	d_shapeList = new List <GLShape *>();
	d_shapeHandleList = new List <DT_ShapeHandle>();
}


//============================================================
// Simulation::Simulation
//============================================================

Simulation :: Simulation(Assembly *assembly)
			:c_isGraphicSimulation(false),
			 c_collisionDecimation (1),
			 c_displayDecimation (-1),
			 c_imageSaveDecimation (-1),
			 c_simulationStep (-1),
			 c_loggingDecimation (-1)
	// Copy Constructor
{
	d_collisionCycles = -1;
	d_displayCycles = -1;
	d_imageSaveCycles = -1;
	d_loggingCycles = -1;
	d_frameCount = 0;
	d_elapsedTime = 0.0;
	d_simulationAssembly = assembly;
	d_simulationCommands = NULL;
	d_simState = SIM_EDIT;
	for(int i = 0; i < 3; i++)
	{
		d_viewPoint[i] = 0.0f;
		d_viewAngle[i] = 0.0f;
	}
	d_collisionZoomFactor = g_collisionZoomFactor;
	d_displayZoomFactor = 1.0f;
	this->d_isInitialized = false;
	//xg
	for(int i = 0; i < 25; i++)
		d_actionPerformed[i] = false;

	d_objectList = new List<Object *>();
	d_shapeList = new List <GLShape *>();
	d_shapeHandleList = new List <DT_ShapeHandle>();
}


//============================================================
// Simulation::Simulation
//============================================================

Simulation :: Simulation(double simulationStep, int collisionDecimation, int displayDecimation,
						 int imageSaveDecimation, int loggingDecimation, 
						 Assembly *assembly, Command *commands)
			:c_isGraphicSimulation(true),
			 c_collisionDecimation (collisionDecimation),
			 c_displayDecimation (displayDecimation),
			 c_imageSaveDecimation (imageSaveDecimation),
			 c_simulationStep (simulationStep),
			 c_loggingDecimation (loggingDecimation)
	// Copy Constructor
{
	d_collisionCycles = -1;
	d_displayCycles = -1;
	d_imageSaveCycles = -1;
	d_loggingCycles = -1;
	d_frameCount = 0;
	d_elapsedTime = 0.0;
	d_simulationAssembly = assembly;
	d_simulationCommands = commands;
	d_simState = SIM_PRERUN;
	for(int i = 0; i < 3; i++)
	{
		d_viewPoint[i] = 0.0f;
		d_viewAngle[i] = 0.0f;
	}
	d_collisionZoomFactor = g_collisionZoomFactor;
	d_displayZoomFactor = 1.0f;
	this->d_isInitialized = false;
	//xg
	for(int i = 0; i < 25; i++)
		d_actionPerformed[i] = false;

	d_objectList = new List<Object *>();
	d_shapeList = new List <GLShape *>();
	d_shapeHandleList = new List <DT_ShapeHandle>();
}


//============================================================
// Simulation::~Simulation
//============================================================

Simulation :: ~Simulation(){}
	// Default Destructor


//============================================================
// Simulation::saveImages
//============================================================

void Simulation :: saveImages(void)
	// Save an image if required
{
	char fileName[100];
	if(d_imageSaveCycles <= 0)
		{
			if(d_frameCount < 10) sprintf(fileName,"..//simulation output//frame0000%d.bmp",d_frameCount);
			else if(d_frameCount < 100) sprintf(fileName,"..//simulation output//frame000%d.bmp",d_frameCount);
			else if(d_frameCount < 1000) sprintf(fileName,"..//simulation output//frame00%d.bmp",d_frameCount);
			else if(d_frameCount < 10000) sprintf(fileName,"..//simulation output//frame0%d.bmp",d_frameCount);
			else sprintf(fileName,"frame%d.bmp",d_frameCount);
			SaveImageAs(fileName);
			d_frameCount++;
			d_imageSaveCycles = c_imageSaveDecimation;
		}
	// Decrement the number of cycles left before next image save
		d_imageSaveCycles--;
}

//============================================================
// Simulation::logData
//============================================================

void Simulation :: logData(void)
	// Log data if required
{
	int i;
	//static char fileName[30];
	static FILE *logFilePtr = fopen(logFileName,"w");
	
	if(d_loggingCycles <= 0)
		{
			if(d_loggingCycles == -1) // Print Header
			{
				fprintf(logFilePtr,"MHUs:\t%d\n",d_simulationAssembly->getNumMHUnits());
				fprintf(logFilePtr,"Time\t");
				for(i = 0; i < d_simulationAssembly->getNumMHUnits(); ++i)
					fprintf(logFilePtr,"Unit\tType\tDimension1\tDimension2\tDimension3\tLocationX\tLocationY\tLocationZ\t");
			}
			fprintf(logFilePtr,"\n");
			fprintf(logFilePtr,"%lf\t", d_elapsedTime);
			for(i = 0; i < d_simulationAssembly->getNumMHUnits(); ++i)
			{
				d_simulationAssembly->getMHUnit(i)->writeLogFile(d_elapsedTime,logFilePtr); 

			}
			fprintf(logFilePtr,"\n");
			d_loggingCycles = c_loggingDecimation;
		}
	// Decrement the number of cycles left before next log
		d_loggingCycles--;
}

//============================================================
// Simulation::updateSolid
//============================================================

void Simulation :: updateSolid(void)
	// Update Solid Objects
{
	int i;
	double qw,qx,qy,qz;
	Vector pos, solidPosition;

	for (i = 0; i < d_simulationAssembly->getNumMHUnits(); ++i) 
		{
			d_objectList->getElement(i).getData()->getMuscle()->getUnitQuaternion(&qw,&qx,&qy,&qz);
			
			pos = d_objectList->getElement(i).getData()->getMuscle()->getPosition();
			
			
			GLShape *temp1 = d_shapeList->getElement(i).getData();
			Muscle *musclePtr = d_objectList->getElement(i).getData()->getMuscle();
			
			if(musclePtr->getShape() == 1)
			{
				GLCylinder *tempGLCyl = (GLCylinder *) temp1;
				Cylinder *tempCyl = (Cylinder *)musclePtr;
				
				tempGLCyl->setRadius(d_collisionZoomFactor*(tempCyl->getRadius()));
				tempGLCyl->setHeight(d_collisionZoomFactor*tempCyl->getHeight());

				DT_ShapeHandle temp2 = d_shapeHandleList->getElement(i).getData();
				DT_Cylinder *temp3 = (DT_Cylinder *)temp2;
				temp3->setRadius(d_collisionZoomFactor*tempCyl->getRadius());
				temp3->setHeight(d_collisionZoomFactor*tempCyl->getHeight());

				solidPosition = pos;// - 0.5*tempCyl->getOrientation()*tempCyl->getHeight();
				solidPosition = d_collisionZoomFactor*solidPosition;
				d_objectList->getElement(i).getData()->reset(
					MT_Transform(MT_Quaternion(qx,qy,qz,qw), MT_Point3(solidPosition.getX(),solidPosition.getY(),solidPosition.getZ())));
			}

			if(musclePtr->getShape() == 2)
			{
				GLBox *tempGLBox = (GLBox *) temp1;
				Box *tempBox = (Box *)musclePtr;
				
				tempGLBox->setDimension1(0.5*d_collisionZoomFactor*tempBox->getDimension2());
				tempGLBox->setDimension2(0.5*d_collisionZoomFactor*tempBox->getDimension3());
				tempGLBox->setDimension3(0.5*d_collisionZoomFactor*tempBox->getDimension1());

				DT_ShapeHandle temp2 = d_shapeHandleList->getElement(i).getData();
				DT_Box *temp3 = (DT_Box *)temp2;
				temp3->setDimension1(0.5*d_collisionZoomFactor*tempBox->getDimension2());
				temp3->setDimension2(0.5*d_collisionZoomFactor*tempBox->getDimension3());
				temp3->setDimension3(0.5*d_collisionZoomFactor*tempBox->getDimension1());

				solidPosition = pos;// - 0.25*tempBox->getUAxis()*tempBox->getDimension1();
				solidPosition = d_collisionZoomFactor*solidPosition;
				d_objectList->getElement(i).getData()->reset(
					MT_Transform(MT_Quaternion(qx,qy,qz,qw), MT_Point3(solidPosition.getX(),solidPosition.getY(),solidPosition.getZ())));
			}
	}
}


//============================================================
// Simulation::checkCollision
//============================================================

void Simulation :: checkCollision(void)
	// Perform collision detection if required
{
	if(d_collisionCycles <= 0)
		{
			// Clear all lists in muscles to non contact state
			for(int i = 0; i < d_simulationAssembly->getNumMHUnits(); i++)
				d_simulationAssembly->getMHUnit(i)->getContactList()->clearList();

			DT_Test(d_scene, d_respTable);
			d_collisionCycles = 1; //c_collisionDecimation;
		}
	// Decrement the number of cycles left before collision detection
		d_collisionCycles--;
}

//============================================================
// Simulation::simulate
//============================================================

void Simulation :: simulate(void)
	// Perform simulation (text only or full)
{
	if(d_elapsedTime >= g_simulationStopTime) d_simState = SIM_STOP;
	
	if(d_simState == SIM_STOP)
	{
		exit(0);
	}
	
	if(d_simState == SIM_EDIT)
	{
		glutPostRedisplay();
		return;
	}

	if(d_simState == SIM_COLL_CHK)
	{
		DT_Test(d_scene, d_respTable);
		glutPostRedisplay();
		return;
	}

	if (d_simState == SIM_RUN) 
	{
				
	// Apply required commands at the current point in time
		d_simulationCommands->applyCommand(d_simulationAssembly, d_elapsedTime);

	// Perform one step of simulation by sequentially updating shape of each MHU 
	// followed by collision detection and updating the surface.
		d_simulationAssembly->updateAssembly();
		


	// Execute control algorithm
		this->performControl();

	// Perform collision detection if required
		this->checkCollision();

	// Save an image if required
		this->saveImages();

	// Preform data logging if required
		this->logData();

	// Increment simulation time
		d_elapsedTime += c_simulationStep;
	
	// Update Soild Objects
		this->updateSolid();
		

	// Update OpenGL display if required
		if(d_displayCycles <= 0)
		{
			glutPostRedisplay();	/* force update of the display */
			d_displayCycles = c_displayDecimation;
		}
	// Decerment number of cycles before next display update
		d_displayCycles--;
			
	}
	
	
	
}

//============================================================
// Simulation::getAssembly
//============================================================

Assembly * Simulation :: getAssembly(void) const
	// Perform simulation (text only or full)
{
	return d_simulationAssembly;
}

//============================================================
// Simulation::getCommands
//============================================================

Command * Simulation :: getCommands(void) const
	// Perform simulation (text only or full)
{
	return d_simulationCommands;
}


//============================================================
// Simulation::setInitialize
//============================================================

void Simulation :: setInitialize(bool initializationValue)
{
	this->d_isInitialized = initializationValue;
}


//============================================================
// Simulation::setSimState
//============================================================

void Simulation :: setSimState(simulationStates newState)
{
	this->d_simState = newState;
}


//============================================================
// Simulation::display
//============================================================
void Simulation::display(void)
{
	char title[80];
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	switch(d_simState)
	{
	case SIM_PRERUN:
		sprintf(title, "Surface Animation    Press F1 to Start,  F3 - Stop") ;
		break;
	case SIM_PAUSE:
		sprintf(title, "Surface Animation    F1 - Continue F3 - Stop    time = %f ",d_elapsedTime  ) ;
		break;
	case SIM_RUN:
		sprintf(title, "Surface Animation    F2 - Pause F3 - Stop    time = %f ",d_elapsedTime  ) ;
		break;
	case SIM_EDIT:
		sprintf(title, "Displaying MH Assembly # %d",d_simulationAssembly->getNumber()) ;
		break;

	case SIM_COLL_CHK:
		sprintf(title, "MH Units currently under collision shown in Red") ;
		break;
	}

	glutSetWindowTitle(title);
	glLoadIdentity();
	glPushMatrix();
		glTranslatef(d_viewPoint[0], d_viewPoint[1] , d_viewPoint[2]);

		glRotatef(d_viewAngle[0], 1.0f, 0.0f, 0.0f);
		glRotatef(d_viewAngle[1], 0.0f, 1.0f, 0.0f);
		glRotatef(d_viewAngle[2], 0.0f, 0.0f, 1.0f);
		
		glScalef(d_displayZoomFactor,d_displayZoomFactor,d_displayZoomFactor);
		d_simulationAssembly->display();
//		additionalDisplay();
	glPopMatrix();
	glutSwapBuffers();
	
}


//============================================================
// Simulation::additionalDisplay
//============================================================
void Simulation :: additionalDisplay(void){}
	// Trivial Implementation


//============================================================
// Simulation::initializeOpenGL
//============================================================
void Simulation :: initializeOpenGL(void)
{
	if(!this->d_isInitialized)
	{
		glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE );
		glutInitWindowSize (1000, 600);
		glutInitWindowPosition (10, 10);
		glutCreateWindow ("Surface Animation : Press F1 to Start Simulation");
		glClearColor (1.0, 1.0, 1.0, 1.0);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		this->d_isInitialized = true;
	}
}

//============================================================
// Simulation::initializeSolid
//============================================================
void Simulation :: initializeSolid(void)
{
	GLCylinder *temp10;
	GLBox *temp11;
	DT_ShapeHandle temp2;

	for(int i=0;i< d_simulationAssembly->getNumMHUnits();i++)
	{
		if(d_simulationAssembly->getMHUnit(i)->getShape() == 1)
		{
			Cylinder *tempCylPtr = (Cylinder *) d_simulationAssembly->getMHUnit(i);
			temp10 = new GLCylinder(d_collisionZoomFactor*tempCylPtr->getRadius(), 
							d_collisionZoomFactor*tempCylPtr->getHeight());

			temp2 = DT_NewCylinder(d_collisionZoomFactor*tempCylPtr->getRadius(),
							d_collisionZoomFactor*tempCylPtr->getHeight());

			d_shapeList->addElement(temp10);
		}
		
		if(d_simulationAssembly->getMHUnit(i)->getShape() == 2)
		{
			Box *tempBoxPtr = (Box *) d_simulationAssembly->getMHUnit(i);
			temp11 = new GLBox(0.5*d_collisionZoomFactor*tempBoxPtr->getDimension2(), 
							0.5*d_collisionZoomFactor*tempBoxPtr->getDimension3(),
							0.5*d_collisionZoomFactor*tempBoxPtr->getDimension1());

			temp2 = DT_NewBox(0.5*d_collisionZoomFactor*tempBoxPtr->getDimension2(), 
							0.5*d_collisionZoomFactor*tempBoxPtr->getDimension3(),
							0.5*d_collisionZoomFactor*tempBoxPtr->getDimension1());

			d_shapeList->addElement(temp11);
		}

				
		d_shapeHandleList->addElement(temp2);
	}
    d_scene = DT_CreateScene();
    d_respTable   = DT_CreateRespTable();
	d_bodyClass   = DT_GenResponseClass(d_respTable);
    DT_AddPairResponse(d_respTable, d_bodyClass, d_bodyClass, body2body, DT_DEPTH_RESPONSE, 0);  

	Object *temp3;
	
	//xg
    for (int i = 0; i < d_simulationAssembly->getNumMHUnits(); i++) 
	{
		temp3 = new Object(d_shapeList->getElement(i).getData(), d_shapeHandleList->getElement(i).getData(), massSphere);
		d_objectList->addElement(temp3);
	}
	//xg
    for (int i = 0; i < d_simulationAssembly->getNumMHUnits(); ++i) 
	{
		d_objectList->getElement(i).getData()->attachMuscle(d_simulationAssembly->getMHUnit(i));
		DT_SetMargin(d_objectList->getElement(i).getData()->getHandle(), BodyMargin);
		
		DT_AddObject(d_scene, d_objectList->getElement(i).getData()->getHandle());
		DT_SetResponseClass(d_respTable, d_objectList->getElement(i).getData()->getHandle(), d_bodyClass); 
    }

	double qw,qx,qy,qz;
	Vector pos, solidPosition;
	
	//xg
	for (int i = 0; i < d_simulationAssembly->getNumMHUnits(); ++i) 
	{
        Muscle *musclePtr = d_objectList->getElement(i).getData()->getMuscle();
		
		musclePtr->getUnitQuaternion(&qw,&qx,&qy,&qz);
		
		pos = musclePtr->getPosition();
		if(musclePtr->getShape() == 1)
			solidPosition = pos;// - 0.5*tempCyl->getOrientation()*tempCyl->getHeight();
		else if(musclePtr->getShape() == 2)
		{
			Box *tempBox = (Box *) d_simulationAssembly->getMHUnit(i);
			solidPosition = pos;// - 0.5*tempBox->getOrientation()*tempBox->getDimension1();
		}
		solidPosition = d_collisionZoomFactor*solidPosition;
		d_objectList->getElement(i).getData()->reset(
			MT_Transform(MT_Quaternion(qx,qy,qz,qw), MT_Point3(solidPosition.getX(),solidPosition.getY(),solidPosition.getZ())));
    }
	qh_initqhull_start (NULL, stdout, stderr);
}

//============================================================
// Simulation::initialize
//============================================================
void Simulation :: initialize(void)
{

	this->initializeOpenGL();
		
	glutPostRedisplay();

	this->initializeSolid();
	
}


//============================================================
// Simulation::reshapeWindow
//============================================================
void Simulation::reshapeWindow(int width, int height)
{
	GLfloat nRange = 80.0f;
	d_windowHeight = height;
	d_windowWidth = width;
	if(height == 0) height = 1;

	// Set Viewport to window dimensions
    glViewport(0, 0, width, height);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if (width <= height) 
		glOrtho (-nRange, nRange, -nRange*height/width, nRange*height/width, -nRange, nRange);
    else 
		glOrtho (-nRange*width/height, nRange*width/height, -nRange, nRange, -nRange, nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//============================================================
// Simulation::onKeyPress
//============================================================
//xg
//void Simulation::onKeyPress1(int key, int x, int y)
void Simulation::onKeyPress(int key, int x, int y)
{
	
	switch (key)
	{
		case GLUT_KEY_LEFT:
			d_viewPoint[0] -= 5.0;
			break;

		case GLUT_KEY_RIGHT:	
			d_viewPoint[0] += 5.0;
			break;

		case GLUT_KEY_UP:	
			d_viewPoint[1] += 5.0;
			break;
			
		case GLUT_KEY_DOWN:	
			d_viewPoint[1] -= 5.0;
			break;
		
		case GLUT_KEY_F1:
			if(d_simState == SIM_EDIT) break;
			d_simState = SIM_RUN;
			break;

		case GLUT_KEY_F2:
			if(d_simState == SIM_EDIT) break;
			d_simState = SIM_PAUSE;
			break;
			
		case GLUT_KEY_F3:
			if(d_simState == SIM_EDIT) break;
			d_simState = SIM_STOP;
			break;

		case GLUT_KEY_PAGE_UP:
			d_displayZoomFactor *= 1.1;
			break;

		case GLUT_KEY_PAGE_DOWN:
			d_displayZoomFactor /= 1.1;
			break;

		case GLUT_KEY_HOME:
			for(int i = 0; i < 3; i++)
			{
				d_viewPoint[i] = 0.0f;
				d_viewAngle[i] = 0.0f;
			}
			d_displayZoomFactor = 1.0f;
			break;
	}
	glutPostRedisplay();	
}


//============================================================
// Simulation::onKeyPress
//============================================================
//xg
//void Simulation::onKeyPress2(unsigned char key, int x, int y)
void Simulation::onKeyPress(unsigned char key, int x, int y)
{
	int i;
	switch (key)
	{
		case '8':
			d_viewAngle[0] -= 5.0;
			break;

		case '2':	
			d_viewAngle[0] += 5.0;
			break;

		case '4':	
			d_viewAngle[1] -= 5.0;
			break;
			
		case '6':	
			d_viewAngle[1] += 5.0;
			break;

		case '9':	
			d_viewAngle[2] -= 5.0;
			break;
		
		case '7':	
			d_viewAngle[2] -= 5.0;
			break;
			
		case '1':	
			d_viewAngle[2] += 5.0;
			break;
		
		case '3':	
			d_viewAngle[2] += 5.0;
			break;
		
		case ' ':
			for(i = 0; i < 3; i++)
			{
				d_viewPoint[i] = 0.0f;
				d_viewAngle[i] = 0.0f;
			}
			d_displayZoomFactor = 1.0f;
			break;
		
		case 27:
			for(i = 0; i < 3; i++)
			{
				d_viewPoint[i] = 0.0f;
				d_viewAngle[i] = 0.0f;
			}
			d_displayZoomFactor = 1.0f;
			break;

	}
	glutPostRedisplay();	
}

//============================================================
// Simulation::onMouseClick
//============================================================
void Simulation::onMouseClick(int button, int state, int x, int y)
{

	Vector offset(this->d_windowWidth/2,-this->d_windowHeight/2,0);
	Vector clickPoint(x,-y,0);
	clickPoint -= offset;
	clickPoint = clickPoint/d_displayZoomFactor;
	// Perform mouse calculations later Pradeep - 10/12/05
}