#pragma once/*Track Header*/

/*Includes these Headers*/
#include "GameObjects\Headers\GameObject.h"
#include "GameEngine/Headers/GameEngine.h"
#include "Reader/Reader.h"

class Track : public GameObject
{
private:
	/*For Texturing*/
	TextureReader obj;
	unsigned int texture[2];

public:

	/*Values for Drawing*/
	unsigned int vao[2];
	unsigned int buffer[3];
	static enum object { TRACK};
	static enum buffer { TRACK_VERTICES, TRACK_NORMALS }; // VBO ids.
	unsigned int TrackTexLoc;
	float Flow;
	/*Track Functions*/
	Track(glm::vec3 position);
	~Track();
	void SetUpDrawing();
	void DrawScene();
	void Update(int deltaTime);
	void loadTrackTexture();
};
