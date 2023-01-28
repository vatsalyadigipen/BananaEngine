#include "Player.h"

Player::Player()
	: m_health(100.0f)
{
	BeginPlay();
}

Player::Player(const float& _health)
	: m_health(_health)
{
	BeginPlay();
}

Player::Player(const std::string& _name)
	: m_health(100.0f)
{
	SetObjectName(_name);

	BeginPlay();
}

Player::Player(const std::string& _name, const float& _health)
	: m_health(_health)
{
	SetObjectName(_name);

	BeginPlay();
}

void Player::BeginPlay()
{
	
}

void Player::Update()
{
	InputComponent* IC_ = (InputComponent*)(this->FindComponent<InputComponent>());
	PhysicsComponent* PC_ = (PhysicsComponent*)(this->FindComponent<PhysicsComponent>());
	if (IC_)
		IC_->Update();

	if (PC_)
		PC_->Update();
	
	updateSelfAndChild();
}

Player::~Player()
{
	
}