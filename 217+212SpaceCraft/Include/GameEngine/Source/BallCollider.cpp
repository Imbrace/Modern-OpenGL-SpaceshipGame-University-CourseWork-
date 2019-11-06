#include "GameEngine\Headers\BallCollider.h"

BallCollider::BallCollider(glm::vec3 * centre, float Radius) {
	this->ColliderCentre = centre;
	this->SphereRadius = Radius;
}


BallCollider::~BallCollider() {
}

float BallCollider::X() {
	return this->ColliderCentre->x - this->width / 2;
}
float BallCollider::Y() {
	return this->ColliderCentre->y - this->height / 2;
}
float BallCollider::Z() {
	return this->ColliderCentre->z + this->length / 2;
}

bool BallCollider::collidesWith(Collider* other) {
	float DistanceX;
	float DistanceY;
	float DistanceZ;

	if (other == NULL) {
		return false;
	}

	DistanceX = fabs(this->X() - other->X());
	DistanceZ = fabs(this->Z() - other->Z());

	return DistanceX + DistanceZ <= (SphereRadius * 2);
	
	//	return overlapX && overlapZ;
}


void BallCollider::Draw() {
	
}
