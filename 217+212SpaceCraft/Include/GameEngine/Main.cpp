/*Source Cpp, Holds the main function to start the game*/
#pragma once
/////////////////////////
//    Jaimz Winter     //  
// Coventry University //
//    S/No 7896068     //
///////////////////////// 

/*Includes these files*/
#include "GameEngine/Headers/GameEngine.h"
#include "GameObjects/Headers/Track.h"
#include "GameObjects/Headers/SpaceCraft.h"
#include "GameObjects/Headers/Sphere.h"
#include "GameObjects\Headers\UFO.h"
#include "GameObjects\Headers\Booster.h"
using namespace std;
/*Main funtion, Starts the Game Engine*/
void main(int argc, char **argv)
{
	std::string Game;
	std::cout << "************************************************************************************************************************" << endl;
	std::cout << "                             ________      *                   *                                 " << endl;
	std::cout << "        *           *       /        \\           *                   *                          " << endl;
	std::cout << "                           /          \\                                                         " << endl;
	std::cout << "               *    ______/____________\\____________        *                 Welcome to space!   "<< endl;
	std::cout << "   *               /            ~                   \\ ~~                *       This is my coursework for 217/212 " << endl;
	std::cout << "         *        /    ~    @                 ~      \\ ~~~~                  Type y and hit enter to begin "<< endl;
	std::cout << "                 /       __               @           \\ ~~~~~~      *                                       " << endl;
	std::cout << "         *      /       /  \\                          \\ ~~~~~~~~                Controls:      " << endl;
	std::cout << "                \\       \\__/       ~                   |~~~~~~~~~               Arrow Keys to move                          " << endl;
	std::cout << "    *            \\                   @       ~   @     / ~~~~~~     *           PgUp and PgDn to move up and down                        "  << endl;
	std::cout << "                  \\     @     ~                       / ~~~~                     R T E to toggle Camera                        " << endl;
	std::cout << "                   \\_________________________________/ ~~          *             C and V to toggle Debug                        " << endl;
	std::cout << "                           \\           /                      *                  WASD to move(FreeCamera only)      " << endl;
	std::cout << "      *             *       \\         /       *                                                              " << endl;
	std::cout << "                             \\_______/     *            *           *                                        " << endl;


	std::cout << "    " << endl;
	std::cout << "   " << endl;
	std::cout << "    " << endl;

	std::cout << "                                          Do you want to play? y/n " << endl;

	std::getline(std::cin, Game);

	if (Game == "y" | Game == "Y") {
		GameEngine::InitEngine(argc, argv);

		GameEngine::addGameObject(new Track(glm::vec3(-30, 10, 25)));

		GameEngine::addGameObject(new Sphere(glm::vec3(-10, 8, -10), 20));

		GameEngine::addGameObject(new UFO(glm::vec3(0, 0, 0)));
	
		GameEngine::addGameObject(new Sphere(glm::vec3(15, 10, 15), 20));
		GameEngine::addGameObject(new Sphere(glm::vec3(20, 4, 0), 20));
		GameEngine::addGameObject(new Sphere(glm::vec3(-10, 10, 15), 20));
		GameEngine::addGameObject(new Sphere(glm::vec3(0, 14, -6), 20));

		GameEngine::addGameObject(new Sphere(glm::vec3(1, 5, 40), 20));

		GameEngine::addGameObject(new UFO(glm::vec3(-20, 3, -20)));
		GameEngine::addGameObject(new UFO(glm::vec3(0, 3, -40)));
		GameEngine::addGameObject(new UFO(glm::vec3(0, 3, 30)));

		GameEngine::addGameObject(new UFO(glm::vec3(20, 1, 20)));

		GameEngine::addGameObject(new Booster(glm::vec3(0, 10, 0)));

		GameEngine::StartEngine();
	}
};

