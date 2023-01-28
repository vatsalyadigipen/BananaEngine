#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

class Transform
{
private:
	glm::mat4 m_modelMatrix = glm::mat4(1.0f);

	bool m_dirty = true;

public:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	float moveSpeed = 0.05f;
	float rotateSpeed = 0.5f;

	Transform()
		: m_position(glm::vec3(0.0f)),
		m_rotation(glm::vec3(0.0f)),
		m_scale(glm::vec3(1.0f))
	{}

	//getter for transform matrix, generally called model matrix
	glm::mat4 GetLocalModelMatrix() const {
		const glm::mat4 rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		const glm::mat4 rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		const glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		// Y * X * Z
		const glm::mat4 roationMatrix = rotationY * rotationX * rotationZ;

		// translation * rotation * scale (also know as TRS matrix)
		return glm::translate(glm::mat4(1.0f), m_position) * roationMatrix * glm::scale(glm::mat4(1.0f), m_scale);
	}

	void ComputeModelMatrix() { m_modelMatrix = GetLocalModelMatrix(); }
	void ComputeModelMatrix(const glm::mat4& parentGlobalModelMatrix) { m_modelMatrix = parentGlobalModelMatrix * GetLocalModelMatrix(); }

	void SetLocalTransform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		this->m_position = position;
		this->m_rotation = rotation;
		this->m_scale = scale;

		MakeDirty();
	}

	void SetLocalPosition(glm::vec3 newPosition) {
		m_position = newPosition;
		MakeDirty();
	}

	void SetLocalRotation(const glm::vec3& newRotation) {
		m_rotation = newRotation;
		MakeDirty();
	}

	void SetLocalScale(const glm::vec3& newScale) {
		m_scale = newScale;
		MakeDirty();
	}

	const glm::vec3& GetGlobalPosition() const { return m_modelMatrix[3]; }
	const glm::vec3& GetLocalPosition() const { return m_position; }
	const glm::vec3& GetLocalRotation() const { return m_rotation; }
	const glm::vec3& GetLocalScale() const { return m_scale; }
	const glm::mat4& GetModelMatrix() const { return m_modelMatrix; }

	void MoveUp() {
		glm::vec3 currentPos = GetLocalPosition();
		currentPos.y += moveSpeed;
		SetLocalPosition(currentPos);
	}

	void MoveDown() {
		glm::vec3 currentPos = GetLocalPosition();
		currentPos.y -= moveSpeed;
		SetLocalPosition(currentPos);
	}

	void MoveLeft() {
		glm::vec3 currentPos = GetLocalPosition();
		currentPos.x -= moveSpeed;
		SetLocalPosition(currentPos);
	}

	void MoveRight() {
		glm::vec3 currentPos = GetLocalPosition();
		currentPos.x += moveSpeed;
		SetLocalPosition(currentPos);
	}

	void RotateClockwise() {
		glm::vec3 currentRotation = GetLocalRotation();
		currentRotation.z += rotateSpeed;
		SetLocalRotation(currentRotation);
	}

	void RotateAntiClockwise() {
		glm::vec3 currentRotation = GetLocalRotation();
		currentRotation.z -= rotateSpeed;
		SetLocalRotation(currentRotation);
	}

	const bool& GetDirtyFlag() const { return m_dirty; }
	void ClearDirtyFlag() { m_dirty = false; }

	void MakeDirty() { m_dirty = true; }
private:
};