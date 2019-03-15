#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::MakePerspective(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	m_Projection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
	m_bIsPerspective = true;
}

void Camera::MakeOrtho(float fWidth, float fHeight, float fNear, float fFar)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;

	m_Projection = glm::ortho(-fHalfWidth, fHalfWidth, -fHalfHeight, fHalfHeight, fNear, fFar);
	m_bIsPerspective = false;
}

void Camera::UpdateProjectionView()
{
	m_ProjectionView = m_Projection * m_View;
}

void Camera::SetLookAt(vec3 const & to, vec3 const & up)
{
	vec3 pos = { m_Transform[3].x, m_Transform[3].y, m_Transform[3].z };
	m_View = glm::lookAt(to, pos, up);
	m_Transform = glm::inverse(m_View);
}

void Camera::SetPosition(vec3 const & pos)
{
	m_Transform[3] = { pos, 1 };
	m_View = glm::inverse(m_Transform);
}
