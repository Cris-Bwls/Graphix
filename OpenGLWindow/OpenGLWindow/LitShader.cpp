#include "LitShader.h"

#define MAX_LIGHTS 8

LitShader::LitShader() : ShaderProgram()
{
}


LitShader::~LitShader()
{
}

bool LitShader::SetLightCount(unsigned int count)
{
	if (count > MAX_LIGHTS)
		return false;

	m_lightCount = count;
	bindUniform("LightCount", (int)count);

	return true;
}

bool LitShader::SetLight(unsigned int index, LitShader::Light const & info)
{
	if (index > m_lightCount)
		return false;

	SetLightPos(index, info.position);
	SetLightDiffuse(index, info.diffuse);
	SetLightSpecular(index, info.specular);

	return true;
}

bool LitShader::AddLight(LitShader::Light const & info, unsigned int * pGivenIndex)
{
	if (!SetLightCount(m_lightCount + 1))
		return false;

	if (!SetLight(m_lightCount, info))
		return false;

	if (pGivenIndex)
		*pGivenIndex = m_lightCount;
	return true;
}

void LitShader::SetLightPos(unsigned int index, vec3 const & pos)
{
	bindUniform(GetUniformName("pos", index).c_str(), pos);
}

void LitShader::SetLightDiffuse(unsigned int index, vec3 const & diffuse)
{
	bindUniform(GetUniformName("diffuse", index).c_str(), diffuse);
}

void LitShader::SetLightSpecular(unsigned int index, vec3 const & specular)
{
	bindUniform(GetUniformName("specular", index).c_str(), specular);
}

void LitShader::SetAmbientLight(float ambient)
{
	bindUniform("lightAmbient", ambient);
}

void LitShader::SetMVP(mat4 const & mvp)
{
	bindUniform("MVP", mvp);
}

void LitShader::SetViewMatrix(mat4 const & view)
{
	bindUniform("View", view);
}

void LitShader::SetModelMatrix(mat4 const & model)
{
	bindUniform("Model", model);
}

void LitShader::SetNormalMatrix(mat3 const & normal)
{
	bindUniform("NormalMatrix", normal);
}

std::string LitShader::GetUniformName(std::string sAttrib, unsigned int index)
{
	return "lights[" + std::to_string(index) + "]." + sAttrib;
}