/*Game Engine Cpp*/

/*Include these files*/
#include "GameEngine\Headers\GameEngine.h"
#include "GameObjects\Headers\Sphere.h"
#include "GameObjects\Headers\SpaceCraft.h"
#include <Windows.h>
#include <mmsystem.h>

SpaceCraft* spacecraft;

/*Vairables*/
int GameEngine::oldTimeSinceStart; // Old time Since last Frame
int GameEngine::newTimeSinceStart; // New time frame

std::map<int, bool> GameObject::specialKeys;
std::map<int, bool> GameObject::keys;

unsigned int GameEngine::modelMatLoc;
unsigned int GameEngine::objectLoc;
unsigned int GameEngine::programId;
vector<GameObject*> GameEngine::GameObjects;

/*VAO and VBO*/

enum object { SPACEONE, SPACETWO, MENU };
enum buffer { SPACEONE_VERTICES, SPACETWO_VERTICES, MENU_VERTICES };

#define PI 3.14														
bool debugMode = false;
bool Menu = true;

/*Camera Values*/
glm::vec3 GameEngine::cameraPos = glm::vec3(0.0f, 5.0f, 0.0f);
glm::vec3 GameEngine::cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float GameEngine::yaw = 90.0f;
float GameEngine::pitch = 0.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
float fov = 45.0f;

int CameraMode = 1;

GameEngine::GameEngine(){} //Constructor

GameEngine::~GameEngine(){}// Destructor

float X = 0;
float Y = 1;
float Z = 0;
struct Light
{
	vec4 ambCols;
	vec4 difCols;
 	vec4 specCols;
	vec4 coords;
};

static Light light0 =
{
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 0.0, 0.0, 0.0)
};

// Global ambient.
static const vec4 globAmb = vec4(0.2, 0.2, 0.2, 1.0);

// Front and back material properties.
static const Material matFandB =
{
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),
	vec4(0.0, 0.0, 0.0, 1.0),
	50.0f
};

/*SpaceOne Coords 1 */
static Vertex SpaceOneVertices[] =
{
{ vec4(50.0, 0.0, 50.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(8.0, 0.0) },
{ vec4(50.0, 0.0, -50.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(8.0, 8.0) },
{ vec4(-50.0, 0.0, 50.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(0.0, 0.0) },
{ vec4(-50.0, 0.0, -50.0, 1.0), vec3(0.0, 1.0, 0.0), vec2(0.0, 8.0) }
};
/*SpaceTwo Coords 1 */
static Vertex SpaceTwoVertices[4] =
{
{ vec4(60.0, 0.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 0.0) },
{ vec4(60.0, 60.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 1.0) },
{ vec4(-60.0, 0.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 0.0) },
{ vec4(-60.0, 60.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 1.0) }
};


/*Menu */
static Vertex MenuVertices[] =
{
{ vec4(60.0, 0.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 0.0) },
{ vec4(60.0, 60.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(1.0, 1.0) },
{ vec4(-60.0, 0.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 0.0) },
{ vec4(-60.0, 60.0, -50.0, 1.0), vec3(0.0, 0.0, 1.0), vec2(0.0, 1.0) }
};

static mat4 modelMat = mat4(1.0f);
static mat4 viewMat = mat4(1.0f);
static mat4 projMat = mat4(1.0);
static mat3 normalMat = mat3(1.0);

static unsigned int
vertexShaderId,
fragmentShaderId,
viewMatLoc,
projMatLoc,
normalMatLoc,
spaceOneTexLoc,
spaceTwoTexLoc,
spaceThreeTexLoc,
sphereTexLoc,
menuTexLoc,
light0coordsLoc,
alphaLoc,
buffer[3],
vao[3],
texture[6];

static BitMapFile *image[6];

static float theta = 0.0; // Angle of the sun.
static float alpha = 0.0; // Blending parameter.

/*REFERECE Shader Test Function// Ian Evans, Coventry University */
void shaderCompileTest(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength; glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;
}


void GameEngine::SetUp() // Setup Function.
{
	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	//Creates the shader prgram
	vertexShaderId = setShader((char*)"vertex", (char*)"vertexShader.glsl");
	fragmentShaderId = setShader((char*)"fragment", (char*)"fragmentShader.glsl");
	GameEngine::programId = glCreateProgram();

	/*REFERENCE CONTINUED Shader Test Function/ Ian Evans */
	/*Runs a shader debug to test for any errors inside the shader*/
	std::cout << "::: VERTEX SHADER :::" << std::endl;
	shaderCompileTest(vertexShaderId);
	std::cout << "::: FRAGMENT SHADER :::" << std::endl;
	shaderCompileTest(fragmentShaderId);
	
	glAttachShader(GameEngine::programId, vertexShaderId);
	glAttachShader(GameEngine::programId, fragmentShaderId);
	glLinkProgram(GameEngine::programId);
	glUseProgram(GameEngine::programId);

	//Creates VAOs and VBOs
	glGenVertexArrays(4, vao);
	glGenBuffers(4, buffer);

	/*REFERENCE Sky and Field Set up/ */
	
	/*
	//Binds Field to Buffer and Vao
	glBindVertexArray(vao[SPACEONE]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[SPACEONE_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpaceOneVertices), SpaceOneVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(SpaceOneVertices[0]), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SpaceOneVertices[0]), (void*)sizeof(SpaceOneVertices[0].coords));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(SpaceOneVertices[0]), (void*)(sizeof(SpaceOneVertices[0].coords) + sizeof(SpaceOneVertices[0].normal)));
	glEnableVertexAttribArray(2);
*/

	//Binds Sky to Buffer and Vao
	glBindVertexArray(vao[SPACETWO]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[SPACETWO_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SpaceTwoVertices), SpaceTwoVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(SpaceTwoVertices[0]), 0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(SpaceTwoVertices[0]), (void*)sizeof(SpaceTwoVertices[0].coords));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(SpaceTwoVertices[0]), (void*)(sizeof(SpaceTwoVertices[0].coords) + sizeof(SpaceTwoVertices[0].normal)));
	glEnableVertexAttribArray(4);


	glBindVertexArray(vao[MENU]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[MENU_VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MenuVertices), MenuVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(7, 9, GL_FLOAT, GL_FALSE, sizeof(MenuVertices[0]), 0);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, sizeof(MenuVertices[0]), (void*)(sizeof(MenuVertices[0].coords) + sizeof(MenuVertices[0].normal)));
	glEnableVertexAttribArray(8);
	

	// Obtain projection matrix uniform location and set value.
	projMatLoc = glGetUniformLocation(GameEngine::programId, "projMat");
	projMat = perspective(glm::radians(45.0f), 1.0f, 1.0f, 1000.0f);
	//frustum(-5.0, 5.0, -5.0, 5.0, 1.0, 1000.0);
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMat));

	// Obtain model matrix, view matrix, normal matrix, object and alpha uniform locations.
	modelMatLoc = glGetUniformLocation(GameEngine::programId, "modelMat");
	viewMatLoc = glGetUniformLocation(GameEngine::programId, "viewMat");

	normalMatLoc = glGetUniformLocation(GameEngine::programId, "normalMat");
	objectLoc = glGetUniformLocation(GameEngine::programId, "object");
	alphaLoc = glGetUniformLocation(GameEngine::programId, "alpha");

	// Obtain light property uniform locations and set values.
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "light0.ambCols"), 1, &light0.ambCols[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "light0.difCols"), 1, &light0.difCols[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "light0.specCols"), 1, &light0.specCols[0]);
	light0coordsLoc = glGetUniformLocation(GameEngine::programId, "light0.coords");

	// Obtain global ambient uniform location and set value.
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "globAmb"), 1, &globAmb[0]);

	// Obtain front material property uniform locations and set values.
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "matFandB.ambRefl"), 1, &matFandB.ambRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "matFandB.difRefl"), 1, &matFandB.difRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "matFandB.specRefl"), 1, &matFandB.specRefl[0]);
	glUniform4fv(glGetUniformLocation(GameEngine::programId, "matFandB.emitCols"), 1, &matFandB.emitCols[0]);
	glUniform1f(glGetUniformLocation(GameEngine::programId, "matFandB.shininess"), matFandB.shininess);

	// Load the Texture images.
	image[4] = getbmp("Planet.bmp");
	image[1] = getbmp("SpaceBlue.bmp");
	image[2] = getbmp("SpaceHuh.bmp");
	image[3] = getbmp("SpaceCraft.bmp");

	// Create texture ids.
	glGenTextures(6, texture);
	
	/*
	// Bind grass image.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->sizeX, image[0]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	spaceOneTexLoc = glGetUniformLocation(GameEngine::programId, "spaceOneTex");
	glUniform1i(spaceOneTexLoc, 0);

	*/


	// Bind sky image.
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->sizeX, image[1]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	spaceTwoTexLoc = glGetUniformLocation(GameEngine::programId, "spaceTwoTex");
	glUniform1i(spaceTwoTexLoc, 1);

	
	// Bind night sky image.
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->sizeX, image[2]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	spaceThreeTexLoc = glGetUniformLocation(GameEngine::programId, "spaceThreeTex");
	glUniform1i(spaceThreeTexLoc, 2);

	
	spacecraft = new SpaceCraft(glm::vec3(-15, 10, -15));
	addGameObject(spacecraft);

	
	/* Bind Menu Image
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->sizeX, image[3]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	menuTexLoc = glGetUniformLocation(GameEngine::programId, "menuTex");
	glUniform1i(menuTexLoc, 3);
	*/
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->sizeX, image[3]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	menuTexLoc = glGetUniformLocation(GameEngine::programId, "spaceCraftTex");
	glUniform1i(menuTexLoc, 3);
	glDisable(GL_TEXTURE3);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->sizeX, image[4]->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	spaceThreeTexLoc = glGetUniformLocation(GameEngine::programId, "sphereTex");
	glUniform1i(spaceThreeTexLoc, 4);

}

void GameEngine::DrawScene() // DrawScene function
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewMat = mat4(1.0);
	/*View Matrix's // Camera*/
	if (CameraMode == 2) {
		viewMat = lookAt(spacecraft->position + glm::vec3(-sin(radians(spacecraft->rotationAngle + 180)) * 13, 13, -cos(radians(spacecraft->rotationAngle - 180)) * 13), spacecraft->position, vec3(X, Y, Z));
	}
	if (CameraMode == 1)
	{
		viewMat = lookAt(GameEngine::cameraPos, GameEngine::cameraPos + GameEngine::cameraFront, cameraUp);
	}
	if (CameraMode == 3) {
		viewMat = lookAt(spacecraft->position + glm::vec3(-sin(radians(spacecraft->rotationAngle + 180)) * 20, 20, -cos(radians(spacecraft->rotationAngle - 180)) * 20), spacecraft->position, vec3(X, Y, Z));
	}
	//viewMat = lookAt(vec3(0, 200, -200), vec3(2, -50, 80), vec3(0, 1, 0));
	
	//viewMat = translate(viewMat, vec3(0.0, 10.0, 0.0));
	glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMat));

	/*Model Matrix */
	modelMat = mat4(1.0);
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));

	/*REFERENCE Blending and Light */
	// Calculate and update light position.
	light0.coords.x = cos((PI / 360.0f)*theta);
	light0.coords.y = sin((PI / 360.0f)*theta);
	glUniform4fv(light0coordsLoc, 1, &light0.coords[0]);

	// Calculate and update blending parameter.
	if (theta <= 90.0f) alpha = theta / 90.0f;
	else alpha = (180.0f - theta) / 90.0f;
	glUniform1f(alphaLoc, alpha);

	// Calculate and update normal matrix.
	normalMat = transpose(inverse(mat3(viewMat)));
	glUniformMatrix3fv(normalMatLoc, 1, GL_FALSE, value_ptr(normalMat));

	modelMat = mat4(1.0);
	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, value_ptr(modelMat));


	// Draw Floor
	glUniform1ui(objectLoc, SPACEONE);
	glBindVertexArray(vao[SPACEONE]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	// Draw SkyBox.
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[SPACETWO]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	/*Create the Sky Box*/

	//Sky Box Right

	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(100, 0, 0));
	modelMat = glm::rotate(modelMat, 1.5708f, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Sky Box Left

	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(-100, 0, 0));
	modelMat = glm::rotate(modelMat, -1.5708f, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Sky Box Back
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(-10, 0, 0));
	modelMat = glm::rotate(modelMat, -3.1416f, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Sky Box Top 1
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(0, 15, -5));
	modelMat = glm::rotate(modelMat, 1.5708f, vec3(1, 0, 0));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	//Sky Box Top 2
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(0, 15, -5));
	modelMat = glm::rotate(modelMat, 1.5708f, vec3(1, 0, 0));
	modelMat = glm::rotate(modelMat, 3.1416f, vec3(0, 0, 1));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	//Sky Box Bottom 3
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(0, -50, -5));
	modelMat = glm::rotate(modelMat, 1.5708f, vec3(1, 0, 0));
	modelMat = glm::rotate(modelMat, 3.1416f, vec3(0, 0, 1));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	//Sky Box Bottom 4
	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(0, -50, -5));
	modelMat = glm::rotate(modelMat, 1.5708f, vec3(1, 0, 0));
	glUniformMatrix4fv(modelMatLoc, SPACETWO, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc, SPACETWO);
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);



	glUniform1ui(objectLoc, MENU);
	glBindVertexArray(vao[MENU]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	modelMat = mat4(1.0);

	modelMat = mat4(1.0);
	modelMat = glm::translate(modelMat, vec3(-15, -5, 0));
	//modelMat = glm::rotate(modelMat, -1.5708f, vec3(0, 1, 0));
	glUniformMatrix4fv(modelMatLoc, MENU, GL_FALSE, value_ptr(modelMat));
	glUniform1ui(objectLoc,	MENU);
	glBindVertexArray(vao[2]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	
	for (std::vector<GameObject*>::size_type i = 0; i != GameObjects.size(); i++) {
		GameObjects[i]->DrawScene();
	}

 	glutSwapBuffers();
}
 
void GameEngine::mouseMove(int x, int y)
{
	if (firstMouse)
	{
		lastX = x;
		lastY = y;
		firstMouse = false;
	}
	float xoffset = x - lastX;
	float yoffset = lastY - y;
	lastX = x;
	lastY = y;

	float sensitivity = 0.3f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	GameEngine::yaw += xoffset;
	GameEngine::pitch += yoffset;

	if (GameEngine::pitch > 89.0f) GameEngine::pitch = 89.0f;
	if (GameEngine::pitch < -89.0f) GameEngine::pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(GameEngine::yaw)) * cos(glm::radians(GameEngine::pitch));
	front.y = sin(glm::radians(GameEngine::pitch));
	front.z = sin(glm::radians(GameEngine::yaw)) * cos(glm::radians(GameEngine::pitch));
	GameEngine::cameraFront = glm::normalize(front);

	//forces mouse to stay in the window
	int win_w = glutGet(GLUT_WINDOW_WIDTH);
	int win_h = glutGet(GLUT_WINDOW_HEIGHT);
	if (x < 100 || x > win_w - 100)
	{
		lastX = win_w / 2;
		lastY = win_h / 2;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
	else if (y < 100 || win_h - 100)
	{
		lastX = win_w / 2.0f;
		lastY = win_h / 2.0f;
		glutWarpPointer(win_w / 2, win_h / 2);
	}
}
void keyInput(unsigned char key, int x, int y)
{
	float cameraSpeed = 0.2f;
	switch (key)
	{
	case 'w':
		GameEngine::cameraPos += cameraSpeed * GameEngine::cameraFront;
		break;
	case 's':
		GameEngine::cameraPos -= cameraSpeed * GameEngine::cameraFront;
		break;
	case 'a':
		GameEngine::cameraPos -= glm::normalize(glm::cross(GameEngine::cameraFront, cameraUp)) * cameraSpeed;
		break;
	case 'd':
		GameEngine::cameraPos += glm::normalize(glm::cross(GameEngine::cameraFront, cameraUp)) * cameraSpeed;
		break;
	case 27:
		exit(0);
		break;
	case 'c':
		debugMode = true;
		break;
	case 'v':
		debugMode = false;
		break;
	case 'r':
		CameraMode = 1;
		cout << CameraMode;
		break;
	case't':
		CameraMode = 2;
		cout << CameraMode;
		break;
	case'e':
		CameraMode = 3;
		cout << CameraMode;
		break;
	}
}
// Non Ascii keys input
void sKeyInput(int key, int x, int y)
{
	GameObject::specialKeys[key] = true;
	glutPostRedisplay();
}

void sKeyUp(int key, int x, int y)
{
	GameObject::specialKeys[key] = false;
	glutPostRedisplay();
}
void GameEngine::Update() // Update Function
{

	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	theta = theta + 1.0f * deltaTime / 100.0f;
	if (theta >= 180.0) theta -= 180.0f;
	
	if (debugMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	for (std::vector<GameObject*>::size_type i = 0; i != GameObjects.size(); i++) {
		GameObjects[i]->Update(deltaTime);
	}
	//Test collisions in a naive way for every pair of gameobjects (note calculations will explode when you increase the amount of gameobjects. Can you think of a better way?
	for (std::vector<GameObject*>::size_type i = 0; i != GameObjects.size(); i++) {
		for (std::vector<GameObject*>::size_type j = i + 1; j != GameObjects.size(); j++) {
			if (GameObjects[i]->collider != NULL) {
				if (GameObjects[i]->collider->collidesWith(GameObjects[j]->collider)) {
					GameObjects[i]->collides(GameObjects[j]->collider);
					GameObjects[j]->collides(GameObjects[i]->collider);
				}
			}
		}
	}

	glutPostRedisplay();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GameEngine::InitEngine(int argc, char **argv)
{
	
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	PlaySound("Background.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SpaceCraft Game.cpp");
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(resize);
	glutIdleFunc(Update);
	glutPassiveMotionFunc(mouseMove);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(sKeyInput);
	glutSpecialUpFunc(sKeyUp);


	glewExperimental = GL_TRUE;
	glewInit();

	SetUp();
}
//////
void GameEngine::addGameObject(GameObject *GameObject) {
	GameObjects.push_back(GameObject);
	GameObject->modelMatLoc = modelMatLoc;
	GameObject->SetUpDrawing();
}
void GameEngine::StartEngine()
{
	glutMainLoop();
	
}
