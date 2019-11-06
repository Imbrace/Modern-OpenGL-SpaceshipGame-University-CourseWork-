#include "GameObjects\Headers\Booster.h"

Booster::Booster(glm::vec3 position) : GameObject(position)
{
	char filename[] = "Race.obj";
	obj.LoadModel(filename);
}

Booster::~Booster()
{
}

void Booster::loadBoosterTexture()
{
	// Local storage for bmp image data.
	static BitMapFile *image[2];

	// Load the textures.
	image[3] = getbmp "Star.bmp");

	// Bind grass image.
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->sizeX, image[3]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	BoosterTexLoc = glGetUniformLocation(GameEngine::programId, "boosterTex");
	glUniform1i(BoosterTexLoc, 6);
	glDisable(GL_TEXTURE6);
}

void Booster::SetUpDrawing()
{
	glGenTextures(5, texture);
	loadTrackTexture();

	glGenVertexArrays(10, vao);
	glGenBuffers(10, buffer);

	glBindVertexArray(vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * obj.numFaces * 3, obj.verts, GL_STATIC_DRAW);
	glVertexAttribPointer(16, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(16);
	glVertexAttribPointer(17, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(Vertex::coords) + sizeof(Vertex::normal)));  //layout(location=4) in vec4 fieldCoords;
	glEnableVertexAttribArray(17);
}

void Booster::DrawScene()
{

	mat4 modelMat = mat4(1.0);
	modelMat = translate(modelMat, this->position);
	//modelMat = glm::translate(modelMat, vec3(0, 15, -5));
	modelMat = rotate(modelMat, -glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = scale(modelMat, vec3(9, 9, 9));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));  //send to the shader
	glUniform1ui(glGetUniformLocation(GameEngine::programId, "object"), 5);
	glBindVertexArray(vao[2]);

	glDrawArrays(GL_TRIANGLES, 0, obj.numFaces * 3);
}

void Booster::Update(int deltaTime)
{
}

void Booster::collides(Collider* other)
{

}