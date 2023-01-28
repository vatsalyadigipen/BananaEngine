#pragma once

#include "Component.h"

class GameObject;

class InputComponent : public Component
{
public:
	InputComponent();
	virtual ~InputComponent();

	void BeginPlay() override;
	void Update() override;

	std::string GetComponentName() override;

	// Serialize & Deserialize
	void Serialize();
	void Deserialize(rapidjson::Value& componentMember);

private:
	void CheckForInput(GameObject* object);
};