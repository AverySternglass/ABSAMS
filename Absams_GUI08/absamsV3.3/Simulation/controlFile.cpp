#include "Simulation.hpp"

//============================================================
// Simulation::performControl
//============================================================

void Simulation :: performControl(void)
{

	// Add control algorithm here
#if 0
//	Sucker * tempSuckerpointer  =  (Sucker *)d_simulationAssembly;
//	tempSuckerpointer->getAreaOfRimContact();
//	tempSuckerpointer->getAreaOfRimContact();

	if(d_elapsedTime >= 0.00003 && d_elapsedTime <= 0.00004)
		d_simulationCommands->deleteSubsequentActions(d_elapsedTime);
	if(d_elapsedTime >=0.00009)
		d_simulationCommands->addCommand(0, 0.0002, -1, 0, 0);
//#endif
	
	Sucker * tempSuckerPtr  =  (Sucker *)d_simulationAssembly;
	Vector testVector;
	//testVector = tempSuckerPtr->getSuckerAdhesionForce();
	int i;

	if(d_elapsedTime >= 0.08 && !d_actionPerformed[1] 
		&& !(tempSuckerPtr->isSealed(d_simulationAssembly->getMHUnit(39))))
	{
		d_actionPerformed[1] = true;
		d_simulationCommands->addCommand(38, d_elapsedTime, -1, 0, 0.3);
		//for(i=0;i<41;i++)
		//		d_simulationCommands->addCommand(i, d_elapsedTime, -1, 0, 0);
	}

	if(tempSuckerPtr->isSealed(d_simulationAssembly->getMHUnit(39)))
		d_simulationAssembly->getMHUnit(39)->setSelectionTag(2);
	else d_simulationAssembly->getMHUnit(39)->setSelectionTag(0);

	//d_simulationAssembly->getMHUnit(39)->setSelectionTag(0);
	if(tempSuckerPtr->isSealed(d_simulationAssembly->getMHUnit(39)))
	{
		
		d_simulationAssembly->getMHUnit(39)
			->applyForceAt(tempSuckerPtr->getSuckerAdhesionForce(),
							d_simulationAssembly->getMHUnit(39)->getPosition());
		if(!d_actionPerformed[0])
		{
			d_actionPerformed[0] = true;
			d_simulationCommands->addCommand(18, d_elapsedTime, -1, 1, 1e-3);
			d_simulationCommands->addCommand(38, d_elapsedTime + 0.001, -1, 0, 0);
			for(i=0;i<6;i++)
				d_simulationCommands->addCommand(i, d_elapsedTime, -1, 0, 0);
		}
	}

	if(d_elapsedTime >= 0.01 && !d_actionPerformed[2])
	{
		d_actionPerformed[2] = true;
		for(i=20;i<26;i++)
				d_simulationCommands->addCommand(i, d_elapsedTime, -1, 1, 0.5);
	}
	return;
#endif
}
