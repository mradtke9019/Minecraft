#include "Model.h"

Model::Model(std::string path, Shader* Shader)
{
	shader = Shader;
	ObjectColor = glm::vec3(1.0, 0.0, 0.0);
	loadModel(path);
}

void Model::Draw(glm::mat4 *ModelTransform)
{
	shader->Use();
	shader->SetUniformMatrix4fv("model", ModelTransform);
	shader->SetUniformVec3("ObjectColor", ObjectColor);
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes.at(i).Draw(ModelTransform);
	}
}

// draws the modell with the given transform overriding the existing one
void Model::Draw(glm::mat4 transform)
{
	shader->Use();
	shader->SetUniformMatrix4fv("model", &transform);
	shader->SetUniformVec3("ObjectColor", ObjectColor);
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes.at(i).Draw(&transform);
	}
}

Shader* Model::GetShader()
{
	return shader;
}

void Model::SetShader(Shader* Shader)
{
	shader = Shader;
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes.at(i).SetShader(shader);
	}
}
