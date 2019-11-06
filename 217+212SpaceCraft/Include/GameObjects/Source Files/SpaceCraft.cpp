/*SpaceCraft Cpp files*/

/*Includes these header files*/
#include "GameObjects\Headers\SpaceCraft.h"
#include "GameEngine\Headers\GameEngine.h"
#include <Windows.h>
#include <mmsystem.h>


/*Defintions of Heading and Position values*/
vec3 heading = vec3(0.0, 0.0, -1.0); 
vec3 position = vec3(0.0, 0.0, 0.0);


/*Constructor*/
SpaceCraft::SpaceCraft(vec3 position) : GameObject(position) 
{
	
	this->position = position;
	
	SpaceCraft::collider = new BallCollider(&this->position, radius);
	char filename[] = "SpaceCraft.obj";
	obj1.LoadModel(filename);
}


/*Destructor*/
SpaceCraft::~SpaceCraft()
{

}

void SpaceCraft::loadSpaceCraftTexture()
{
	// Local storage for bmp image data.
	BitMapFile *image[5];

	// Load the textures.
	image[4] = getbmp("Moon.bmp");

	// Bind grass image.
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	spaceCraftTexLoc = glGetUniformLocation(GameEngine::programId, "spaceCraftTex");
	glUniform1i(spaceCraftTexLoc, 3);
	glDisable(GL_TEXTURE3);
}

void SpaceCraft::SetUpDrawing()
{
	glGenVertexArrays(1, vao);
	glGenBuffers(1, buffer);
	loadSpaceCraftTexture();

	glBindVertexArray(vao[SPACECRAFT]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[SPACECRAFT_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj1.numFaces * 3, /*this->sphereVerticesNor*/obj1.verts, GL_STATIC_DRAW);  //please note the change
	glVertexAttribPointer(9, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(9);
	glVertexAttribPointer(10, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex::coords) + sizeof(Vertex::normal)));   //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(10);
}

void SpaceCraft::DrawScene()
{

	mat4 modelMat = mat4(1.0);
	modelMat = translate(modelMat, this->position);
	modelMat = rotate(modelMat, -glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = scale(modelMat, vec3(5, 5, 5));

	modelMat = rotate(modelMat, glm::radians(rotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));  //Sends to the Shader
	glUniform1ui(glGetUniformLocation(GameEngine::programId, "object"), 4);
	glBindVertexArray(vao[SPACECRAFT]);

	glDrawArrays(GL_TRIANGLES, 0, obj1.numFaces * 3);
}


void SpaceCraft::Update(int deltaTime) {

	/*Reference*/
	//heading.y = 0;
	float turningSpeed = TURNING_SPEED * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time
	NewVelocity = Velocity + (Acceleration* this->heading) * (deltaTime / 1000.0f);
	position = position + NewVelocity * (deltaTime / 1000.0f);



		if (specialKeys[GLUT_KEY_UP]) {
			Acceleration += MOVE_SPEED;

		}
		else if (specialKeys[GLUT_KEY_DOWN]) {
			Acceleration -= MOVE_SPEED;
		}
		else
		{
			if (Acceleration > 0) {
				Acceleration = Acceleration - MOVE_SPEED;
			}
			if (Acceleration < 0)
			{
				Acceleration = Acceleration + MOVE_SPEED;
			}

			if (Acceleration > -10.0f && Acceleration < 10.0f)
			{
				Acceleration = 0.0f;
			}

		}
		if (specialKeys[GLUT_KEY_PAGE_UP])
		{
			this->pitchAngle += turningSpeed; // in degrees not radians

		}
		if (specialKeys[GLUT_KEY_PAGE_DOWN])
		{
			this->pitchAngle -= turningSpeed; // in degrees not radians
		}
		if (specialKeys[GLUT_KEY_LEFT]) {
			this->rotationAngle += turningSpeed; //in degrees not radians
		}

		if (specialKeys[GLUT_KEY_RIGHT]) {
			this->rotationAngle -= turningSpeed; //in degrees not radians
		}


		this->heading = glm::rotate(this->startHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
		this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0.0, 0.0, 1.0));
	}

void SpaceCraft::collides(Collider* other)
{

	this->position.x--;
	this->position.z--;

	Acceleration = 0;
}
