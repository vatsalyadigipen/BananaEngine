#pragma once

#include "../GameObject.h"
#include "../Components/InputComponent.h"
#include "../Components/TransformComponent.h"

class Enemy : public GameObject
{
private:
	float m_health;

public:
	Enemy();
	Enemy(const float& _health);
	Enemy(const std::string& _name);
	Enemy(const std::string& _name, const float& _health);
	~Enemy();

	void BeginPlay() override;
	void Update() override;
};