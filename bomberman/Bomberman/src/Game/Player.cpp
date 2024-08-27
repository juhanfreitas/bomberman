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
#include "Intro.h"
#include "Stage1.h"
#include "Bomb.h"
#include "Explosion.h"


// ---------------------------------------------------------------------------------

Player::Player()
{
    type = PLAYER;
    playerTiles = new TileSet("Resources/bomberman.png", 24, 32, 12, 72);
    anim = new Animation(playerTiles, 0.120f, true);
    bombStack = * new stack<Bomb*>;
    explosionStack = * new stack<Explosion*>;
    
    type = PLAYER;

    bombPower = 1;
    lives = 2;
    maxBombs = 1;
    availableBombs = maxBombs;

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
    speed = 50.0f;
    bored_timing = 10.0f;
    timer.Start();

    MoveTo(32, 48);
    BBox(CreateBBox());

    MoveTo(40, 48);
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
    Bomberman::scoreboard->UpdateBombs(maxBombs);
    Bomberman::scoreboard->UpdatePower(bombPower);
    Bomberman::scoreboard->UpdateLives(lives);

    if (state == DYING && timer.Elapsed(1.5f)){
        MoveTo(40, 48);
        state = STILL;
        anim->ChangeLoop(TRUE);

    }

    HandleBombs();
    HandleExplosions();

    // anda para cima
    if (window->KeyDown(VK_UP) && state != DYING)
    {
        timer.Reset();
        lastState = state;
        state = WALKUP;
        Translate(0, -speed * gameTime);
    }

    // anda para baixo
    if (window->KeyDown(VK_DOWN) && state != DYING)
    {
        timer.Reset();
        lastState = state;
        state = WALKDOWN;
        Translate(0, speed * gameTime);
    }

    // anda para esquerda
    if (window->KeyDown(VK_LEFT) && state != DYING)
    {
        timer.Reset();
        lastState = state;
        state = WALKLEFT;
        Translate(-speed * gameTime, 0);
    }

    // anda para direita
    if (window->KeyDown(VK_RIGHT) && state != DYING)
    {
        timer.Reset();
        lastState = state;
        state = WALKRIGHT;
        Translate(speed * gameTime, 0);
    }

    if (window->KeyPress(VK_SPACE) && state != DYING)
    {
        timer.Reset();
        CreateBomb(NORMAL);
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
        && window->KeyUp('N')
        && state != DYING)
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



void Player::CreateBomb(BombType bombType)
{
    if (availableBombs > 0) {
        availableBombs -= 1;
        Bomb * bomb = new Bomb(bombType, x, y);
        Stage1::scene->Add(bomb, STATIC);
        bombStack.push(bomb);
    }
}



Geometry* Player::CreateBBox()
{
    float l, r, t, b;
    l = -1.0f * playerTiles->TileWidth() / 2.0f + 5;
    r = 1.0f * playerTiles->TileWidth() / 2.0f - 5;
    t = -1.0f * playerTiles->TileHeight() / 2.0f + 20;
    b = 1.0f * playerTiles->TileHeight() / 2.0f - 1;
    return new Rect(l, t, r, b);
}



void Player::HandleBombs()
{
    if (!bombStack.empty()) {
        Bomb * recentBomb = bombStack.top();
        
        if (recentBomb->timer.Elapsed(3.0f)) {
            availableBombs += 1;
            Stage1::scene->Delete(recentBomb, STATIC);
            Explosion* explosion = new Explosion(recentBomb->X(), recentBomb->Y());
            Stage1::scene->Add(explosion, STATIC);
            explosionStack.push(explosion);
            bombStack.pop();
        }
    }
}



void Player::HandleExplosions()
{
    if (!explosionStack.empty()) {
        Explosion* recentExplosion = explosionStack.top();

        if (recentExplosion->timer.Elapsed(1.5f)) {
            Stage1::scene->Delete(recentExplosion, STATIC);
            explosionStack.pop();
        }
    }
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
    
    if (obj->Type() == BOMB) {
        if (state == WALKLEFT || lastState == WALKLEFT)
            Translate(speed * gameTime, 0);
        if (state == WALKRIGHT || lastState == WALKRIGHT)
            Translate(-speed * gameTime, 0);
        if (state == WALKUP || lastState == WALKUP)
            Translate(0, speed * gameTime);
        if (state == WALKDOWN || lastState == WALKDOWN)
            Translate(0, -speed * gameTime);
    }
    if (obj->Type() == EXPLOSION) {

        if (state != DYING) {
            state = DYING;
            anim->ChangeLoop(FALSE);
            timer.Reset();
            lives -= 1;
            if (lives < 0) {
                state = WINNING;
            }
        }
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