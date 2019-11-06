/*UFO Header*/

/*Includes these Headers*/
#include "GameObjects\Headers\GameObject.h"
#include "GameEngine/Headers/GameEngine.h"
#include "Reader/Reader.h"
#include "GameEngine\Headers\BallCollider.h"
#include "GameEngine\Headers\Collider.h"

class UFO : public GameObject
{
private:
	TextureReader obj;
	unsigned int texture[2];
	float angle;
public:

	
	unsigned int vao[2];
	unsigned int buffer[3];
	static enum object {UFOD};
	static enum buffer {UFOD_VERTICES, UFOD_NORMALS}; // VBO ids.
	unsigned int UFOTexLoc;
	float Flow;
	
	UFO(glm::vec3 position);
	~UFO();
	void SetUpDrawing();
	void DrawScene();
	void Update(int deltaTime);
	void loadUFOTexture();
	void collides(Collider * other);
};
