#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Component.h"

class TransformComponent : public Component
{
private:
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);

	// Dirty Flag
	bool m_dirty = true;

public:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	float moveSpeed = 0.05f;
	float rotateSpeed = 0.5f;

public:
	//Constructor
	TransformComponent();

	void BeginPlay() override;
	void Update() override;

	std::string GetComponentName() override;

	//getter for transform matrix, generally called model matrix
	glm::mat4 GetLocalModelMatrix() const;

	void ComputeModelMatrix();
	void ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix);

	void SetLocalTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	void SetLocalPosition(glm::vec3 newPosition);
	void SetLocalRotation(const glm::vec3& newRotation);
	void SetLocalScale(const glm::vec3& nonUniformScale);
	void SetLocalScale(const float& uniformScale);

	const glm::vec3& GetGlobalPosition() const;
	const glm::vec3& GetLocalPosition() const;
	const glm::vec3& GetLocalRotation() const;
	const glm::vec3& GetLocalScale() const;
	const glm::mat4& GetModelMatrix() const;

	// Movement function
	// TODO: Fix that
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void RotateClockwise();
	void RotateAntiClockwise();

	// DirtyFlag pattern
	const bool& GetDirtyFlag() const;
	void ClearDirtyFlag();
	void MakeDirty();

	// Serialize & Deserialize
	void Serialize();
	void Deserialize(rapidjson::Value& componentMember);

	virtual ~TransformComponent();
};