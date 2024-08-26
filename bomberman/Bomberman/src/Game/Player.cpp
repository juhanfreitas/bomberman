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
#include "Bomberman.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    playerTiles = new TileSet("Resources/bomberman.png", 24, 32, 12, 72);
    anim = new Animation(playerTiles, 0.120f, true);
    //bombs = new list<Bomb>;
    
    Player::CreateBBox();

    uint SeqStill[1] = { 0 };
    uint SeqUp[4] = { 9, 10, 9, 11 };
    uint SeqDown[4] = { 0, 1, 0, 2 };
    uint SeqLeft[4] = { 6, 7, 6, 8 };
    uint SeqRight[4] = { 3, 4, 3, 5 };
    uint SeqBored[8] = { 48, 49, 50, 51, 52, 53, 54, 55 };
    uint SeqWinning[8] = { 36, 37, 38, 39, 40, 41, 42, 43 };
    uint SeqDying[11] = { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };

    anim->Add(STILL, SeqStill, 1);
    anim->Add(WALKUP, SeqUp, 4);
    anim->Add(WALKDOWN, SeqDown, 4);
    anim->Add(WALKLEFT, SeqLeft, 4);
    anim->Add(WALKRIGHT, SeqRight, 4);
    anim->Add(BORED, SeqBored, 7);
    anim->Add(DYING, SeqDying, 11);
    anim->Add(WINNING, SeqWinning, 8);

    state = STILL;
    speed = 100.0f;
    bored_timing = 10.0f;
    timer.Start();

    MoveTo(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale
    );
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
    Bomberman::scoreboard->UpdateScore(score);
    // anda para cima
    if (window->KeyDown(VK_UP))
    {
        timer.Reset();
        state = WALKUP;
        Translate(0, -speed * gameTime);
    }

    // anda para baixo
    if (window->KeyDown(VK_DOWN))
    {
        timer.Reset();
        state = WALKDOWN;
        Translate(0, speed * gameTime);
    }

    // anda para esquerda
    if (window->KeyDown(VK_LEFT))
    {
        timer.Reset();
        state = WALKLEFT;
        Translate(-speed * gameTime, 0);
    }

    // anda para direita
    if (window->KeyDown(VK_RIGHT))
    {
        timer.Reset();
        state = WALKRIGHT;
        Translate(speed * gameTime, 0);
    }

    if (window->KeyDown(VK_SPACE))
    {
        timer.Reset();
        state = DYING;
        anim->ChangeLoop(FALSE);
    }

    if (window->KeyDown('N'))
    {
        timer.Reset();
        state = WINNING;
        score += 10;
    }

    // se todas as teclas estão liberadas, mude para o estado parado
    if (window->KeyUp(VK_UP)
        && window->KeyUp(VK_DOWN)
        && window->KeyUp(VK_LEFT)
        && window->KeyUp(VK_RIGHT)
        && window->KeyUp(VK_SPACE)
        && window->KeyUp('N'))
    {
        state = STILL;
    }

    // se o bomberman estiver parado a tempo demais, mude para o estado entediado
    if (state == STILL && timer.Elapsed(bored_timing)) {
        state = BORED;
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