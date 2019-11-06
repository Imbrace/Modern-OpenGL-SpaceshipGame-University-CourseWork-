/*BallCollider Header*/
#pragma once

/*Child of Collider*/
#include "GameEngine\Headers\Collider.h"

/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 

/*BallCollider Class*/
class BallCollider : public Collider {
private:

public:
	BallCollider(glm::vec3 * centre, float Radius); //Constructor
	~BallCollider(); //<Default destructor.

	float SphereRadius;

	float length = 0.0, width = 0.0, height = 0.0;

	float X();
	float Z();
	float Y();

	bool collidesWith(Collider * other);  //< Implementation of fuction deciding if this collider collides with the other one.
	void Draw(); // Draws ball collider around objects
};

