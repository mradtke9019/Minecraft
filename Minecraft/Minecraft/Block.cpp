#include "Block.h"
#include "Constants.h"

Block::Block(Shader* s, std::map<BlockType, Texture*>* texMap)
	: ITransformable()
{
	//model = m;
    shader = s;
	visible = true;
    BlockTexture = BlockType::Grass;
    TextureMap = texMap;
    


    int size = (288 + 1) * sizeof(float); // Size of array in bytes (add 1 for null terminator)
    cubeData = new float[288] {
  
        //Positions (3)   //Tex Coords (2) //Normals (3)
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
    };

        glGenVertexArrays(1, &CubeVAO);
        glGenBuffers(1, &CubeVBO);
        glBindVertexArray(CubeVAO);
        glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
        glBufferData(GL_ARRAY_BUFFER, size, cubeData, GL_STATIC_DRAW);


        // position attribute 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // normal attribute 
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);     

       /* for (int i = 0; i < textures.size(); i++) {
            Textures.push_back(textures[i]);
        }*/
   
}

void Block::Draw()
{
	if (!visible)
	{
		return;
	}
	

    shader->Use();
    shader->SetUniformMatrix4fv("model", GetTransformPointer());
    glBindVertexArray(CubeVAO);
    

    for (int i = 0; i < NumVerticesPerFace; i++) 
    {   
        if (i == 5 && BlockTexture == BlockType::Grass) {
            Texture* tex = (*TextureMap)[BlockType::GrassTop];
            tex->Bind();
            glDrawArrays(GL_TRIANGLES, i * NumVerticesPerFace, NumVerticesPerFace);
            continue;
        }
        Texture* tex = (*TextureMap)[BlockTexture];
        tex->Bind();
        glDrawArrays(GL_TRIANGLES, i * NumVerticesPerFace, NumVerticesPerFace);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(0);
    }


   /* switch (BlockTexture)
    {
    case BlockType::None:
        break;
    case BlockType::Grass:
        SetTextureTop(BlockType::Diamond);
        SetTextureBottom(BlockType::Carpet);
        break;
    case BlockType::Stone:
        SetTextureTop(BlockType::Diamond);
        SetTextureBottom(BlockType::Carpet);
        break;
    case BlockType::Gold:
        SetTextureTop(BlockType::Diamond);
        SetTextureBottom(BlockType::Carpet);
        break;
    case BlockType::Coal:
        SetTextureTop(BlockType::Diamond);
        SetTextureBottom(BlockType::Carpet);
        break;
    case BlockType::Diamond:
        SetTextureTop(BlockType::Diamond);
        SetTextureBottom(BlockType::Carpet);
        break;
    case BlockType::Carpet:
        SetTextureTop(BlockType::Diamond);
        SetTextureBottom(BlockType::Carpet);
        break;
    default:
        break;
    }*/
    //glBindVertexArray(0);

}

BlockType Block::GetBlockType()
{
    return BlockTexture;
}

void Block::SetBlockType(BlockType bType)
{
    BlockTexture = bType;
}

void Block::SetVisibility(bool v)
{
	visible = v;
}

bool Block::IsVisible()
{
	return visible;
}

void Block::SetTextureTop(BlockType blockTexture)
{
    //vertices for top of cube are stored at the end of the VBO
    //starting location in BVO is 30 i.e. 5 * 6 
    Texture* tex = (*TextureMap)[blockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 5 * NumVerticesPerFace, NumVerticesPerFace);
    //tex->Unbind();
}

void Block::SetTextureBottom(BlockType blockTexture)
{
    Texture* tex = (*TextureMap)[blockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 4 * NumVerticesPerFace, NumVerticesPerFace);
}

void Block::SetTextureLeft(BlockType blockTexture)
{
    Texture* tex = (*TextureMap)[blockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 3 * NumVerticesPerFace, NumVerticesPerFace);
}

void Block::SetTextureRight(BlockType blockTexture)
{
    Texture* tex = (*TextureMap)[blockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 2 * NumVerticesPerFace, NumVerticesPerFace);
}

void Block::SetTextureFront(BlockType blockTexture)
{
    Texture* tex = (*TextureMap)[blockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 1 * NumVerticesPerFace, NumVerticesPerFace);
}

void Block::SetTextureBack(BlockType blockTexture)
{
    Texture* tex = (*TextureMap)[blockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 0 * NumVerticesPerFace, NumVerticesPerFace);
}


void Block::DrawGrassTexture()
{
    Texture* tex = (*TextureMap)[BlockTexture];
    //Texture* tex = TextureMap[BlockTexture];
    tex->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);

    tex->Unbind();

   
}

void Block::DrawStoneTexture()
{
}

void Block::DrawGoldTexture()
{
}

void Block::DrawCoalTexture()
{
}

void Block::DrawDiamondTexture()
{
}

void Block::DrawCarpetTexture()
{
}
