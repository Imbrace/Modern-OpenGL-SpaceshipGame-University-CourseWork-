/*Game Engine Header*/
#pragma once
/*Include these files*/
#include "GameObjects\Headers\GameObject.h"

class GameEngine
{
private:
	
public:
	/*Vectors to keep track of drawn and undrawn objects*/
	//static std::vector <GameObject*> GameObjects;
	//static std::vector <GameObject*> DrawnObjects;
	


	/*Camera Variables */
	static float yaw;
	static float pitch;
	static void mouseMove(int x, int y);
	static glm::vec3 cameraPos;
	static glm::vec3 cameraFront;

	/*The old time since the start of the game (from previous frame) for delta time calculation.*/
	static int oldTimeSinceStart;

	/*The time since the start of the game for delta time calculation.*/
	static int newTimeSinceStart;

	/*Variables */
	static unsigned int modelMatLoc;
	static unsigned int objectLoc;
	static unsigned int programId;
	static unsigned int Friction;
	static vector<GameObject*> GameObjects;


	/*Game Engine Functions*/
	GameEngine();
	~GameEngine();
	static void Update();
	static void DrawScene();
	static void SetUp();
	static void InitEngine(int argc, char ** argv);
	static void addGameObject(GameObject *gameobject);
	static void StartEngine();
};

