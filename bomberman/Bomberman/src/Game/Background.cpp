/**********************************************************************************
// Background (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/

#include "Background.h"
#include "Bomberman.h"
#include <list>

// ---------------------------------------------------------------------------------

Background::Background()
{
    Background::CreateGrid();
    MoveTo(window->CenterX() / Bomberman::screenScale, window->CenterY() / Bomberman::screenScale + 16, Layer::BACK);
    backgs = * new list<Sprite*>;
    backgs.push_back(new Sprite("Resources/stage/Stage 1.png"));
    list<Sprite*>::iterator it = backgs.begin();
    activeSprite = * it;
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    backgs.clear();
}



void Background::Draw()
{
    activeSprite->Draw(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale + 16,
        Layer::BACK, 1.0f, 0.0f
    );
}

// -------------------------------------------------------------------------------

void Background::ChangeTo(uint value) 
{
    // muda a fase de acordo com o valor passado
    it = backgs.begin();
    std::advance(it, value);
    activeSprite = *it;
}

// -------------------------------------------------------------------------------