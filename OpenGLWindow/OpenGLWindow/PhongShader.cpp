#include "PhongShader.h"



PhongShader::PhongShader() : LitShader()
{
	loadShader((unsigned int)eShaderStage::VERTEX, "shaders/phong.vert");
	loadShader((unsigned int)eShaderStage::FRAGMENT, "shaders/phong.frag");
	link();

	SetLightCount(1);

	SetLight(0, { {10.0f,10.0f,10.0f}, vec4(1), vec4(1) });
}