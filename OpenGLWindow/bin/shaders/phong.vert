#version 410

layout(location=0)in vec4 Position;
layout(location=1)in vec4 Normal;
layout(location=2)in vec2 TexCoord;
layout(location=3)in vec4 Tangent;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 MVP;
uniform mat3 NormalMatrix;

out vec3 vertNormal;
out vec3 vertPos;
out vec3 viewPos;
out vec2 uv;
out vec4 tangent;

void main() {
    vertNormal = NormalMatrix * Normal.xyz;

    vec4 pos = MVP * Position;
    gl_Position = pos;

    vertPos = (Model*Position).xyz;

    viewPos = (inverse(View)[3]).xyz;

	uv = TexCoord;
    tangent = Tangent;
}