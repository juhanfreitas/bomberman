/**********************************************************************************
// Player (Código Fonte)
//
// Criação:     27 Jan 2013
// Atualização: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto animado
//
**********************************************************************************/

#include "Player.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    playerTiles = new TileSet("Resources/bomberman.png", 24, 32, 12, 72);
    anim = new Animation(playerTiles, 0.120f, true, 2.0f);

    Player::CreateBBox();

    uint SeqStill[1] = { 0 };
    uint SeqUp[4] = { 9, 10, 9, 11 };
    uint SeqDown[4] = { 0, 1, 0, 2 };
    uint SeqLeft[4] = { 6, 7, 6, 8};
    uint SeqRight[4] = { 3, 4, 3, 5 };
    uint SeqBored[7] = { 66, 60, 61, 62, 63, 64, 65 };
    uint SeqWinning[8] = { 48, 49, 50, 51, 52, 53, 54, 55 };
    uint SeqDying[11] = { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };

    anim->Add(WALKUP, SeqUp, 8);
    anim->Add(WALKDOWN, SeqDown, 8);
    anim->Add(WALKLEFT, SeqLeft, 8);
    anim->Add(WALKRIGHT, SeqRight, 8);
    anim->Add(STILL, SeqStill, 1);

    state = STILL;
    speed = 150.0f;
    MoveTo(window->CenterX(), window->CenterY());
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete playerTiles;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    anim->ChangeLoop(TRUE);


    // anda para cima
    if (window->KeyDown(VK_UP))
    {
        Translate(0, -speed * gameTime);
        state = WALKUP;
    }

    // anda para baixo
    if (window->KeyDown(VK_DOWN))
    {
        state = WALKDOWN;
        Translate(0, speed * gameTime);
    }

    // anda para esquerda
    if (window->KeyDown(VK_LEFT))
    {
        state = WALKLEFT;
        Translate(-speed * gameTime, 0);
    }

    // anda para direita
    if (window->KeyDown(VK_RIGHT))
    {
        state = WALKRIGHT;
        Translate(speed * gameTime, 0);
    }

    if (window->KeyPress(VK_SPACE))
    {
        timer.Reset();
        state = DYING;
        anim->ChangeLoop(FALSE);
        //bomb->Draw();
    }
    if (window->KeyPress('B'))
    {
        //bomb->Draw();
    }

    if (window->KeyDown('N'))
    {
        timer.Reset();
        state = WINNING;
    }

    // se todas as teclas estão liberadas, mude para o estado parado
    if (window->KeyUp(VK_UP) && window->KeyUp(VK_DOWN) && window->KeyUp(VK_LEFT) && window->KeyUp(VK_RIGHT))
    {
        state = STILL;
    }

    // atualiza animação
    anim->Select(state);
    anim->NextFrame();

    // mantém personagem dentro da tela
    if (x + playerTiles->TileWidth() / 2.0f > window->Width())
        MoveTo(window->Width() - playerTiles->TileWidth() / 2.0f, y);

    if (x - playerTiles->TileWidth() / 2.0f < 0)
        MoveTo(playerTiles->TileWidth() / 2.0f, y);

    if (y + playerTiles->TileHeight() / 2.0f > window->Height())
        MoveTo(x, window->Height() - playerTiles->TileHeight() / 2.0f);

    if (y - playerTiles->TileHeight() / 2.0f < 0)
        MoveTo(x, playerTiles->TileHeight() / 2.0f);
}

void Player::CreateBBox()
{
    float l, r, t, b;

    l = -1.0f * playerTiles->TileWidth() + 8;
    r =  1.0f * playerTiles->TileWidth() - 8;
    t =  1.0f * playerTiles->TileHeight() - 32;
    b =  1.0f * playerTiles->TileHeight() - 2;

    BBox(new Rect(l, t, r, b));
}


// ---------------------------------------------------------------------------------