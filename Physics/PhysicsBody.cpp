#include "PhysicsBody.h"

PhysicsBody::PhysicsBody()
	: m_Velocity(glm::vec3(0.0f)), m_Accleration(glm::vec3(0.0f)), m_Mass(1.0f)
{

}

void PhysicsBody::BeginPlay()
{

}

void PhysicsBody::Update()
{

}

void PhysicsBody::SetVelocity(const glm::vec3& _velocity) { m_Velocity = _velocity; }
void PhysicsBody::SetAcceleration(const glm::vec3& _acceleration) { m_Accleration = _acceleration; }
void PhysicsBody::SetMass(const float& _mass) { m_Mass = _mass; }

glm::vec3& PhysicsBody::GetVelocity() { return m_Velocity; }
glm::vec3& PhysicsBody::GetAcceleration() { return m_Accleration; }
float& PhysicsBody::GetMass() { return m_Mass; }

PhysicsBody::~PhysicsBody()
{

}