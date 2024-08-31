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

    playerTiles = new TileSet("Resources/bomberman.png", 24, 32, 12, 72);
    anim = new Animation(playerTiles, 0.120f, true);
    bombStack = * new list<Bomb*>;
    
    type = PLAYER;

    bombPower = 3;
    lives = 2;
    maxBombs = 4;
    availableBombs = maxBombs;

    uint SeqStill[1] = { 0 };
    uint SeqUp[4] = { 9, 10, 9, 11 };
    uint SeqDown[4] = { 0, 1, 0, 2 };
    uint SeqLeft[4] = { 6, 7, 6, 8 };
    uint SeqRight[4] = { 3, 4, 3, 5 };
    uint SeqBored[8] = { 48, 49, 50, 51, 52, 53, 54, 55 };
    uint SeqWinning[8] = { 36, 37, 38, 39, 40, 41, 42, 43 };
    uint SeqDying[11] = { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };

    anim->Add(WALKUP,       SeqUp,      4);
    anim->Add(WALKDOWN,     SeqDown,    4);
    anim->Add(WALKLEFT,     SeqLeft,    4);
    anim->Add(WALKRIGHT,    SeqRight,   4);
    anim->Add(BORED,        SeqBored,   7);
    anim->Add(DYING,        SeqDying,   11);
    anim->Add(WINNING,      SeqWinning, 8);
    anim->Add(STILL,        SeqStill,   1);

    speed = 50.0f;
    bored_timing = 5.0f;
    timer.Start();

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

void Player::Reset()
{
    MoveTo(40, 48);
    stateBuffer.clear();
    bombStack.clear();
    stateBuffer.push_front(STILL);
    anim->ChangeLoop(true);
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    Bomberman::scoreboard->UpdateScore(score);
    Bomberman::scoreboard->UpdateBombs(maxBombs);
    Bomberman::scoreboard->UpdatePower(bombPower);
    Bomberman::scoreboard->UpdateLives(lives);

    HandleBombs();

    // anda para cima
    if (window->KeyPress(VK_UP))
    {
        if (stateBuffer.size() < 3)
            stateBuffer.push_front(WALKUP);
        else
        {
            stateBuffer.pop_back();
            stateBuffer.push_front(WALKUP);
        }
    }
    if (window->KeyUp(VK_UP))
    {
        stateBuffer.remove(WALKUP);
    }


    // anda para baixo
    if (window->KeyPress(VK_DOWN))
    {
        if (stateBuffer.size() < 3)
            stateBuffer.push_front(WALKDOWN);
        else
        {
            stateBuffer.pop_back();
            stateBuffer.push_front(WALKDOWN);
        }
    }
    if (window->KeyUp(VK_DOWN))
    {
        stateBuffer.remove(WALKDOWN);
    }


    // anda para esquerda
    if (window->KeyPress(VK_LEFT))
    {
        if (stateBuffer.size() < 3)
            stateBuffer.push_front(WALKLEFT);
        else
        {
            stateBuffer.pop_back();
            stateBuffer.push_front(WALKLEFT);
        }
    }
    if (window->KeyUp(VK_LEFT))
    {
        stateBuffer.remove(WALKLEFT);
    }


    // anda para direita
    if (window->KeyPress(VK_RIGHT))
    {
        if (stateBuffer.size() < 3)
            stateBuffer.push_front(WALKRIGHT);
        else
        {
            stateBuffer.pop_back();
            stateBuffer.push_front(WALKRIGHT);
        }
    }
    if (window->KeyUp(VK_RIGHT))
    {
        stateBuffer.remove(WALKRIGHT);
    }


    if (window->KeyPress(VK_SPACE))
    {
        timer.Reset();
        CreateBomb(NORMAL);
    }

    if (stateBuffer.empty())
    {
        stateBuffer.push_front(STILL);
    }
    else {
        if (stateBuffer.size() > 1)
        {
            stateBuffer.remove(BORED);
        }
    }

    switch (stateBuffer.front())
    {
    case STILL:
        if (timer.Elapsed(bored_timing))
        {
            stateBuffer.clear();
            stateBuffer.push_front(BORED);
        }
        break;
    case BORED:
        
        break;
    case WALKUP:
        timer.Reset();
        Translate(0, -speed * gameTime);
        break;
    case WALKDOWN:
        timer.Reset();
        Translate(0, speed * gameTime);
        break;
    case WALKLEFT:
        timer.Reset();
        Translate(-speed * gameTime, 0);
        break;
    case WALKRIGHT:
        timer.Reset();
        Translate(speed * gameTime, 0);
        break;
    case WINNING:
        timer.Reset();
        score += 10;
        break;
    case DYING:
        if (anim->Inactive())
        {
            Reset();
        }
        break;
    }

    // mantém personagem dentro da tela
    {
        // saída pela esquerda
        if (x < 40)
            MoveTo(40, y);

        // saída pela direita
        if (x > window->Width() / 2.0f - 40)
            MoveTo(window->Width() / 2.0f - 40, y);

        if (y < 49)
            MoveTo(x, 49);

        // saída por baixo
        if (y > window->Height() / 2.0f - 31)
            MoveTo(x, window->Height() / 2.0f - 31);
    }

    // atualiza animação
    anim->Select(stateBuffer.front());
    anim->NextFrame();
}

// ---------------------------------------------------------------------------------

Geometry* Player::CreateBBox()
{
    float l, r, t, b;
    l = -1.0f * playerTiles->TileWidth() / 2.0f + 4;
    r = 1.0f * playerTiles->TileWidth() / 2.0f - 4;
    t = -1.0f * playerTiles->TileHeight() / 2.0f + 15;
    b = 1.0f * playerTiles->TileHeight() / 2.0f - 1;
    return new Rect(l, t, r, b);
}

// ---------------------------------------------------------------------------------

void Player::CreateBomb(BombType bombType)
{
    if (availableBombs > 0) {
        availableBombs -= 1;
        Bomb* bomb = new Bomb(bombType, x, y);
        Stage1::scene->Add(bomb, STATIC);
        bombStack.push_back(bomb);
    }
}

// ---------------------------------------------------------------------------------

void Player::HandleBombs()
{
    if (!bombStack.empty()) {
        Bomb * recentBomb = bombStack.front();
        
        if (recentBomb->state == READY) {
            availableBombs += 1;
            recentBomb->Explode(bombPower);
            bombStack.pop_front();
        }
    }
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    Rect* objBox = (Rect*)obj->BBox();
    Rect* plrBox = (Rect*)BBox();
    float diffUp = objBox->Top() - plrBox->Bottom();
    float diffDn = plrBox->Top() - objBox->Bottom();
    float diffLt = objBox->Left() - plrBox->Right();
    float diffRt = plrBox->Left() - objBox->Right();
    
    float width = plrBox->Right() - plrBox->Left();
    float height = plrBox->Bottom() - plrBox->Top();
 
    switch (obj->Type())
    {
    case BLOCK:

    // --------------------------------------------------------------------------------------------
    case BUILDING:

        // colisão pela esquerda
        if (diffLt <= 0 && diffLt >= -1)
        {
            if ((diffUp >= -4 && diffUp <= 0))
            {
                if (stateBuffer.front() == WALKRIGHT)
                {
                    MoveTo(x, y + diffUp);
                }
            }
            else if ((diffDn >= -4 && diffDn <= 0))
            {
                if (stateBuffer.front() == WALKRIGHT)
                {
                    MoveTo(x, y - diffDn);
                }
            }
            else 
            { 
                MoveTo(objBox->Left() - (width / 2.0f), y);
            }
        }

        // colisão por cima
        if (diffUp <= 0 && diffUp >= -1)
        {
            if (diffLt >= -4 && diffLt <= 0)
            {
                if (stateBuffer.front() == WALKDOWN)
                {
                    MoveTo(x + diffLt, y);
                }
            }
            else if (diffRt >= -4 && diffRt <= 0)
            {
                if (stateBuffer.front() == WALKDOWN)
                {
                    MoveTo(x - diffRt, y);
                }
            }
            else
                MoveTo(x, objBox->Top() - (height / 2.0f) - 7);
        }

        // colisão pela direita
        if (diffRt <= 0 && diffRt >= -1)
        {
            if (diffUp >= -4 && diffUp <= 0)
            {
                if (stateBuffer.front() == WALKLEFT)
                {
                    MoveTo(x, y + diffUp);
                }
            }
            else if (diffDn >= -4 && diffDn <= 0)
            {
                if (stateBuffer.front() == WALKLEFT)
                {
                    MoveTo(x, y - diffDn);
                }
            }
            else
                MoveTo(objBox->Right() + (width / 2.0f), y);
        }        

        // colisão por baixo
        if (diffDn <= 0 && diffDn >= -1)
        {
            if (diffLt >= -4 && diffLt <= 0)
            {
                if (stateBuffer.front() == WALKUP)
                {
                    MoveTo(x + diffLt, y);
                }
            }
            else if (diffRt >= -4 && diffRt <= 0)
            {
                if (stateBuffer.front() == WALKUP)
                {
                    MoveTo(x - diffRt, y);
                }
            }
            else
                MoveTo(x, objBox->Bottom() + (height / 2.0f) - 7);
        }
        break;
    // --------------------------------------------------------------------------------------------
    case BOMB:
        if (stateBuffer.front() == WALKLEFT)
            Translate(speed * gameTime, 0);
        
        if (stateBuffer.front() == WALKRIGHT)
            Translate(-speed * gameTime, 0);
        
        if (stateBuffer.front() == WALKUP)
            Translate(0, speed * gameTime);

        if (stateBuffer.front() == WALKDOWN)
            Translate(0, -speed * gameTime);

        break;
    // --------------------------------------------------------------------------------------------
    case EXPLOSION:
        if (stateBuffer.front() != DYING) {
            stateBuffer.clear();
            stateBuffer.push_front(DYING);
            anim->ChangeLoop(FALSE);
        }        
        break;

    case POWERUPS:

        break;
    // --------------------------------------------------------------------------------------------
    }
}

// --------------------------------------------------------------------------------------------