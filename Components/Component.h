#pragma once

#include <string>

#include "rapidjson/document.h"

class GameObject;

class Component
{
private:
	GameObject* m_owner = nullptr;
public:
	Component() {}
	virtual ~Component() {}

	virtual void BeginPlay() = 0;
	virtual void Update() = 0;

	// Store Component Name
	virtual std::string GetComponentName() = 0;

	// return owner
	void SetOwner(GameObject* owner) { m_owner = owner; }
	GameObject* GetOwner() { return m_owner; }

	virtual void Deserialize(rapidjson::Value& componentMember) = 0;
};