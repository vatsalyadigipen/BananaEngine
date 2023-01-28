#include "Enemy.h"

Enemy::Enemy()
	: m_health(100.0f)
{
	BeginPlay();
}

Enemy::Enemy(const float& _health)
	: m_health(_health)
{
	BeginPlay();
}

Enemy::Enemy(const std::string& _name)
	: m_health(100.0f)
{
	SetObjectName(_name);

	BeginPlay();
}

Enemy::Enemy(const std::string& _name, const float& _health)
	: m_health(_health)
{
	SetObjectName(_name);

	BeginPlay();
}

void Enemy::BeginPlay()
{

}

void Enemy::Update()
{
	updateSelfAndChild();
}

Enemy::~Enemy()
{

}