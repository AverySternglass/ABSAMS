/*
 * SOLID - Software Library for Interference Detection
 * 
 * Copyright (C) 2001-2003  Dtecta.  All rights reserved.
 *
 * This library may be distributed under the terms of the Q Public License
 * (QPL) as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE.QPL included in the packaging of this file.
 *
 * This library may be distributed and/or modified under the terms of the
 * GNU General Public License (GPL) version 2 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.
 *
 * This library is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Commercial use or any other use of this library not covered by either 
 * the QPL or the GPL requires an additional license from Dtecta. 
 * Please contact info@dtecta.com for enquiries about the terms of commercial
 * use of this library.
 */

//#define STACKING            // Try stacking some boxes.
//#define FAKE_IT             // Set the inertia of rotation to infinite. 
                              // (Cheat to get things stable.) 
//#define USE_COMPLEX_GROUND  // Use a 20x20 mesh of triangles as ground surface                                
//#define USE_QUADS           // Idem, but now with quads  

#ifndef INCLUDED_Solid_hpp
#define INCLUDED_Solid_hpp


#include <new>
#include <GL/glut.h>

#include "GEN_MinMax.h"
#include "MT_Point3.h"
#include "MT_Vector3.h"
#include "MT_Quaternion.h"
#include "MT_Matrix3x3.h"
#include "MT_Transform.h"
#include "..\Assembly\Cement.hpp"

#include <SOLID.h>
#include "RigidBody.h"



const MT_Scalar GroundMargin =  0.0f;
const MT_Scalar BodyMargin = 0.0f;//-0.01f;//-0.05f; //-0.00001f

const int MaxImpulseIterations = 3;
const int MaxRelaxIterations = 3;
const MT_Scalar Relaxation  = 0.5f;


class GLShape {
public:
    virtual void paint() const = 0;
};

class GLBox : public GLShape {
    MT_Vector3 extent;
public:
    GLBox(MT_Scalar x, MT_Scalar y, MT_Scalar z) : 
        extent(x, y, z) {}

    void paint() const 
	{
        glPushMatrix();
        glScaled(extent[0], extent[1], extent[2]);
        glutSolidCube(1.0);
        glPopMatrix();
    }

	void setDimension1(double dimension1)
	{
		extent[0] = dimension1;
	}

	void setDimension2(double dimension2)
	{
		extent[1] = dimension2;
	}

	void setDimension3(double dimension3)
	{
		extent[2] = dimension3;
	}

};

class GLCylinder : public GLShape {
    MT_Scalar radius;
    MT_Scalar height;
    mutable GLuint displayList;

public:
    GLCylinder(MT_Scalar r, MT_Scalar h) : 
        radius(r), 
        height(h), 
        displayList(0) {}

    void paint() const 
	{ 
        if (displayList) glCallList(displayList); 
        else {
            GLUquadricObj *quadObj = gluNewQuadric();
            displayList = glGenLists(1);
            glNewList(displayList, GL_COMPILE_AND_EXECUTE);
            glPushMatrix();
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, -1.0);
            gluQuadricDrawStyle(quadObj, (GLenum)GLU_FILL);
            gluQuadricNormals(quadObj, (GLenum)GLU_SMOOTH);
            gluCylinder(quadObj, radius, radius, height, 15, 10);
            glPopMatrix ();
            glEndList();
        }
    }

	void setRadius(double newRadius)
	{
		radius = newRadius;
	}

	void setHeight(double newHeight)
	{
		height = newHeight;
	}

	MT_Scalar getRadius(void)
	{
		return(radius);
	}

	MT_Scalar getHeight(void)
	{
		return(height);
	}

};

struct MassProps {
	DT_Scalar   m_mass;
	DT_Vector3  m_inertia;
};

class Object : public RigidBody {
public:
    Object() {}
    Object(GLShape *gl_shape, DT_ShapeHandle shape, const MassProps& massProps)
	  : m_gl_shape(gl_shape),
        m_shape(shape),
        m_object(DT_CreateObject(this, shape)),
        m_penalty(0.0f, 0.0f, 0.0f),
		m_scaling(1.0f, 1.0f, 1.0f),
		m_color(MT_Vector3::random().absolute())
	{
#ifdef FAKE_IT
      MT_Vector3 inertia(0.0f, 0.0f, 0.0f);
#else
      MT_Vector3 inertia(massProps.m_inertia);
#endif
		setMassProps(massProps.m_mass, inertia);

	}
	
    ~Object() { DT_DestroyObject(m_object); }
	
	
    DT_ObjectHandle getHandle() const { return m_object; }
    
	void correct(const MT_Vector3& error) 
	{
		m_penalty += error;
	}
	
 	void setTransform(const MT_Transform& xform)
	{
		RigidBody::setTransform(xform);	
		float m[16];
		xform.getValue(m);
		DT_SetMatrixf(m_object, m);
		DT_SetScaling(m_object, m_scaling);
	}
	
	void relax()
	{
		translate(m_penalty * Relaxation);	
		m_penalty.setValue(0.0f, 0.0f, 0.0f);
		DT_SetPosition(m_object, getPosition()); 
	}
	
    void proceed(MT_Scalar step)
	{
		RigidBody::proceed(step);
		float m[16];
		m_xform.getValue(m);
		DT_SetMatrixf(m_object, m);
		DT_SetScaling(m_object, m_scaling);
	}
	
	void setScaling(MT_Scalar x, MT_Scalar y, MT_Scalar z)
	{
		m_scaling.setValue(x, y, z);
	}

	void attachMuscle(Muscle *mhu)
	{
		d_mhUnit = mhu;
	}

	Muscle *getMuscle(void)
	{
		return d_mhUnit;
	}

	GLShape *getShape(void)
	{
		return m_gl_shape;
	}

	void paint() 
	{
		if(d_mhUnit == NULL)
		{
			float m[16];
			DT_GetMatrixf(m_object, m);
			glPushMatrix(); 
			glMultMatrixf(m);
#ifdef DRAW_COORD
			coordSystem();
#endif
			glColor3fv(m_color);
			m_gl_shape->paint();
			glPopMatrix();
		}
		else
			d_mhUnit->display();
	}
	
private:
    GLShape        *m_gl_shape;
    DT_ShapeHandle  m_shape;
    DT_ObjectHandle m_object;
    MT_Vector3      m_penalty;
	MT_Vector3      m_scaling;
	MT_Vector3      m_color; 
	Muscle *d_mhUnit;
};


#endif // INCLUDED_Solid_hpp