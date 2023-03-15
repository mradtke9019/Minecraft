#include "Shader.h"
#include "Log.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath, bool debug)
	: ShaderProgramID(0)
{
	this->debugShader = debug;
	VertexShaderText = ReadFile(vertexShaderPath);
	FragmentShaderText = ReadFile(fragmentShaderPath);
	ShaderProgramID = CompileShaders(VertexShaderText, FragmentShaderText);
}

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
	: ShaderProgramID(0), debugShader(false)
{
	VertexShaderText = ReadFile(vertexShaderPath);
	FragmentShaderText = ReadFile(fragmentShaderPath);
	ShaderProgramID = CompileShaders(VertexShaderText, FragmentShaderText);
}


void Shader::DebugOn()
{
	debugShader = true;
}

void Shader::DebugOff()
{
	debugShader = true;
};

GLuint Shader::GetAttribLocation(std::string shaderAttribute)
{
	int id = glGetAttribLocation(GetShaderProgramID(), shaderAttribute.c_str());
	if (id < 0 && debugShader)
	{
		Log::WriteLog("Error finding attrib '" + shaderAttribute + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}
	return id;
}

std::string Shader::GetVertexShaderText()
{
	return VertexShaderText;
}
std::string Shader::GetFragmentShaderText()
{
	return FragmentShaderText;
}

GLuint Shader::GetShaderProgramID()
{
	return ShaderProgramID;
}

void Shader::Use()
{
	glUseProgram(ShaderProgramID);
	//if (textureID > 0) {
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	//}
}

GLuint Shader::GetUniformLocation(const char* uniform)
{
	int uniformId = glGetUniformLocation(ShaderProgramID, uniform);
	if (uniformId < 0 && debugShader)
	{
		Log::WriteLog("Error finding uniform '" + std::string(uniform) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}
	return uniformId;
}

void Shader::SetUniform1i(const char* uniform, int value)
{
	Use();
	int uniformId = GetUniformLocation(uniform);
	if (uniformId < 0 && debugShader)
	{
		Log::WriteLog("Error setting uniform '" + std::string(uniform) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}
	glUniform1i(GetUniformLocation(uniform), value);
}

void Shader::SetUniform1f(const char* uniform, float value)
{
	Use();
	int uniformId = GetUniformLocation(uniform);
	if (uniformId < 0 && debugShader)
	{
		Log::WriteLog("Error setting uniform '" + std::string(uniform) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}
	glUniform1f(GetUniformLocation(uniform), value);
}

GLuint Shader::GetUniformMatrix4fv(const char* mat)
{
	int uniformId = glGetUniformLocation(ShaderProgramID, mat);
	if (uniformId < 0 && debugShader)
	{
		Log::WriteLog("Error finding uniform matrix'" + std::string(mat) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}
	return uniformId;
}

void Shader::SetUniformMatrix44fv(const char* mat, glm::mat4x4* matrix)
{
	Use();
	int id = GetUniformMatrix4fv(mat);
	if (id < 0 && debugShader) {
		Log::WriteLog("Error to set uniform matrix'" + std::string(mat) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}

	glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0][0]);
}

void Shader::SetUniformMatrix4fv(const char* mat, glm::mat4* matrix)
{
	Use();
	int id = GetUniformMatrix4fv(mat);
	if (id < 0 && debugShader) {
		Log::WriteLog("Error to set uniform matrix'" + std::string(mat) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}

	glUniformMatrix4fv(id, 1, GL_FALSE, &matrix[0][0][0]);
}

GLuint Shader::GetUniformVec3(const char* vec)
{
	Use();
	int id = glGetUniformLocation(ShaderProgramID, vec);
	if (id < 0 && debugShader) {
		Log::WriteLog("Unable to get vec3 '" + std::string(vec) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}

	return id;
}

void Shader::SetUniformVec3(const char* vec, glm::vec3 vector)
{
	Use();
	int id = GetUniformMatrix4fv(vec);
	if (id < 0 && debugShader) {
		Log::WriteLog("Unable to set vec3 '" + std::string(vec) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}
	glUniform3f(id, vector.x, vector.y, vector.z);
}

void Shader::SetUniformFloatArray(const char* name, const float arr[], int count)
{
	Use();
	int id = glGetUniformLocation(ShaderProgramID, name);
	if (id < 0 && debugShader) {
		Log::WriteLog("Unable to set uniform float '" + std::string(name) + "' in shader program id: '" + std::to_string(ShaderProgramID) + "'.", Debug);
	}

	glUniform1fv(id, count * sizeof(GLfloat), arr);
}