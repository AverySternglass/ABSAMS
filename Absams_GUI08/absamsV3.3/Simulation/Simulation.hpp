//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Simulation.hpp
// Interface of the class Simulation.
//========================================================================  
 

#ifndef INCLUDED_Simulation_hpp
#define INCLUDED_Simulation_hpp

#include "..\Assembly\Cement.hpp"
#include "..\Assembly\Sucker.hpp"
#include "..\Command\Command.hpp"

#include "..\Solid\Solid.hpp"
#include "..\Solid\DT_Cylinder.h"
#include "..\Solid\DT_Box.h"


#include<GL\glut.h>


//====================================================================
// class Simulation
// -------------------------------------------------------------------
// \brief
// The class \c Simulation represents a single run of a connective 
// tissue under specific conditions
//
// 
// 
//
// The class \c Simulation defines the data type \c Simulation and provides 
// methods for operations such as Run, Pause and Stop.
//
// <b>Example Program:</b>
//
// \include Simulation.t.cpp
//========================================================================  


class Simulation
{
public:
	
// ---- Constructor and Destructor -----
	
	Simulation(double simulationStep, Assembly *assembly, Command *command);
		// Copy Constructor used to perform simulations in text only mode

	Simulation(Assembly *assembly);
		// Copy Constructor used in MHA file editing mode

	Simulation(double simulationStep, int collisionDecimation, int displayDecimation, 
		int imageSaveDecimation, int loggingDecimation, Assembly *assembly, Command *command);
		// Copy Constructor used to perform simulations in full graphics mode

	~Simulation();
		// The default destructor.

// ---- Member Functions ----- 

	void simulate(void);
		// Performs entire simulation and all the functions needed thereof

	void saveImages(void);
		// Checks if screenshot needs to be saved and does required operations
		// to handle saving images when needed

	void updateSolid(void);
		// Updates Solid objects with the changes in the current simulation cycle
		
	void logData(void);
		// Checks if simulation data needs to be saved and does required operations
		// to handle data logging when needed

	void checkCollision(void);
		// Checks if objects are in collision by using Solid commands. 
		// Appropriate action is taken by Solid in response to collision

	void performControl(void);
		// The Control Algorithm

	Assembly *getAssembly(void) const;
		// Provides access to the assembly being simulated

	Command *getCommands(void) const;
		// Provides access to the commands being applied

#ifdef __glut_h__

	void initialize(void);
		// Initialize all simulation parameters and windows

	void initializeOpenGL(void);
		// Initialize all the required openGL functions and windows

	void initializeSolid(void);
		// Initialize all the required objects for Solid
	
	void display(void);
		// All the required graphics are displayed

	void additionalDisplay(void);
		// Trivially implemented here, used when the example program
		// requires specific outputs to be displayed. Useful for debugging

	void reshapeWindow (int width, int height);
		// Handles window reshaping

	//xg
	//void onKeyPress1(int key, int x, int y);
	void onKeyPress(int key, int x, int y);
		// Handles keyboard inputs
	//xg
	//void onKeyPress2(unsigned char key, int x, int y);
	void onKeyPress(unsigned char key, int x, int y);
		// Handles keyboard inputs

	void onMouseClick(int button, int state, int x, int y);
		// Handles Mouse clicks

	void setInitialize(bool initializationValue);
		// Provides access to the window created by openGL

	void setSimState(simulationStates newState);
		// Provides access to the data member d_simState
#endif
	
	double d_elapsedTime;
		// Time elapsed in the simulation
private:
		
	int d_collisionCycles;
		// Number of simulation steps since collision was last tested

	int d_displayCycles;
		// Number of simulation steps since the graphics window was last updated
	
	int d_imageSaveCycles;
		// Number of simulation steps since the graphics window was last saved to 
		// a bmp file

	double d_loggingCycles;
		// Number of simulation steps since the log data was last saved
		// Is set to -1 initially to write out Log file header.
		// Subsequently it is either 0 or a positive number

	int d_frameCount;
		// Number of frames (bmp images) created

	const double c_simulationStep;
		// Simulation Step size to be used

	const int c_collisionDecimation;
		// Number of simulation steps after which collision detection is done

	const int c_displayDecimation;
		// Number of simulation steps after which display is updated

	const int c_imageSaveDecimation;
		// Number of simulation steps after which a bmp image is saved

	const int c_loggingDecimation;
		// Number of simulation steps after which an entry is made to the log file

	const bool c_isGraphicSimulation;

	simulationStates d_simState;

	double d_viewPoint[3];
		// View Point for the OpenGL graphics

	double d_viewAngle[3];
		// Angle of rotation for the OpenGL graphics

	double d_windowHeight;
		// Height of openGL window

	double d_windowWidth;
		// Width of openGL window

	double d_collisionZoomFactor;
		// Zoom Factor only for collision purposes

	double d_displayZoomFactor;
		// Zoom Factor only for display purposes

	bool d_isInitialized;
		// Indicates if the simulation has been initialized
	
	bool d_actionPerformed[25];
		// Used to ensure that certain control actions are performed only once
		// Initialized to false and when action occures, the flag is reset

	/*Simulation();
		// The default constructor. Do not allow simulation without specifying 
		// parameters
	*/
	Assembly *d_simulationAssembly;
		// The MH Assembly  to be simulated

	Command *d_simulationCommands;
		// The MH Assembly  to be simulated

	List <Object *> *d_objectList;
		// List of Solid objects
	
	List <GLShape *> *d_shapeList;
		// List of Solid Shapes

	List <DT_ShapeHandle> *d_shapeHandleList;
		// List of Solid Shape Handles

	DT_SceneHandle     d_scene;
	DT_RespTableHandle d_respTable;
	DT_ResponseClass   d_bodyClass;
		// Solid junk

		
};



#endif // INCLUDED_Simulation_hpp