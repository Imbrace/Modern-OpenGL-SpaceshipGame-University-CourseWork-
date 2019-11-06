#include "GameObjects\Headers\Sphere.h"
#include "GameObjects\Headers\GameObject.h"
#include "GameObjects\Headers\SpaceCraft.h"

using namespace std;
unsigned int GameEngine::Friction;
float Radii = 2.0f;
float Size = 1.0f;
/*REFERENCE- */
static const Material sphereFandB =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	50.0f
};

static const Material sphereRed =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(1.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	50.0f
};

static const Material sphereBlue =
{
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	50.0f
};

Sphere::Sphere(vec3 position, int i) : GameObject(position)
{
	stacks = 10;
	slices = 10;
	radius = Radii;

	position = position;
	Sphere::collider = new BallCollider(&this->position, radius);
	idd = i;

	sphereVerticesNor = (Vertex *)malloc(sizeof(Vertex) * 121);
	sphereIndices = (unsigned int *)malloc(sizeof(unsigned int) * 660);
	CreateSpherewithNormal();
}

Sphere::~Sphere()
{
	delete Sphere::collider;
	Sphere::collider = NULL;
}

void Sphere::loadSphereTexture()
{
	// Local storage for bmp image data.
	BitMapFile *image[10];

	// Load the textures.
	image[4] = getbmp("Planet.bmp");

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	sphereTexLoc = glGetUniformLocation(GameEngine::programId, "sphereTex");
	glUniform1i(sphereTexLoc, 4);
	glDisable(GL_TEXTURE4);


}

void Sphere::SetUpDrawing()
{
	
	glGenVertexArrays(1, vao);
	glGenBuffers(2, buffer);
	loadSphereTexture();
	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*121, sphereVerticesNor, GL_STATIC_DRAW);  ///please note the change
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*660, sphereIndices, GL_STATIC_DRAW); ///please note the change
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), 0);  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(13, 3, GL_FLOAT, GL_FALSE, sizeof(sphereVerticesNor[0]), (GLvoid*)sizeof(sphereVerticesNor[0].coords));
	glEnableVertexAttribArray(13);
	
}


void SphereColour(Material color) {
	//codes for OpenGL lighting Sphere MATS
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "SphereFandB.ambRefl"), 1, &color.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "SphereFandB.difRefl"), 1, &color.difRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "SphereFandB.specRefl"), 1, &color.specRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "SphereFandB.emitCols"), 1, &color.emitCols[0]);
	glUniform1f(glGetUniformLocation(GameEngine::programId, "SphereFandB.shininess"), color.shininess);
}

void Sphere::CreateSpherewithNormal(void)
{
	int count;
	count = 0;
	for (int i = 0; i <= stacks; ++i) {

		GLfloat V = i / (float)stacks;
		GLfloat phi = V * glm::pi <float>();

		// Loop Through Slices
		for (int j = 0; j <= slices; ++j) {

			GLfloat U = j / (float)slices;
			GLfloat theta = U * (glm::pi <float>() * 2);

			// Calc The Vertex Positions
			GLfloat x = cosf(theta) * sinf(phi);
			GLfloat y = cosf(phi);
			GLfloat z = sinf(theta) * sinf(phi);

			sphereVerticesNor[count].coords = vec4(x * radius, y * radius + 6.0, z * radius, 1.0);
			sphereVerticesNor[count].normal = vec3(x, y, z); ///Sphere normals
			count++;
		}
	}

	count = 0;
	// Calc The Index Positions
	for (int i = 0; i < slices * stacks + slices; ++i) {

		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i + slices;
		count++;

		sphereIndices[count] = i + slices + 1;
		count++;
		sphereIndices[count] = i;
		count++;
		sphereIndices[count] = i + 1;
		count++;
	}

	count = 0;
}


Vertex * Sphere::GetVerData(int &verNum)
{
	verNum = 121;
	return sphereVerticesNor;
}

unsigned int * Sphere::GetTriData(int &triNum)
{
	triNum = 660;
	return sphereIndices;
}

void Sphere::DrawScene()
{

	mat4 model = mat4(1.0f);
	model = translate(model, this->position);
	model = rotate(model, -glm::radians(accel), glm::vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(Size, Size, Size));
	glUniformMatrix4fv(GameEngine::modelMatLoc, 1, GL_FALSE, value_ptr(model));  //send tp the shader
	glUniform1ui(glGetUniformLocation(GameEngine::programId, "object"), 2);  //if (object == Sphere)

	glBindVertexArray(vao[0]);
	glDrawElements(GL_TRIANGLE_STRIP, 660, GL_UNSIGNED_INT, 0);  ///use index array to control triangle drawing
}

void Sphere::Update(int deltaTime)
{
	
	accel += 0.1f;
	if (accel >= 360.0f) accel -= 360.0f;
}

void Sphere::collides(Collider* other)
{
	
}
	//playsound