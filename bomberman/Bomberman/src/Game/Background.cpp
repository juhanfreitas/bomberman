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
#include <list>

// ---------------------------------------------------------------------------------

Background::Background()
{
    
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
    backgs = * new list<Sprite*>;
    backgs.push_back(new Sprite("Resources/Stage 1.png"));
    list<Sprite*>::iterator it = backgs.begin();
    activeSprite = * it;
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    //delete &backgs;
}

// -------------------------------------------------------------------------------

void Background::Update()
{
    // se o jogador passar de fase muda para o próximo plano de fundo
    if (stagePassed)
    {
        std::advance(it, 1);
        activeSprite = *it;
    }
}

// -------------------------------------------------------------------------------

void Background::Draw()
{
    // desenha plano de fundo ativo
    activeSprite->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 2.0f, 0.0f);
}

void Background::ChangeTo(uint value) 
{
    // muda a fase de acordo com o valor passado
    it = backgs.begin();
    std::advance(it, value);
    activeSprite = *it;
}

// -------------------------------------------------------------------------------
