#pragma once

#include "glm/glm.hpp"

class PhysicsBody
{
private:
	glm::vec3 m_Velocity;
	glm::vec3 m_Accleration;
	float m_Mass;

public:
	PhysicsBody();
	~PhysicsBody();

	void BeginPlay();
	void Update();

	// Getters and Setters
	void SetVelocity(const glm::vec3& _velocity);
	void SetAcceleration(const glm::vec3& _acceleration);
	void SetMass(const float& _mass);

	glm::vec3& GetVelocity();
	glm::vec3& GetAcceleration();
	float& GetMass();
};