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
    type = PLAYER;
    playerTiles = new TileSet("Resources/bomberman.png", 24, 32, 12, 72);
    anim = new Animation(playerTiles, 0.120f, true);
    bombs = new list<Bomb>;
    
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

    MoveTo(32, 48);
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
    /*Bomberman::scoreboard->UpdateBombs(2);
    Bomberman::scoreboard->UpdatePower(2);
    Bomberman::scoreboard->UpdateLives(3);*/

    // anda para cima
    if (window->KeyDown(VK_UP))
    {
        timer.Reset();
        lastState = state;
        state = WALKUP;
        Translate(0, -speed * gameTime);
    }

    // anda para baixo
    if (window->KeyDown(VK_DOWN))
    {
        timer.Reset();
        lastState = state;
        state = WALKDOWN;
        Translate(0, speed * gameTime);
    }

    // anda para esquerda
    if (window->KeyDown(VK_LEFT))
    {
        timer.Reset();
        lastState = state;
        state = WALKLEFT;
        Translate(-speed * gameTime, 0);
    }

    // anda para direita
    if (window->KeyDown(VK_RIGHT))
    {
        timer.Reset();
        lastState = state;
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
    if (x > window->Width()/2.0f - 40)
        MoveTo(window->Width()/2.0f - 40, y);

    if (x < 40)
        MoveTo(40, y);

    if (y > window->Height()/2.0f - 31)
        MoveTo(x, window->Height()/2.0f - 31);

    if (y < 48)
        MoveTo(x, 48);
}

void Player::CreateBBox()
{
    float l, r, t, b;

    l = -1.0f * playerTiles->TileWidth()/2.0f + 4;
    r =  1.0f * playerTiles->TileWidth()/2.0f - 4;
    t = -1.0f * playerTiles->TileHeight()/2.0f + 18;
    b =  1.0f * playerTiles->TileHeight()/2.0f - 1;

    BBox(new Rect(l, t, r, b));
}

void Player::OnCollision(Object* obj)
{
    if (obj->Type() == BLOCK)
    {
        Rect* objBox = (Rect*)obj->BBox();
        Rect* plrBox = (Rect*)BBox();

        int diffUp = plrBox->Bottom() - objBox->Top();
        int diffDn = plrBox->Top() - objBox->Bottom();
        int diffLt = plrBox->Right() - (int)objBox->Left();
        int diffRt = plrBox->Left() - (int)objBox->Right();

        // colisão pela esquerda
        if (diffLt == 0)
        {
            float width = plrBox->Right() - plrBox->Left();
            if (state == WALKRIGHT)
            {
                if ((diffUp <= 1 && diffUp >= 0) ||
                    (diffDn <= 1 && diffDn >= 0))
                {
                    MoveTo(x, y);
                }
                else
                    MoveTo(objBox->Left() - (width / 2.0f), y);
            }
            if (state == WALKUP || state == WALKDOWN)
            {
                MoveTo(x, y);
            }

        }

        // colisão pela direita
        if (diffRt == 0)
        {
            float width = plrBox->Right() - plrBox->Left();
            if (state == WALKLEFT)
            {
                if ((diffUp <= 1 && diffUp >= 0) ||
                    (diffDn <= 1 && diffDn >= 0))
                {
                    MoveTo(x, y);
                }
                else
                    MoveTo(objBox->Right() + (width / 2.0f), y);
            }
            if (state == WALKUP || state == WALKDOWN)
            {
                MoveTo(x, y);
            }

        }

        // colisão por cima
        if (diffUp == 0)
        {
            float height = plrBox->Bottom() - plrBox->Top();
            if (state == WALKDOWN)
            {
                if ((diffRt <= 1 && diffRt >= 0) ||
                    (diffLt <= 1 && diffLt >= 0))
                {
                    MoveTo(x, y);
                }
                else
                    MoveTo(x, objBox->Top() - (height / 2.0f) - 9);
            }
            if (state == WALKLEFT || state == WALKRIGHT)
            {
                MoveTo(x, objBox->Top() - (height / 2.0f) - 9);
            }
        }

        // colisão por baixo
        if (diffDn == 0)
        {
            float height = plrBox->Bottom() - plrBox->Top();
            if (state == WALKUP)
            {
                if ((diffRt <= 1 && diffRt >= 0) ||
                    (diffLt <= 1 && diffLt >= 0))
                {
                    MoveTo(x, y);
                }
                else
                    MoveTo(x, objBox->Bottom() + (height / 2.0f) - 9);
            }
            if (state == WALKLEFT || state == WALKRIGHT)
            {
                MoveTo(x, objBox->Bottom() + (height / 2.0f) - 9);
            }
        }
    }
    
    if (obj->Type() == BOMB)
    {
        
    }

    if (obj->Type() == BUILDING)
    {
        Rect* objBox = (Rect*)obj->BBox();
        Rect* plrBox = (Rect*)BBox();

        int diffUp = plrBox->Bottom() - objBox->Top();
        int diffDn = plrBox->Top() - objBox->Bottom();
        int diffLt = plrBox->Right() - (int)objBox->Left();
        int diffRt = plrBox->Left() - (int)objBox->Right();

        // colisão pela esquerda
        if (diffLt == 0)
        {
            float width = plrBox->Right() - plrBox->Left();
            if (state == WALKRIGHT)
            {
                if ((diffUp <= 1 && diffUp >= 0) ||
                    (diffDn <= 1 && diffDn >= 0))
                {
                    MoveTo(x, y);
                }
                else 
                    MoveTo(objBox->Left() - (width / 2.0f), y);
            }
            if (state == WALKUP || state == WALKDOWN)
            {
                MoveTo(x, y);
            }

        }

        // colisão pela direita
        if (diffRt == 0)
        {
            float width = plrBox->Right() - plrBox->Left();
            if (state == WALKLEFT)
            {
                if ((diffUp <= 1 && diffUp >= 0) ||
                    (diffDn <= 1 && diffDn >= 0))
                {
                    MoveTo(x, y);
                } 
                else
                    MoveTo(objBox->Right() + (width / 2.0f), y);
            }
            if (state == WALKUP || state == WALKDOWN)
            {
                MoveTo(x, y);
            }

        }

        // colisão por cima
        if (diffUp == 0)
        {
            float height = plrBox->Bottom() - plrBox->Top();
            if (state == WALKDOWN)
            {
                if ((diffRt <= 1 && diffRt >= 0) ||
                    (diffLt <= 1 && diffLt >= 0))
                {
                    MoveTo(x, y);
                }
                else
                    MoveTo(x, objBox->Top() - (height / 2.0f) - 9);
            }
            if (state == WALKLEFT || state == WALKRIGHT)
            {
                MoveTo(x, objBox->Top() - (height / 2.0f) - 9);
            }
        }

        // colisão por baixo
        if (diffDn == 0)
        {
            float height = plrBox->Bottom() - plrBox->Top();
            if (state == WALKUP)
            {
                if ((diffRt <= 1 && diffRt >= 0) ||
                    (diffLt <= 1 && diffLt >= 0))
                {
                    MoveTo(x, y);
                }
                else
                    MoveTo(x, objBox->Bottom() + (height / 2.0f) - 9);
            }
            if (state == WALKLEFT || state == WALKRIGHT)
            {
                MoveTo(x, objBox->Bottom() + (height / 2.0f) - 9);
            }
        }
    }
    if (obj->Type() == POWERUPS)
    { 
    
    }
}

// ---------------------------------------------------------------------------------