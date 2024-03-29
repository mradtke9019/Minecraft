#include "Mesh.h"
// Inspiration for Mesh Class and cincepts here
// https://learnopengl.com/Model-Loading/Mesh


void Mesh::SetShader(Shader* shader)
{
    this->shader = shader;
}

Shader* Mesh::GetShader()
{
    return shader;
}

void Mesh::Draw(glm::mat4* ModelTransform)
{
    shader->Use();
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to std::string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to std::string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to std::string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader->GetShaderProgramID(), (name + number).c_str()), i);
        // and finally bind the texture

        glBindTexture(GL_TEXTURE_2D, textures[i].id);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        if (mipmap == "GL_NEAREST_MIPMAP_NEAREST")
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        }
        else if (mipmap == "GL_LINEAR_MIPMAP_NEAREST")
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        }
        else if (mipmap == "GL_NEAREST_MIPMAP_LINEAR")
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        }
        else if (mipmap == "GL_LINEAR_MIPMAP_LINEAR")
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        }
        // Default
        else {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        }
    }

    // Translate mesh back to origin, rotate, then re apply the translation
    glm::mat4 t = (*ModelTransform);

    shader->SetUniformMatrix4fv("model", &t);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);

}