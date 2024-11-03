/**********************************************************************************
// Sprite (Código Fonte)
// 
// Criação:     11 Jul 2007
// Atualização: 23 Ago 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para representar um sprite
//
**********************************************************************************/

#include "Sprite.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de membros estáticos das classes

// valores de profundidade predefinidos
const float Layer::FRONT  = 0.01f;
const float Layer::UPPER  = 0.25f;
const float Layer::MIDDLE = 0.50f;
const float Layer::LOWER  = 0.75f;
const float Layer::BACK   = 0.99f;

// ---------------------------------------------------------------------------------

Sprite::Sprite(string filename)
{
    // carrega imagem
    image = new Image(filename);
    localImage = true;
    
    // configura sprite
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::Sprite(const Image * img)
{
    // aponta para imagem externa
    image = img;
    localImage = false;

    // configura sprite
    sprite.width = image->Width();
    sprite.height = image->Height();
    sprite.texture = image->View();
}

// ---------------------------------------------------------------------------------

Sprite::~Sprite()
{
    if (localImage)
        delete image;
}

// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color color)
{
    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;
    sprite.scale = scale;
    sprite.rotation = rotation * XM_PI / 180.0f;
    sprite.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}


// ---------------------------------------------------------------------------------

void Sprite::Draw(float x, float y, float z, float scale, float rotation, Color color, RECT* rect)
{
    // ajusta coordenadas usando a viewport
    x -= Engine::game->viewport.left;
    y -= Engine::game->viewport.top;

    sprite.x = x;
    sprite.y = y;
    sprite.depth = z;
    sprite.scale = scale;
    sprite.rotation = rotation * XM_PI / 180.0f;
    sprite.width = rect->right - rect->left;
    sprite.height = rect->bottom - rect->top;
    sprite.texCoord.x = float(rect->left) / image->Width();
    sprite.texCoord.y = float(rect->top) / image->Height();
    sprite.texSize.x = float(sprite.width) / image->Width();
    sprite.texSize.y = float(sprite.height) / image->Height();
    sprite.color = color;

    // adiciona o sprite na lista de desenho
    Engine::renderer->Draw(sprite);
}


// ---------------------------------------------------------------------------------