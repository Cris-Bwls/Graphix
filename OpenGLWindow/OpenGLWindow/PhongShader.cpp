#include "PhongShader.h"



PhongShader::PhongShader() : LitShader()
{
	loadShader((unsigned int)eShaderStage::VERTEX, "shaders/phong.vert");
	loadShader((unsigned int)eShaderStage::FRAGMENT, "shaders/phong.frag");
	link();
	Use();
}