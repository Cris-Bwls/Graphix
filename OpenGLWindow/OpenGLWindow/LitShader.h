#pragma once
#include "Shader.h"

#include <string>

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

class LitShader :
	public ShaderProgram
{
public:
	LitShader();
	~LitShader();

	struct Light
	{
		vec3 position;
		vec4 diffuse;
		vec4 specular;
	};

	bool SetLightCount(unsigned int count);
	bool SetLight(unsigned int index, LitShader::Light const& info);
	bool AddLight(LitShader::Light const& info, unsigned int* pGivenIndex = nullptr);

	void SetLightPos(unsigned int index, vec3 const& pos);
	void SetLightDiffuse(unsigned int index, vec4 const& diffuse);
	void SetLightSpecular(unsigned int index, vec4 const& specular);

	void SetAmbientLight(float ambient);

	void SetMVP(mat4 const& mvp);
	void SetViewMatrix(mat4 const& view);
	void SetModelMatrix(mat4 const& model);
	void SetNormalMatrix(mat3 const& normal);

private:
	std::string GetUniformName(std::string sAttrib, unsigned int index);

	unsigned int m_lightCount = 0;
};

