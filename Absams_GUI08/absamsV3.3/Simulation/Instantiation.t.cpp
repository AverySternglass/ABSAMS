//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Instantiation.t.cpp
// Example program to test the instantiation of the Assembly Class.
//========================================================================

//========================================================================
// Instantiation.t.cpp
//------------------------------------------------------------------------
// \brief
// The file Instantiation.t.cpp is an example program that tests the 
// instantiation of the assembly class. It was created to simplify the 
// process of debugging.
//
// This program demostrates the creation of the Assembly from a given 
// descriptor file (*.mha file)
//========================================================================


#include "Simulation.hpp"




Simulation *sim;

void mainDisplay(void)
{
	//display();
	sim->display();
	//SaveImageAs("test1.bmp");
}

void mainKeyboardFunction(int key, int x, int y)
{
	sim->onKeyPress(key,x,y);
}

void mainWindowFunction(int width, int height)
{
	sim->reshapeWindow(width, height);
}

void mainSimulationLoop(void)
{

	sim->simulate();
	Sucker *suckerPtr = (Sucker *)sim->getAssembly();
	if(suckerPtr->isSealed(sim->getAssembly()->getMHUnit(39))) cout << "Seal formed" << endl;
	else cout << "Seal not formed" << endl;
		
}




int main()
{
	Sucker *appendage;
	Command *commands;
	
	appendage = new Sucker(1, "Simulation Inputs\\Sucker13ObjFloor_6.mha");
	commands = new Command("Simulation Inputs\\Command_file3.mhc");
	sim = new Simulation(g_stepSize, g_collisionDecimation, g_displayDecimation, g_imageSaveDecimation,
				g_loggingDecimation, appendage, commands);
	sim->initialize();

	//appendage->getMHUnit(4)->setSelectionTag(2);
	//appendage->writeMHAFile("Simulation Inputs\\gm2_o.mha");
	//double testVol = appendage->getMuscleGroup(0)->getVolume();
	//cout << testVol << endl;
	//sim->getAssembly()->getSurface(0)->getNode(0)->setExternalForce(Vector(-1,0,0));
	//sim->getAssembly()->getSurface(0)->getNode(1)->setExternalForce(Vector(0,0.5,0));
	//sim->getAssembly()->getSurface(0)->getNode(2)->setExternalForce(Vector(0,0,0));
	//sim->getAssembly()->getSurface(0)->getNode(3)->setExternalForce(Vector(-1,0,0));
	//sim->getAssembly()->getMHUnit(0)->setAnchor();
	//cout << sim->getAssembly()->getMuscleGroup("grp2")->getGroupName() << endl;
	
	glutIdleFunc(mainSimulationLoop);
	glutDisplayFunc(mainDisplay); 
	glutReshapeFunc(mainWindowFunction);
	glutSpecialFunc(mainKeyboardFunction);
	glutMainLoop();
	return 0;
}


