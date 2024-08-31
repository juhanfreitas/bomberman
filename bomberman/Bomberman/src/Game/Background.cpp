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
    backgs.push_back(new Sprite("Resources/stage/Stage 1.png"));
    list<Sprite*>::iterator it = backgs.begin();
    activeSprite = * it;

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
    for (auto lin = 0; lin < 13; lin++)
    {
        for (auto col = 0; col < 17; col++)
        {
            // primeira e última linha
            if (lin == 0 || lin == 12)
            {
                backGrid[lin][col] = false;
            }

            // linhas restantes
            if (lin > 0 && lin < 12)
            {
                // linhas impares
                if ((lin % 2 != 0))
                {
                    backGrid[lin][col] = true;

                    if (col == 0 || col == 1 ||
                        col == 15 || col == 16)
                    {
                        backGrid[lin][col] = false;
                    }
                }
                // linhas pares
                else
                {
                    backGrid[lin][col] = true;

                    if (col == 0 || col == 1 ||
                        col == 3 || col == 5 ||
                        col == 7 || col == 9 ||
                        col == 11 || col == 13 ||
                        col == 15 || col == 16)
                    {
                        backGrid[lin][col] = false;
                    }
                }
            }
        }
    }
}

// -------------------------------------------------------------------------------
