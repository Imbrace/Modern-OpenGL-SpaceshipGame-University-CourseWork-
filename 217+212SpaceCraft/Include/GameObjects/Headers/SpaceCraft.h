/*SpaceCraft Header*/

/*Includes these Headers*/
#include "GameObject.h"
#include "GameEngine\Headers\Collider.h"
#include "GameEngine\Headers\BallCollider.h"
#include "Reader\Reader.h"
/*Definitions for Turning And Movement Speed*/
#define TURNING_SPEED 90.0
#define MOVE_SPEED 5.0


class SpaceCraft: public GameObject
{
private:

	//unsigned int modelMatLoc;
	/*Private Values*/
	TextureReader obj1;
	unsigned int texture[2];
public:
	float radius = 1.0f;

	/* Private Values for Movement*/
	float Acceleration = 5;
	glm::vec3 NewVelocity;
	glm::vec3 Velocity;

	/*Public Values for Movement*/
	float rotationAngle, pitchAngle = 0.0; //<Angle at which the ship is rotated.
	float rotSpeed = 90;
	glm::vec3 startHeading = GameObject::heading;
	glm::vec3 heading = startHeading;

	/*Values for Drawing*/
	unsigned int vao[2];
	unsigned int buffer[3];
	static enum object {SPACECRAFT};
	static enum buffer { SPACECRAFT_VERTICES, SPACECRAFT_NORMALS }; // VBO ids.
	unsigned int spaceCraftTexLoc;

	/*SpaceCraft Functions*/
	SpaceCraft(glm::vec3 position);
	~SpaceCraft();
	void SetUpDrawing();
	void DrawScene();
	void Update(int deltaTime);
	unsigned int * GetTriData(int &);
	void collides(Collider * other);
	void loadSpaceCraftTexture();
	
};