// All the collision resolution functions
#include "Simulation.hpp"
MassProps massSphere = {
    1.0f,
    { 0.4f, 0.4f, 0.4f }
};


DT_Bool body2body(void *client_data,  
			   void *object1,
			   void *object2,
			   const DT_CollData *coll_data) 
{
	
	Object& obj1 = *(Object *)object1;
	Object& obj2 = *(Object *)object2;
	MT_Point3 pos1(coll_data->point1);
	MT_Point3 pos2(coll_data->point2);
	MT_Vector3 normal(coll_data->normal);

	
	DT_GetPenDepth(obj1.getHandle(),obj2.getHandle(), pos1,pos2);
	//xg
	float dist = 0;
	for(int i=0;i<3;i++)
		dist += (pos2[i] - pos1[i])*(pos2[i] - pos1[i]);

	Vector newNormal (normal[0],normal[1],normal[2]);
	newNormal = newNormal.normalize();

	Vector newPoint[2];
		
	Muscle *mhUnitID[2];
	Vector velocity[2];
	double relativeVelocity;

	MT_Point3 gpos1 = obj1.getPosition();
	MT_Point3 gpos2 = obj2.getPosition();


	static int numCollisions = 0;
	static int numEffectiveCollisions = 0;
	numCollisions++;
	

	mhUnitID[0] = obj1.getMuscle();
	mhUnitID[1] = obj2.getMuscle();
	newPoint[0] = Vector((double)pos1[0],(double)pos1[1],(double)pos1[2]);
	newPoint[1] = Vector ((double)pos2[0],(double)pos2[1],(double)pos2[2]);
	
	
	mhUnitID[0]->getContactList()->addElement(mhUnitID[1]);
	mhUnitID[1]->getContactList()->addElement(mhUnitID[0]);

	if(mhUnitID[0]->getIgnoreCollision() && mhUnitID[1]->getIgnoreCollision())
	{
		mhUnitID[0]->setSelectionTag(1);
		mhUnitID[1]->setSelectionTag(1);
		return DT_CONTINUE;
	}
	//xg
	for(int i=0; i < 2; i++)
	{
		int newX = 1e4*newPoint[i].getX();
		int newY = 1e4*newPoint[i].getY();
		int newZ = 1e4*newPoint[i].getZ();

		newPoint[i] = Vector((double)newX,(double)newY,(double)newZ);

		newPoint[i] = newPoint[i]/(1e4*g_collisionZoomFactor);
	}

	//cout << newPoint[0] << endl;
	//xg
	for(int i=0; i < 2; i++)
		velocity[i] = mhUnitID[i]->getInstantaneousVelocity(newPoint[i]);


	// Step 1 : Calculate the relative velocity of the two points of contact
	//			which we have already done.

	relativeVelocity = newNormal.dotProduct((velocity[0] - velocity[1]));
	
	if(relativeVelocity < -g_epsilon)
	{
		// First we query each unit to get the equivalent Inertia
		// invIstar = 1/M + n.(invI* (r x n)) x r
		// where M - the mass of the unit
		//       n - normal at the point of collision
		//    invI - inverse Inertia matrix in the world frame (time varying)
		//		 r - relative position of the point of collision in the world frame
		//           ( i.e., the vector joining the centre of the MHU to the point
		//             as expressed in the world frame)
		numEffectiveCollisions++;
		//printf("%d\t%d\n", numCollisions, numEffectiveCollisions);
		double denom = 0;
		//xg
		for(int i=0; i < 2; i++)
			denom += mhUnitID[i]->getInvIstar(newNormal, newPoint[i]);

			double impulse = -((1 + g_restitutionCoefficient)/denom)* relativeVelocity /g_stepSize;
		
			mhUnitID[0]->applyForceAt(impulse*newNormal, newPoint[0]);
			mhUnitID[1]->applyForceAt(-1*impulse*newNormal, newPoint[1]);


		//cout << "Time: " << elapsedTime << "Num Collisons: " << numCollisions++ << endl;

	}




	// Now we have to calculate the magnitude of the impulse force that needs to be
	// applied to avoid penetration.
	// This is done parallel to the notes by David Baraff

	
	// Step 2 : 

	

	return DT_CONTINUE;
}
