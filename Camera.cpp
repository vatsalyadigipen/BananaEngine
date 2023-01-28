#include "Camera.h"

Camera* Camera::m_Instance = nullptr;

Camera& Camera::GetInstance()
{
	static Camera instance_;
	return instance_;
}

glm::mat4 Camera::GetViewProjection() const { return m_Projection * m_View; }
const glm::mat4& Camera::GetProjection() const { return m_Projection; }
const glm::mat4& Camera::GetView() const { return m_View; }

void Camera::SetViewProjection(const glm::mat4& _projection, const glm::mat4& _view)
{
	m_Projection = _projection;
	m_View = _view;
}