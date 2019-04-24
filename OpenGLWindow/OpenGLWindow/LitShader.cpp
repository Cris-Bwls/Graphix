#include "LitShader.h"

#define MAX_LIGHTS 8

LitShader::LitShader() : ShaderProgram()
{
}


LitShader::~LitShader()
{
}

/*
	@brief Sets Light Count
	@param New light count
	@return Is new light count within bounds
*/
bool LitShader::SetLightCount(unsigned int count)
{
	if (count > MAX_LIGHTS)
		return false;

	m_lightCount = count;

	Use();
	bindUniform("lightCount", (int)count);

	return true;
}

/*
	@brief Sets Light info at index
	@param Index of light
	@param Light info
	@return Is index within bounds
*/
bool LitShader::SetLight(unsigned int index, LitShader::Light const & info)
{
	if (index > m_lightCount)
		return false;

	SetLightPos(index, info.position);
	SetLightDiffuse(index, info.diffuse);
	SetLightSpecular(index, info.specular);

	return true;
}

/*
	@brief Sets Light info at index
	@param Light info
	@param Index of light as pointer
	@return Was Successful in adding light
*/
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

/*
	@brief Sets Position of Light at index
	@param Index of light
	@param New Position
*/
void LitShader::SetLightPos(unsigned int index, vec3 const & pos)
{
	Use();
	bindUniform(GetUniformName("pos", index).c_str(), pos);
}

/*
	@brief Sets Diffuse of Light at index
	@param Index of light
	@param New Diffuse
*/
void LitShader::SetLightDiffuse(unsigned int index, vec4 const & diffuse)
{
	Use();
	bindUniform(GetUniformName("diffuse", index).c_str(), diffuse);
}

/*
	@brief Sets Specular of Light at index
	@param Index of light
	@param New Specular
*/
void LitShader::SetLightSpecular(unsigned int index, vec4 const & specular)
{
	Use();
	bindUniform(GetUniformName("specular", index).c_str(), specular);
}

/*
	@brief Sets Ambient Light
	@param Ambient light
*/
void LitShader::SetAmbientLight(float ambient)
{
	Use();
	bindUniform("lightAmbient", ambient);
}

/*
	@brief Sets ModelViewProjection
	@param ModelViewProjection
*/
void LitShader::SetMVP(mat4 const & mvp)
{
	Use();
	bindUniform("MVP", mvp);
}

/*
	@brief Sets View Matrix
	@param View Matrix
*/
void LitShader::SetViewMatrix(mat4 const & view)
{
	Use();
	bindUniform("View", view);
}

/*
	@brief Sets Model Matrix
	@param Model Matrix
*/
void LitShader::SetModelMatrix(mat4 const & model)
{
	Use();
	bindUniform("Model", model);
}

/*
	@brief Sets Normal Matrix
	@param Normal Matrix
*/
void LitShader::SetNormalMatrix(mat3 const & normal)
{
	Use();
	bindUniform("NormalMatrix", normal);
}

/*
	@brief Creates Uniform String with array index
	@param Uniform Attribute
	@param  Array index
	@return Uniform String with array index
*/
std::string LitShader::GetUniformName(std::string sAttrib, unsigned int index)
{
	return "lights[" + std::to_string(index) + "]." + sAttrib;
}
