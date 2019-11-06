/*Booster Header*/

/*Includes these Headers*/


#include "GameObjects\Headers\GameObject.h"
#include "GameEngine/Headers/GameEngine.h"
#include "Reader/Reader.h"


class Booster : public GameObject
{
private:

	TextureReader obj2;
	unsigned int texture[2];
public:

	unsigned int vao[2];
	unsigned int buffer[3];
	static enum object { BOOSTER }; // VAO ids.
	static enum buffer { BOOSTER_VERTICES, BOOSTER_NORMALS }; // VBO ids.
	unsigned int BoosterTexLoc;
	float Flow;
	
	Booster(glm::vec3 position);
	~Booster();
	void SetUpDrawing();
	void DrawScene();
	void Update(int deltaTime);
	void loadBoosterTexture();
	void collides(Collider * other);
};

#pragma once
