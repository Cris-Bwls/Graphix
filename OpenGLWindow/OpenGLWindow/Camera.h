#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void Update(float fDeltaTime) = 0;

	void MakePerspective(float fFOV, float fAspectRatio, float fNear, float fFar);
	void MakeOrtho(float fWidth, float fHeight, float fNear, float fFar);
	void UpdateProjectionView();
	void SetLookAt(vec3 const& to, vec3 const& up);
	void SetPosition(vec3 const& pos);

	inline mat4 GetTransform() const& { return m_Transform; };
	inline mat4 GetView() const& { return m_View; };
	inline mat4 GetProjection() const& { return m_Projection; };
	inline mat4 GetProjectionView() const& { return m_ProjectionView; };
	inline bool GetIsPerspective() const { return m_bIsPerspective; };

protected:
	mat4 m_Transform;
	mat4 m_View;
	mat4 m_Projection;
	mat4 m_ProjectionView;
	bool m_bIsPerspective;

	float m_fNear;
	float m_fFar;
};

