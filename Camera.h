#pragma once

#include "Transform.h"
#include "Mesh.h"

#include <glm/glm.hpp>

// Singleton Class
class Camera
{
private:
	static Camera* m_Instance;

	glm::mat4 m_Projection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, -1.0f, 1.0f);
	glm::mat4 m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

public:
	static Camera& GetInstance();

	// TODO: Fix this don't return a copy
	glm::mat4 GetViewProjection() const;
	const glm::mat4& GetProjection() const;
	const glm::mat4& GetView() const;

	void SetViewProjection(const glm::mat4& _projection, const glm::mat4& _view);

private:
	Camera() {}
};