
#include "PhysicsComponent.h"

#include "../GameObject.h"
#include "TransformComponent.h"

PhysicsComponent::PhysicsComponent()
	: m_TransformComponent(nullptr),
	m_Mass(1),
	m_InverseMass(1),
	m_MinVelocity(0.0f),
	m_MaxVelocity(0.05f),
	m_MinAcceleration(0.0f),
	m_MaxAcceleration(5.0f),
	m_Velocity(glm::vec3(0.0f)),
	m_Acceleration(glm::vec3(0.0f)),
	m_AngularVelocity(glm::vec3(0.0f))
{}

void PhysicsComponent::BeginPlay()
{

}

void PhysicsComponent::Update()
{
	if (bCanMove == true)
		UpdatePlayerMovement();
}

std::string PhysicsComponent::GetComponentName() { return "PhysicsComponent"; }

void PhysicsComponent::SetMass(const unsigned int& _mass) { m_Mass = _mass; }
void PhysicsComponent::SetInverseMass(const unsigned int& _inverseMass) { m_InverseMass = _inverseMass; }
void PhysicsComponent::SetVelocity(const glm::vec3& _velocity){ m_Velocity = _velocity; }
void PhysicsComponent::SetVelocity(const glm::vec3& _velocity, float _minVelocity, float _maxVelocity)
{
	m_Velocity = _velocity;
	m_MinVelocity = _minVelocity;
	m_MaxVelocity = _maxVelocity;
}
void PhysicsComponent::SetAcceleration(const glm::vec3& _acceleration) { m_Acceleration = _acceleration; }
void PhysicsComponent::SetAcceleration(const glm::vec3& _acceleration, float _minAcceleration, float _maxAcceleration)
{
	m_Acceleration = _acceleration;
	m_MinAcceleration = _minAcceleration;
	m_MaxAcceleration = _maxAcceleration;
}
void PhysicsComponent::SetAngularVelocity(const glm::vec3& _angularVelocity) { m_AngularVelocity = _angularVelocity; }
void PhysicsComponent::SetAngularVelocity(const glm::vec3& _angularVelocity, float _minAcceleration, float _maxAcceleration)
{
	m_AngularVelocity = _angularVelocity;
	m_MinAcceleration = _minAcceleration;
	m_MaxAcceleration = _maxAcceleration;
}

const unsigned int& PhysicsComponent::GetMass() const { return m_Mass; }
const unsigned int& PhysicsComponent::GetInverseMass() const { return m_InverseMass; }
const glm::vec3& PhysicsComponent::GetVelocity() const { return m_Velocity; }
const float& PhysicsComponent::GetMinVelocity() const { return m_MinVelocity; }
const float& PhysicsComponent::GetMaxVelocity() const { return m_MaxVelocity; }
const glm::vec3& PhysicsComponent::GetAcceleration() const { return m_Acceleration; }
const float& PhysicsComponent::GetMinAccelertion() const { return m_MinAcceleration; }
const float& PhysicsComponent::GetMaxAccelertion() const { return m_MaxAcceleration; }
const glm::vec3& PhysicsComponent::GetAngularVelocity() const { return m_AngularVelocity; }

void PhysicsComponent::UpdatePlayerMovement()
{
	// Update Positions and Rotation
	PlayerMovement();
	PlayerRotation();
}

void PhysicsComponent::PlayerMovement() {
	glm::vec3 currentPos = m_TransformComponent->GetLocalPosition();
	currentPos += m_Velocity;	// change x
	m_TransformComponent->SetLocalPosition(currentPos);
}

void PhysicsComponent::PlayerRotation() {
	glm::vec3 currentRotation = m_TransformComponent->GetLocalRotation();
	currentRotation += m_AngularVelocity;	// change z
	m_TransformComponent->SetLocalRotation(currentRotation);
}

PhysicsComponent::~PhysicsComponent()
{

}