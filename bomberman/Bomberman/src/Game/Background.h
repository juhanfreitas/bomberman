/**********************************************************************************
// Background (Arquivo de Cabe�alho)
// 
// Cria��o:     21 Abr 2012
// Atualiza��o: 02 Set 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Plano de fundo do jogo
//
**********************************************************************************/
#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include <list>
#include "../Engine/Types.h"                      // tipos espec�ficos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Sprite.h"                     // background � composto por sprites
#include "Enums.h"

// ---------------------------------------------------------------------------------

class Background : public Object
{
private:

    // lista contendo todos os planos de fundo
    list<Sprite*> backgs;                         
    // plano de fundo atual
    Sprite * activeSprite;                        
    // iterador dos planos de fundo
    list<Sprite*>::iterator it;                   

public:

    FillType backGrid[13][17];
    bool stagePassed = false;

    Background();                                   // construtor
    ~Background();                                  // destrutor

    // desenha o plano de fundo ativo   na cena
    void Draw();                                    
    // atualiza��o do plano de fundo ativo
    void Update();
    // muda o plano de fundo para o endere�o passado
    void ChangeTo(uint value);                      
    // cria grid padr�o de blocos do cen�rio
    void CreateGrid();         
    //bool CheckGridPosition(float x, float y);
    // ocupa a posi��o do grid dado pelos pontos x e y com o tipo passado
    void OccupyGridPosition(float x, float y, FillType type);      
    // ocupa a linha e coluna do grid com o tipo passado
    void OccupyGridPosition(int line, int column, FillType type);  
    // assume a posi��o do grid dado pelos pontos x e y como vazio
    void ClearGridPosition(float x, float y);       
    // torna o valor da linha e coluna do grid como vazio
    void ClearGridPosition(int line, int column);   
    // verifica o valor da posi��o do grid dada pelos pontos x e y passados
    FillType CheckGridPosition(float x, float y);       
    // compara o valor da posi��o do grid dada pelos pontos x e y passados com o tipo passado
    bool CheckGridPosition(float x, float y, FillType type);       
    // verifica o valor do grid na linha e coluna passados
    FillType CheckGridPosition(int line, int column);   
    // verifica o valor do grid na linha e coluna desejada com o tipo passado
    bool CheckGridPosition(int line, int column, FillType  type);   
    
}; 

// --------------------------------------------------------------------------------

inline void Background::Update()
{
    // se o jogador passar de fase muda para o pr�ximo plano de fundo
    if (stagePassed)
    {
        std::advance(it, 1);
        activeSprite = *it;
        stagePassed = false;
    }
}

//inline bool Background::CheckGridPosition(float x, float y)
//{
//    int line = (y - 32) / 16;
//    int column = x / 16;
//    
//    return backGrid[line][column];
//}

// ----------------------------------------------------------------------------
inline void Background::OccupyGridPosition(float x, float y, FillType type)
{
    int line = (y - 32) / 16;
    int column = x / 16;
    backGrid[line][column] = type;
}
// ----------------------------------------------------------------------------
inline void Background::OccupyGridPosition(int line, int column, FillType type)
{
    backGrid[line][column] = type;
}
// ----------------------------------------------------------------------------
inline void Background::ClearGridPosition(float x, float y)
{
    int line = (y - 32) / 16;
    int column = x / 16;

    //backGrid[line][column] = true;
    backGrid[line][column] = MPT;
}
// ----------------------------------------------------------------------------
inline void Background::ClearGridPosition(int line, int column)
{
    //backGrid[line][column] = true;
    backGrid[line][column] = MPT;
}
// ----------------------------------------------------------------------------
inline FillType Background::CheckGridPosition(float x, float y)
{
    int line = (y - 32) / 16;
    int column = x / 16;

    return backGrid[line][column];
}
// ----------------------------------------------------------------------------
inline bool Background::CheckGridPosition(float x, float y, FillType type)
{
    int line = (y - 32) / 16;
    int column = x / 16;

    return backGrid[line][column] == type;
}
// ----------------------------------------------------------------------------
inline FillType Background::CheckGridPosition(int line, int column)
{
    return backGrid[line][column];
}
// ----------------------------------------------------------------------------
inline bool Background::CheckGridPosition(int line, int column, FillType type)
{
    return backGrid[line][column] == type;
}
// ----------------------------------------------------------------------------
inline void Background::CreateGrid() {
    for (auto lin = 0; lin < 13; lin++)
    {
        for (auto col = 0; col < 17; col++)
        {
            // primeira e �ltima linha
            if (lin == 0 || lin == 12)
                backGrid[lin][col] = WLL;

            // linhas restantes
            if (lin > 0 && lin < 12)
            {
                // linhas impares
                if ((lin % 2 != 0))
                {
                    backGrid[lin][col] = MPT;

                    if (col == 0 || col == 1 ||
                        col == 15 || col == 16)
                    {
                        backGrid[lin][col] = WLL;
                    }
                }
                // linhas pares
                else
                {
                    backGrid[lin][col] = MPT;

                    if (col == 0 || col == 1 ||
                        col == 3 || col == 5 ||
                        col == 7 || col == 9 ||
                        col == 11 || col == 13 ||
                        col == 15 || col == 16)
                    {
                        backGrid[lin][col] = WLL;
                    }
                }
            }
        }
    }
}
// ---------------------------------------------------------------------------------
#endif _BACKGROUND_H_