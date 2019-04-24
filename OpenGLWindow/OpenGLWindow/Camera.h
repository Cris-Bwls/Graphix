#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	/*
		@brief Performs Update, pure virtual
		@param deltaTime
	*/
	virtual void Update(float fDeltaTime) = 0;

	/*
		@brief Makes Camera perspective
		@param Field of View
		@param Aspect Ratio
		@param Near Clipping Plane
		@param Far Clipping Plane
	*/
	void MakePerspective(float fFOV, float fAspectRatio, float fNear, float fFar);

	/*
		@brief Makes Camera orthogonal
		@param view width
		@param view Height
		@param Near Clipping Plane
		@param Far Clipping Plane
	*/
	void MakeOrtho(float fWidth, float fHeight, float fNear, float fFar);

	/*
		@brief Updates the Projection View
	*/
	void UpdateProjectionView();

	/*
		@brief Makes Camera Look at a position
		@param position to look at
		@param up vector
	*/
	void SetLookAt(vec3 const& to, vec3 const& up);

	/*
		@brief Set Cameras current position
		@param position
	*/
	void SetPosition(vec3 const& pos);

	/*
		@brief Rotates Camera on around axis
		@param Amount to rotate
		@param Axis to rotate around
	*/
	void Rotate(float fAngle, vec3 const& axis);

	/*
		@brief Get Camera Transform
		@return Camera Transform
	*/
	inline mat4 GetTransform() const& { return m_Transform; };

	/*
		@brief Get Camera View
		@return Camera View
	*/
	inline mat4 GetView() const& { return m_View; };

	/*
		@brief Get Camera Projection
		@return Camera Projection
	*/
	inline mat4 GetProjection() const& { return m_Projection; };

	/*
		@brief Get Camera ProjectionView
		@return Camera ProjectionView
	*/
	inline mat4 GetProjectionView() const& { return m_ProjectionView; };

	/*
		@brief Get if camera is persepective
		@return If Camera is Perspective
	*/
	inline bool GetIsPerspective() const { return m_bIsPerspective; };

protected:
	vec3 m_RotTo;

	mat4 m_Transform;
	mat4 m_View;
	mat4 m_Projection;
	mat4 m_ProjectionView;
	bool m_bIsPerspective;

	float m_fNear;
	float m_fFar;
};

