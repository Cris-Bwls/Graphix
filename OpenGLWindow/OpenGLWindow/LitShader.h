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

	/*
		@brief Sets Light Count
		@param New light count
		@return Is new light count within bounds
	*/
	bool SetLightCount(unsigned int count);

	/*
		@brief Sets Light info at index
		@param Index of light
		@param Light info
		@return Is index within bounds
	*/
	bool SetLight(unsigned int index, LitShader::Light const& info);

	/*
		@brief Sets Light info at index
		@param Light info
		@param Index of light as pointer
		@return Was Successful in adding light
	*/
	bool AddLight(LitShader::Light const& info, unsigned int* pGivenIndex = nullptr);

	/*
		@brief Sets Position of Light at index
		@param Index of light
		@param New Position
	*/
	void SetLightPos(unsigned int index, vec3 const& pos);

	/*
		@brief Sets Diffuse of Light at index
		@param Index of light
		@param New Diffuse
	*/
	void SetLightDiffuse(unsigned int index, vec4 const& diffuse);

	/*
		@brief Sets Specular of Light at index
		@param Index of light
		@param New Specular
	*/
	void SetLightSpecular(unsigned int index, vec4 const& specular);

	/*
		@brief Sets Ambient Light
		@param Ambient light
	*/
	void SetAmbientLight(float ambient);

	/*
		@brief Sets ModelViewProjection
		@param ModelViewProjection
	*/
	void SetMVP(mat4 const& mvp);

	/*
		@brief Sets View Matrix
		@param View Matrix
	*/
	void SetViewMatrix(mat4 const& view);

	/*
		@brief Sets Model Matrix
		@param Model Matrix
	*/
	void SetModelMatrix(mat4 const& model);

	/*
		@brief Sets Normal Matrix
		@param Normal Matrix
	*/
	void SetNormalMatrix(mat3 const& normal);

private:
	/*
		@brief Creates Uniform String with array index
		@param Uniform Attribute
		@param  Array index
		@return Uniform String with array index
	*/
	std::string GetUniformName(std::string sAttrib, unsigned int index);

	unsigned int m_lightCount = 0;
};

