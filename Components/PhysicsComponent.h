#pragma once

#include "Component.h"

class TransformComponent;

#include <glm/glm.hpp>

class PhysicsComponent : public Component
{
public:
	bool bCanMove = true;

private:
	TransformComponent* m_TransformComponent;

	unsigned int m_Mass;
	unsigned int m_InverseMass;

	float m_MinVelocity;
	float m_MaxVelocity;
	float m_MinAcceleration;	// use same for angular acceleration
	float m_MaxAcceleration;	// use same for angular acceleration

	glm::vec3 m_Velocity;
	glm::vec3 m_Acceleration;
	glm::vec3 m_AngularVelocity;

public:
	PhysicsComponent();
	virtual ~PhysicsComponent();

	// Virtual Methods
	void BeginPlay() override;
	void Update() override;
	std::string GetComponentName() override;

	// Add Transform Component
	void AddTransformComponent(TransformComponent* _transformComponent) { m_TransformComponent = _transformComponent; }
	TransformComponent* GetTransformComponent() { return m_TransformComponent; }

	//////////////////////////////
	///Getter and Setter Below ///
	//////////////////////////////

	void SetMass(const unsigned int& _mass);
	void SetInverseMass(const unsigned int& _inverseMass);
	void SetVelocity(const glm::vec3& _velocity);	// assumes [min, max] = [0, 5]
	void SetVelocity(const glm::vec3& _velocity, float _minVelocity, float _maxVelocity);
	void SetAcceleration(const glm::vec3& _acceleration);	// assumes [min, max] = [0, 5]
	void SetAcceleration(const glm::vec3& _acceleration, float _minAcceleration, float _maxAcceleration);
	void SetAngularVelocity(const glm::vec3& _angularVelocity);	// assumes [min, max] = [0, 5]
	void SetAngularVelocity(const glm::vec3& _angularVelocity, float _minAcceleration, float _maxAcceleration);

	const unsigned int& GetMass() const;
	const unsigned int& GetInverseMass() const;
	const glm::vec3& GetVelocity() const;
	const float& GetMinVelocity() const;
	const float& GetMaxVelocity() const;
	const glm::vec3& GetAcceleration() const;
	const float& GetMinAccelertion() const;
	const float& GetMaxAccelertion() const;
	const glm::vec3& GetAngularVelocity() const;

	// TODO: Instead of 4 Move functions implement MoveHorizontal/MoveVertical later
	void PlayerMovement();
	void PlayerRotation();

	void UpdatePlayerMovement();

	// Serialize & Deserialize
	void Serialize() {}	// empty body
	void Deserialize(rapidjson::Value& componentMember) {}	// empty body
};