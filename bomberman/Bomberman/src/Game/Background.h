/**********************************************************************************
// Background (Arquivo de Cabeçalho)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Plano de fundo do jogo
//
**********************************************************************************/
#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include <list>
#include "../Engine/Types.h"                      // tipos específicos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Sprite.h"                     // background é composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:

    list<Sprite*> backgs;                         // lista contendo todos os planos de fundo
    Sprite * activeSprite;                        // plano de fundo atual
    list<Sprite*>::iterator it;                   // iterador dos planos de fundo

public:

    bool backGrid[13][17];
    bool stagePassed = false;

    Background();                                   // construtor
    ~Background();                                  // destrutor

    void Draw();                                    // desenho do objeto
    void Update();                                  // atualização do plano de fundo ativo
    void ChangeTo(uint value);                      // muda o plano de fundo para o endereço passado
    void CreateGrid();                              // cria matriz padrão de blocos do cenário
    void OccupyGridPosition(float x, float y);      // seta a posição do grid dado pelos pontos x e y como falso, indicando que está ocupado
    void OccupyGridPosition(int line, int column);  // seta o valor da linha e coluna do grid falso, indicando que está ocupado
    void ClearGridPosition(float x, float y);       // transforma a posição do grid dado pelos pontos x e y verdadeiros
    void ClearGridPosition(int line, int column);   // transforma o valor do grid pela linha e coluna em verdadeiro
    bool CheckGridPosition(float x, float y);       // verifica o valor da posição do grid dada pelos pontos x e y passados
    bool CheckGridPosition(int line, int column);   // verifica o valor do grid na linha e coluna passados
    
}; 

// --------------------------------------------------------------------------------

inline void Background::Update()
{
    // se o jogador passar de fase muda para o próximo plano de fundo
    if (stagePassed)
    {
        std::advance(it, 1);
        activeSprite = *it;
    }
}

// ----------------------------------------------------------------------------

inline void Background::OccupyGridPosition(float x, float y)
{
    int line = (y - 32) / 16;
    int column = x / 16;
    backGrid[line][column] = false;
}


inline void Background::OccupyGridPosition(int line, int column)
{
    backGrid[line][column] = false;
}

// ----------------------------------------------------------------------------

inline void Background::ClearGridPosition(float x, float y)
{
    int line = (y - 32) / 16;
    int column = x / 16;

    backGrid[line][column] = true;
}

// ----------------------------------------------------------------------------

inline void Background::ClearGridPosition(int line, int column)
{
    backGrid[line][column] = true;
}

// ----------------------------------------------------------------------------

inline bool Background::CheckGridPosition(float x, float y)
{
    int line = (y - 32) / 16;
    int column = x / 16;

    return backGrid[line][column];
}

inline bool Background::CheckGridPosition(int line, int column)
{
    return backGrid[line][column];
}

// ----------------------------------------------------------------------------

inline void Background::CreateGrid() {
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

// ---------------------------------------------------------------------------------

#endif _BACKGROUND_H_