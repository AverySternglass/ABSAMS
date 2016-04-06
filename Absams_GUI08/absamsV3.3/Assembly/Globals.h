#ifndef INCLUDED_globals_h
#define INCLUDED_globals_h

#include <GL\Glut.h>
#include "Volume.hpp" // Qhull includes to calculate volumes

#define MAX_NODES 27	
#define NUM_ROWS 5
#define NUM_COLS 5
#define MAX_NUM_SPRINGS 99 // Exact Number can be calculated based on the configuration 
#define NUM_ANCHORS 3
#define MAX_SURFACES 10

enum simulationStates
	{
		SIM_PRERUN,
		SIM_RUN,
		SIM_PAUSE,
		SIM_EDIT,
		SIM_COLL_CHK,
		SIM_STOP
	};
//#define costrain_dynamics

//const static double g_nodeMass = 0.01;					// Mass per node

//const static double g_collisionSpringStiffness = 100;

const static double g_pretension = 0;
const static double g_stepSize = 0.0000001;//0.0000001
const static int g_collisionDecimation =  1;//0.0001
const static int g_displayDecimation =  100;//0.0001
const static int g_imageSaveDecimation =  10000;//0.0001
const static int g_loggingDecimation =  10000;   //0.000001
const static double g_simulationStopTime =  1.0;

const static char logFileName[60] = "log.mhl";
//const static char logFileName[60] = "log.mhl";


const static double g_scaleFactor = 2000; 
const static double g_epsilon = 1e-5;//1e-10 // Smallest relative vel to trigger impulse response
const static double g_restitutionCoefficient = 0.0; // 1 for no energy loss 0 for total loss
const static double g_infiniteMass = 10; // If anchored, it is used in colision calculations
const static double g_muscleForcePerArea = -600000; // In N/sq.m corresponds to 600mN/sq.mm

const static double g_cephMuscleDensity = 1000;	// Density in Kg/cu.m
const static double g_EAP1MuscleDensity = 1800;	// Density in Kg/cu.m
const static double g_EAP2MuscleDensity = 1800;	// Density in Kg/cu.m

const static double g_collagenDamping = 1000; // 10;
const static double g_rubberDamping = 1000;//10;

const static double g_collagenStiffness = 700000;//1000//700000
const static double g_rubberStiffness = 700000;//1000//700000

const static double g_sizeRatio = 1;




const static double PI=3.1415926535897932;
const static double g_ambientPressure = 0.0;//9810 ;
//const static double g_cylinderMass = 7.85e-3; // the mass of each cylinder calculated individually
const static double g_bulkModulus = 2.35e9;

const static double g_radialMuscleStiffness = 5e4;
const static double g_longitudinalMuscleStiffness = 1.23e4;

// For Box class.. will be combined with the above two later
const static double g_dimension1MuscleStiffness = 5e4;
const static double g_dimension3MuscleStiffness = 1.23e4;

const static double g_muscleDamping = 1200 ;
const static double g_gravity = 9.8;

const static double g_waterDensity = 1e3;


enum Media
{
	AIR,
	WATER
};
const static double medium = WATER;
const static double g_collisionZoomFactor = 100;


#endif // INCLUDED_globals_h