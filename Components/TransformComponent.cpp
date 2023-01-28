#include "TransformComponent.h"

#include <iostream>

TransformComponent::TransformComponent()
	: m_position(glm::vec3(0.0f)),
	m_rotation(glm::vec3(0.0f)),
	m_scale(glm::vec3(1.0f))
{
	BeginPlay();
}

void TransformComponent::BeginPlay()
{

}

void TransformComponent::Update()
{
	
}

std::string TransformComponent::GetComponentName() { return "TransformComponent"; }

//getter for transform matrix, generally called model matrix
glm::mat4 TransformComponent::GetLocalModelMatrix() const {
	const glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	const glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	const glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	// Y * X * Z
	const glm::mat4 roationMatrix = rotationY * rotationX * rotationZ;

	// translation * rotation * scale (also know as TRS matrix)
	return glm::translate(glm::mat4(1.0f), m_position) * roationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
}

void TransformComponent::ComputeModelMatrix() { m_modelMatrix = GetLocalModelMatrix(); }
void TransformComponent::ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix) { m_modelMatrix = parentGlobalModelMatrix * GetLocalModelMatrix(); }

void TransformComponent::SetLocalTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	this->m_position = position;
	this->m_rotation = rotation;
	this->m_scale = scale;
	MakeDirty();
}

void TransformComponent::SetLocalPosition(glm::vec3 newPosition) {
	m_position = newPosition;
	MakeDirty();
}

void TransformComponent::SetLocalRotation(const glm::vec3& newRotation) {
	m_rotation = newRotation;
	MakeDirty();
}

void TransformComponent::SetLocalScale(const glm::vec3& newScale) {
	m_scale = newScale;
	MakeDirty();
}

void TransformComponent::SetLocalScale(const float& uniformScale)
{
	m_scale = glm::vec3(uniformScale);
	MakeDirty();
}

const glm::vec3& TransformComponent::GetGlobalPosition() const { return m_modelMatrix[3]; }
const glm::vec3& TransformComponent::GetLocalPosition() const { return m_position; }
const glm::vec3& TransformComponent::GetLocalRotation() const { return m_rotation; }
const glm::vec3& TransformComponent::GetLocalScale() const { return m_scale; }
const glm::mat4& TransformComponent::GetModelMatrix() const { return m_modelMatrix; }

/// <summary>
/// TODO: Fix this to GameObject based logic
/// Movement Mechanincs
/// </summary>
void TransformComponent::MoveUp() {
	glm::vec3 currentPos = GetLocalPosition();
	currentPos.y += moveSpeed;
	SetLocalPosition(currentPos);
}

void TransformComponent::MoveDown() {
	glm::vec3 currentPos = GetLocalPosition();
	currentPos.y -= moveSpeed;
	SetLocalPosition(currentPos);
}

void TransformComponent::MoveLeft() {
	glm::vec3 currentPos = GetLocalPosition();
	currentPos.x -= moveSpeed;
	SetLocalPosition(currentPos);
}

void TransformComponent::MoveRight() {
	glm::vec3 currentPos = GetLocalPosition();
	currentPos.x += moveSpeed;
	SetLocalPosition(currentPos);
}

void TransformComponent::RotateClockwise() {
	glm::vec3 currentRotation = GetLocalRotation();
	currentRotation.z += rotateSpeed;
	SetLocalRotation(currentRotation);
}

void TransformComponent::TransformComponent::RotateAntiClockwise() {
	glm::vec3 currentRotation = GetLocalRotation();
	currentRotation.z -= rotateSpeed;
	SetLocalRotation(currentRotation);
}

const bool& TransformComponent::GetDirtyFlag() const { return m_dirty; }
void TransformComponent::ClearDirtyFlag() { m_dirty = false; }
void TransformComponent::MakeDirty() { m_dirty = true; }

void TransformComponent::Serialize()
{

}

void TransformComponent::Deserialize(rapidjson::Value& componentMembers)
{
	std::cout << "Deserializing Transform Component!" << std::endl;

	rapidjson::Value& transformData = componentMembers.FindMember("Transform")->value;

	rapidjson::Value& posData	= transformData.FindMember("position")->value;
	rapidjson::Value& rotData	= transformData.FindMember("rotation")->value;
	rapidjson::Value& scaleData = transformData.FindMember("scale")->value;

	if (posData.IsArray())
	{
		glm::vec3 position;
		position.x = posData[0].GetFloat();
		position.y = posData[1].GetFloat();
		position.z = posData[2].GetFloat();

		SetLocalPosition(position);
	}

	if (rotData.IsArray())
	{
		glm::vec3 rotation;
		rotation.x = rotData[0].GetFloat();
		rotation.y = rotData[1].GetFloat();
		rotation.z = rotData[2].GetFloat();

		SetLocalRotation(rotation);
	}

	if (scaleData.IsArray())
	{
		glm::vec3 scale;
		scale.x = scaleData[0].GetFloat();
		scale.y = scaleData[1].GetFloat();
		scale.z = scaleData[2].GetFloat();

		SetLocalScale(scale);
	}
}

TransformComponent::~TransformComponent()
{}