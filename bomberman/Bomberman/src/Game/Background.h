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

#ifndef _BOMBERMAN_BACKGROUND_H_
#define _BOMBERMAN_BACKGROUND_H_

// ---------------------------------------------------------------------------------

#include <list>
#include "../Engine/Types.h"                      // tipos espec�ficos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Sprite.h"                     // background � composto por sprites

// ---------------------------------------------------------------------------------

class Background : public Object
{
private: 

    list<Sprite*> backgs;                 // lista contendo todos os planos de fundo
    Sprite * activeSprite;                // plano de fundo atual
    list<Sprite*>::iterator it;           // iterador dos planos de fundo


public:

    bool stagePassed = false;

    Background();                       // construtor
    ~Background();                      // destrutor

    void Update();                      // atualiza��o do plano de fundo ativo
    void ChangeTo(uint value);          // muda o plano de fundo para o endere�o passado
    void Draw();                        // desenho do objeto
}; 

// ---------------------------------------------------------------------------------

#endif