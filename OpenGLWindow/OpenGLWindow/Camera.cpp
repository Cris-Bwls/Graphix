#include "Camera.h"

Camera::Camera(){}
Camera::~Camera(){}

/*
	@brief Makes Camera perspective
	@param Field of View
	@param Aspect Ratio
	@param Near Clipping Plane
	@param Far Clipping Plane
*/
void Camera::MakePerspective(float fFOV, float fAspectRatio, float fNear, float fFar)
{
	m_Projection = glm::perspective(fFOV, fAspectRatio, fNear, fFar);
	m_bIsPerspective = true;
}

/*
	@brief Makes Camera orthogonal
	@param view width
	@param view Height
	@param Near Clipping Plane
	@param Far Clipping Plane
*/
void Camera::MakeOrtho(float fWidth, float fHeight, float fNear, float fFar)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;

	m_Projection = glm::ortho(-fHalfWidth, fHalfWidth, -fHalfHeight, fHalfHeight, fNear, fFar);
	m_bIsPerspective = false;
}

/*
	@brief Updates the Projection View
*/
void Camera::UpdateProjectionView()
{
	m_ProjectionView = m_Projection * m_View;
}

/*
	@brief Makes Camera Look at a position
	@param position to look at
	@param up vector
*/
void Camera::SetLookAt(vec3 const & to, vec3 const & up)
{
	vec3 pos = m_Transform[3];
	m_View = glm::lookAt(to, pos, up);
	m_Transform = glm::inverse(m_View);
}

/*
	@brief Set Cameras current position
	@param position
*/
void Camera::SetPosition(vec3 const & pos)
{
	m_Transform[3] = { pos, 1 };
	m_View = glm::inverse(m_Transform);
}

/*
	@brief Rotates Camera on around axis
	@param Amount to rotate
	@param Axis to rotate around
*/
void Camera::Rotate(float fAngle, vec3 const & axis)
{
	m_Transform = glm::rotate(m_Transform, fAngle, axis);
	m_View = glm::inverse(m_Transform);
}
