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

// ---------------------------------------------------------------------------------

Background::Background()
{
    Background::CreateMatrix();
    MoveTo(window->CenterX(), window->CenterY(), Layer::BACK);
    backgs = * new list<Sprite*>;
    backgs.push_back(new Sprite("Resources/Stage 1.png"));
    list<Sprite*>::iterator it = backgs.begin();
    activeSprite = * it;
}

// ---------------------------------------------------------------------------------

Background::~Background()
{
    backgs.clear();
}


// -------------------------------------------------------------------------------



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
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || 
            i == 7 || i == 15 || i ==16) 
        { 
            backGrid[1][i] = false;
            break;
        }
        backGrid[1][i] = true;
    }


    // terceira linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 3 || 
            i == 5 || i == 7 || i == 9 || 
            i == 11|| i == 13|| i == 15|| i ==16) 
        { 
            backGrid[2][i] = false;
            break;
        }
        backGrid[2][i] = true;
    }


    // quarta linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || 
            i == 15 || i == 16) 
        {
            backGrid[3][i] = false;
            break;
        }
        backGrid[3][i] = true;
    }


    // quinta linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 ||
            i == 11|| i == 13|| i == 15|| i == 16)
        {
            backGrid[4][i] = false;
            break;
        }
        backGrid[4][i] = true;
    }


    // sexta linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 13 ||
            i == 15|| i == 16)
        {
            backGrid[5][i] = false;
            break;
        }
        backGrid[5][i] = true;
    }


    // sétima linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 || 
            i == 10|| i == 11|| i == 13|| 
            i == 15|| i == 16)
        {
            backGrid[6][i] = false;
            break;
        }
        backGrid[6][i] = true;
    }


    // oitava linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 9 ||
            i == 15|| i == 16)
        {
            backGrid[7][i] = false;
            break;
        }
        backGrid[7][i] = true;
    }


    // nona linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 ||
            i == 11|| i == 13|| i == 15|| i == 16)
        {
            backGrid[8][i] = false;
            break;
        }
        backGrid[8][i] = true;
    }


    // décima linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 14 ||
            i == 15|| i == 16)
        {
            backGrid[9][i] = false;
            break;
        }
        backGrid[9][i] = true;
    }


    // décima primeira linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 3 ||
            i == 5 || i == 7 || i == 9 ||
            i == 11 || i == 13 || i == 15 || i == 16)
        {
            backGrid[10][i] = false;
            break;
        }
        backGrid[10][i] = true;
    }


    // décima segunda linha
    for (auto i = 0; i < 17; i++) {
        if (i == 0 || i == 1 || i == 5 ||
            i == 7 || i == 9 || i == 15|| i == 16)
        {
            backGrid[11][i] = false;
            break;
        }
        backGrid[11][i] = true;
    }


    // décima terceira linha
    for (auto i = 0; i < 17; i++) {
        backGrid[12][i] = false;
    }
}

// -------------------------------------------------------------------------------