#include "GameObjects/Headers\GameObject.h"


GameObject::GameObject(glm::vec3 position)
{
	this->position = position;
}

GameObject::~GameObject()
{
}
void GameObject::SetUpDrawing() {

}
void GameObject::DrawScene()
{
	//modelViewMat = mat4(1.0);
	//modelViewMat = lookAt(vec3(0.0, 10.0 + GameObject::d3, 15.0 + GameObject::d2), vec3(0.0, 10.0 + GameObject::d, 0.0), vec3(0.0, 1.0, 0.0));
	//modelViewMat = translate(modelViewMat, vec3(0.0, 0.0f, 0.0));
}

void GameObject::Update(int deltaTime)
{
}


void GameObject::collides(Collider * other)
{
}
