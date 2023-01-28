#pragma once

#include "../GameObject.h"
#include "../Components/InputComponent.h"
#include "../Components/TransformComponent.h"

class Player : public GameObject
{
private:
	float m_health;

public:
	Player();
	Player(const float& _health);
	Player(const std::string& _name);
	Player(const std::string& _name, const float& _health);
	~Player();

	void BeginPlay() override;
	void Update() override;
};