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
    Background::CreateMatrix();
    backgs = * new list<Sprite*>;
    backgs.push_back(new Sprite("Resources/Stage 1.png"));
    list<Sprite*>::iterator it = backgs.begin();
    activeSprite = * it;

    //BBox(new Rect(-1.0f * activeSprite->Width()/2.0f, -1.0f * 8, activeSprite->Width()/2.0f, 8));
    MoveTo(window->CenterX()/2.0f, window->CenterY() + 32, Layer::BACK);
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    backgs.clear();
}


// -------------------------------------------------------------------------------


void Background::Draw()
{
    // desenha plano de fundo ativo
    activeSprite->Draw(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale + 16,
        Layer::BACK
    );
}

void Background::ChangeTo(uint value) 
{
    // muda a fase de acordo com o valor passado
    it = backgs.begin();
    std::advance(it, value);
    activeSprite = *it;
}


void Background::CreateMatrix() {
    // primeira linha
    for (auto i = 0; i < 17; i++) {
        backGrid[0][i] = false;
    }


    // segunda linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[1][i] = true;

        if (i == 0 || i == 1 || 
            i == 7 || i == 15 || i ==16) 
        { 
            backGrid[1][i] = false;
        }
    }


    // terceira linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[2][i] = true;

        if (i == 0 || i == 1 || i == 3 || 
            i == 5 || i == 7 || i == 9 || 
            i == 11|| i == 13|| i == 15|| i == 16) 
        { 
            backGrid[2][i] = false;
        }
    }


    // quarta linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[3][i] = true;

        if (i == 0 || i == 1 || 
            i == 15|| i == 16) 
        {
            backGrid[3][i] = false;
        }
    }


    // quinta linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[4][i] = true;

        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 ||
            i == 11|| i == 13|| i == 15|| i == 16)
        {
            backGrid[4][i] = false;
        }
    }


    // sexta linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[5][i] = true;

        if (i == 0 || i == 1 || i == 13 ||
            i == 15|| i == 16)
        {
            backGrid[5][i] = false;
        }
    }


    // sétima linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[6][i] = true;

        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 || 
            i == 10|| i == 11|| i == 13|| 
            i == 15|| i == 16)
        {
            backGrid[6][i] = false;
        }
    }


    // oitava linha
    for (auto i = 0; i < 17; i++) {
        backGrid[7][i] = true;

        if (i == 0 || i == 1 || i == 9 ||
            i == 15|| i == 16)
        {
            backGrid[7][i] = false;
        }
    }


    // nona linha
    for (auto i = 0; i < 17; i++) {
        backGrid[8][i] = true;

        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 ||
            i == 11|| i == 13|| i == 15|| i == 16)
        {
            backGrid[8][i] = false;
        }
    }


    // décima linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[9][i] = true;

        if (i == 0 || i == 1 || i == 14 ||
            i == 15|| i == 16)
        {
            backGrid[9][i] = false;
        }
    }

// -------------------------------------------------------------------------------

    // décima primeira linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[10][i] = true;

        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 ||
            i == 11 || i == 13 || i == 15 || i == 16)
        {
            backGrid[10][i] = false;
        }
    }


    // décima segunda linha
    for (auto i = 0; i < 17; i++) 
    {
        backGrid[11][i] = true;

        if (i == 0 || i == 1 || i == 5 ||
            i == 7 || i == 9 || i == 15|| i == 16)
        {
            backGrid[11][i] = false;
        }
    }


    // décima terceira linha
    for (auto i = 0; i < 17; i++) {
        backGrid[12][i] = false;
    }
}

// -------------------------------------------------------------------------------
