
#include "GameObjects\Headers\Booster.h"

Booster::Booster(glm::vec3 position) : GameObject(position)
{
	char filename[] = "SpaceCraft.obj";
	obj2.LoadModel(filename);
}

Booster::~Booster()
{
}

void Booster::loadBoosterTexture()
{
	// Local storage for bmp image data.
	static BitMapFile *image[5];

	// Load the textures.
	image[4] = getbmp("UFO.bmp");

	// Bind grass image.
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	BoosterTexLoc = glGetUniformLocation(GameEngine::programId, "spaceOneTex");
	glUniform1i(BoosterTexLoc, 6);
}

void Booster::SetUpDrawing()
{
	glGenTextures(5, texture);
	//loadBoosterTexture();

	glGenVertexArrays(1, vao);
	glGenBuffers(1, buffer);

	glBindVertexArray(vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj2.numFaces * 3, obj2.verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex::coords) + sizeof(Vertex::normal)));  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(1);
}

void Booster::DrawScene()
{

	mat4 modelMat = mat4(1.0);
	modelMat = translate(modelMat, this->position);
	
	modelMat = rotate(modelMat, -glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = scale(modelMat, vec3(400, 400, 400));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));  //send to the shader
	glUniform1ui(glGetUniformLocation(GameEngine::programId, "object"), 6);
	glBindVertexArray(vao[0]);

	glDrawArrays(GL_TRIANGLES, 0, obj2.numFaces * 3);
}

void Booster::Update(int deltaTime)
{
}

void Booster::collides(Collider* other)
{

}
