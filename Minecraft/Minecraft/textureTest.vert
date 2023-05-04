#version 330

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec2 vTexture;
layout (location = 2) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 LightColor;
uniform vec3 LightPosition;  

out vec3 fNormal;
out vec3 fPosition;
out vec2 TexCoord;

void main()                                                              
{
	gl_Position = projection * view * model * vec4(vPosition, 1.0);

	fPosition = vec3(gl_Position);
	fNormal =  transpose(inverse(mat3(model))) * vNormal;
	TexCoord = vec2(vTexture.x, vTexture.y);
}
