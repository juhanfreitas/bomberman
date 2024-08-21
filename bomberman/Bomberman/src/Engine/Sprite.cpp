/**********************************************************************************
// Sprite (C�digo Fonte)
// 
// Cria��o:     11 Jul 2007
// Atualiza��o: 07 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de membros est�ticos das classes

// valores de profundidade predefinidos
const float Layer::FRONT  = 0.01f;
const float Layer::UPPER  = 0.25f;
const float Layer::MIDDLE = 0.50f;
const float Layer::LOWER  = 0.75f;
const float Layer::BACK   = 0.99f;

// ---------------------------------------------------------------------------------

void Sprite::InitSpriteData()
{
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
    sprite.texCoord.x = 0;
    sprite.texCoord.y = 0;
    sprite.texSize.x = 1;
    sprite.texSize.y = 1;
}

// ---------------------------------------------------------------------------------


Sprite::Sprite(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;
    
    // configura sprite
    InitSpriteData();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(const Image * img)
{
    // aponta para imagem externa
    image = img;
    localImage = false;

    // configura sprite
    InitSpriteData();
}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
    if (localImage)
        delete image;
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z)
{
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(&sprite);
}

// ---------------------------------------------------------------------------------