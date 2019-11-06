#ifndef SPHERE_H
#define SPHERE_H

#include "Graphics\vertex.h"
#include <vector>
#include "GameEngine\Headers\Collider.h"
#include "GameEngine\Headers\GameEngine.h"
#include "GameObject.h"
#include "GameEngine\Headers\BallCollider.h"

using namespace glm;
using namespace std;

class collisionManager;

class Sphere : public GameObject
{
private:
	//Sphere creation
	//REFERENCE: 'FieldAndSkyFilteredShaderized.sln'. From Computer Graphics Through OpenGL by Samanta Guha
	Vertex *sphereVerticesNor;  //121
	unsigned int *sphereIndices; //660
	int stacks; //10
	int slices; //10
	int sizeX;
	int sizeY;
	void CreateSpherewithNormal();
	int triNum = 660;
	float radius;
	unsigned int texture[5];
	float accel;
public:


	unsigned int vao[1];
	unsigned int buffer[2];

	enum object { SPHERE }; /// VAO ids.
	enum buffer { SPHERE_VERTICES, SPHERE_NORMALS };
	unsigned int sphereTexLoc;	
	int idd;
	static int idChecker;
	/**/
	Sphere(vec3 position, int i);

	~Sphere();
	void loadSphereTexture();
	void DrawScene();
	void Update(int deltaTime);
	void SetUpDrawing();
	Vertex * GetVerData(int &);
	unsigned int * GetTriData(int &);
	void collides(Collider * other);
};


#endif