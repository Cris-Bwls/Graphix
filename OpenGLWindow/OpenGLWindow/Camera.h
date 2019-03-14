#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

enum class Projection
{
	Ortho,
	Perspective
};

class Camera
{
public:
	Camera();
	~Camera();

	mat4 m_View;
	mat4 m_Projection;
	Projection m_ProjectionType;
};

