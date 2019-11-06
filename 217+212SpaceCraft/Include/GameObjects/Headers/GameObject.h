/*Game Object Header*/
/*Holds Data for all game objects such as Collider.h and shader.h*/
#pragma once

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLUT/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif

/*Including Libraries*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>
/*Including my class headers*/
#include "Shaders\Shader.h"
#include "Graphics\getbmp.h"
#include "Graphics\material.h"
#include "Graphics\vertex.h"
#include "Reader\Reader.h"

#include "GameEngine\Headers\Collider.h"
#include "GameEngine\Headers\BallCollider.h"
/*Name Spaces I'm using*/
using namespace glm;
using namespace std;


class GameObject
{
protected:

public:
	/*Key mapping to allow key press functions*/
	
	static std::map<int, bool> specialKeys;
	static std::map<int, bool> keys;
	unsigned int modelMatLoc;
	Collider* collider = NULL;
	static float d, d2, d3, d4, d5, d6;
	
	bool active = true;
	mat4 modelViewMat = mat4(1.0);

	vec3 heading = vec3(0.0, 0.0, -1.0); // direction object faces
	vec3 position = vec3(0.0, 0.0, 0.0);
	//GameObject();
	GameObject(glm::vec3 position);
	~GameObject();
	virtual void SetUpDrawing(); 
	virtual void DrawScene();
	virtual void Update(int deltaTime);
	virtual void collides(Collider* other);


	//static enum object { TRACK, UFOD, SPACECRAFT }; // VAO ids.
	//static enum buffer { TRACK_VERTICES, TRACK_NORMALS, UFOD_VERTICES, UFOD_NORMALS, SPACECRAFT_VERTICES, SPACECRAFT_NORMALS }; // VBO ids.


};

