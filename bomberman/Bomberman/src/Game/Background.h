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

    bool stagePassed = false;

    Background();                                   // construtor
    ~Background();                                  // destrutor

    // desenha o plano de fundo ativo na cena
    void Draw();

    // desenha a região do plano de fundo dado pela viewport
    void Draw(ViewPort* view);

    // largura do background ativo
    float Width();

    // altura do background ativo
    float Height();

    // atualização do plano de fundo ativo
    void Update();

    // muda o plano de fundo para o endereço passado
    void ChangeTo(uint value);                      
    
    
}; 

// --------------------------------------------------------------------------------

inline void Background::Draw()                      // desenha plano de fundo ativo
{
    activeSprite->Draw(window->CenterX()/2.0f, window->CenterY()/2.0f + 16, Layer::BACK);
}

inline float Background::Width() { return activeSprite->Width(); }
inline float Background::Height() { return activeSprite->Height(); }


inline void Background::Draw(ViewPort* vp)          // desenha a região do plano de fundo dada pela viewport
{
    RECT rect;
    rect.left = vp->left;
    rect.right = vp->right;
    rect.top = vp->top;
    rect.bottom = vp->bottom;

    activeSprite->Draw(window->CenterX() / 2.0f, window->CenterY() / 2.0f + 16, Layer::BACK, 1.0f, 0.0f, {1,1,1,1}, &rect);
}

inline void Background::Update()
{
    // se o jogador passar de fase muda para o próximo plano de fundo
    if (stagePassed)
    {
        std::advance(it, 1);
        activeSprite = *it;
        stagePassed = false;
    }
}

// ---------------------------------------------------------------------------------
#endif _BACKGROUND_H_