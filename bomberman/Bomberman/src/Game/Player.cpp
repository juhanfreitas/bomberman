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
#include "Powerup.h"


// ---------------------------------------------------------------------------------

Player::Player()
{
    type = PLAYER;
    playerTiles = new TileSet("Resources/Sprites/general/bomberman.png", 24, 32, 12, 72);
    anim = new Animation(playerTiles, 0.120f, true);
    bombStack = * new list<Bomb*>;
       

    // atributos do player
    bombType = NORMAL;
    bombKick = false;
    bombPass = false;
    bombPower = 1;
    blockPass = false;
    lives = 2;
    maxBombs = 1;
    availableBombs = maxBombs;
    // ---------------------------

    uint SeqStill[1] = { 0 };
    uint SeqUp[4] = { 9, 10, 9, 11 };
    uint SeqDown[4] = { 0, 1, 0, 2 };
    uint SeqLeft[4] = { 6, 7, 6, 8 };
    uint SeqRight[4] = { 3, 4, 3, 5 };
    uint SeqBored[8] = { 48, 49, 50, 51, 52, 53, 54, 55 };
    uint SeqLosing[3] = { 45, 46, 47 };
    uint SeqWinning[8] = { 36, 37, 38, 39, 40, 41, 42, 43 };
    uint SeqDying[11] = { 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34 };

    anim->Add(WALKUP,       SeqUp,      4);
    anim->Add(WALKDOWN,     SeqDown,    4);
    anim->Add(WALKLEFT,     SeqLeft,    4);
    anim->Add(WALKRIGHT,    SeqRight,   4);
    anim->Add(BORED,        SeqBored,   7);
    anim->Add(DYING,        SeqDying,   11);
    anim->Add(LOSING,       SeqLosing,  3);
    anim->Add(WINNING,      SeqWinning, 8);
    anim->Add(STILL,        SeqStill,   1);

    speed = 50.0f;

    timer.Start();
    transparencyTimer.Start();

    BBox(CreateBBox());
    MoveTo(startX, startY);

}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete playerTiles;
}

// ---------------------------------------------------------------------------------
// Reset for Game Over or Level Clear
void Player::Reset()
{
    SoftReset();
    bombStack.clear();
    availableBombs = maxBombs;

    // verifica se o player está vivo para o reset de game over
    if (!alive) {
        alive = true;
        lives = 2;
        ClearPowerUps();
    }
}

// Reset for deaths
void Player::SoftReset()
{
    MoveTo(startX, startY);
    stateBuffer.clear();
    stateBuffer.push_front(STILL);
    timer.Reset();
    transparencyTimer.Reset();
    anim->ChangeLoop(true);
}

// ---------------------------------------------------------------------------------

void Player::Die()
{
    if (stateBuffer.front() != DYING && transparencyTimer.Elapsed(transparencyDuration)) {
        stateBuffer.clear();
        stateBuffer.push_front(DYING);
        Bomberman::audioManager->Play(SE_PLAYERDEATH);
        Bomberman::audioManager->Volume(SE_PLAYERDEATH, Bomberman::SEVolume);
        anim->ChangeLoop(false);
    }
}

void Player::State(uint type)
{
    if (stateBuffer.front() == type)
        return;

    stateBuffer.clear();

    switch (type)
    {
    case DYING:
        stateBuffer.push_front(DYING);
        Bomberman::audioManager->Play(SE_PLAYERDEATH);
        Bomberman::audioManager->Volume(SE_PLAYERDEATH, Bomberman::SEVolume);
        anim->ChangeLoop(false);
        break;
    case LOSING:
        stateBuffer.push_front(LOSING);
        lives -= 1;
        break;
    case WINNING:
        stateBuffer.push_front(WINNING);
        break;
    default:
        break;
    }    
}
// ---------------------------------------------------------------------------------

void Player::Update()
{
    // Verifica se o player morreu
    if (lives < 0) {
        lives = 0;
        alive = false;
    }

    Bomberman::scoreboard->UpdateScore(score);
    Bomberman::scoreboard->UpdateBombs(maxBombs);
    Bomberman::scoreboard->UpdatePower(bombPower);
    Bomberman::scoreboard->UpdateLives(lives);

    // cria nova bomba
    if (window->KeyPress(VK_SPACE))
    {
        timer.Reset();
        CreateBomb(bombType);
    }
    // denota a bomba
    if (window->KeyPress('D'))
        DetonateBombs();


    if (stateBuffer.front() != DYING && stateBuffer.front() != LOSING && stateBuffer.front() != WINNING) {
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
    }
    // --------------------------------------------------------------

    // trata o input
    switch (stateBuffer.front())
    {
    case STILL:
        if (timer.Elapsed(bored_timing))
        {
            stateBuffer.clear();
            stateBuffer.push_front(BORED);
        }
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

    case DYING:
        if (anim->Inactive() && alive) {
            SoftReset();
            lives -= 1;
        }
        break;
    }
    // --------------------------------------------------------------

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
        Bomberman::audioManager->Play(SE_BOMBPLACE);
        Bomberman::audioManager->Volume(SE_BOMBPLACE, Bomberman::SEVolume);
        Bomb* bomb = new Bomb(this, bombType, x, y, bombPower);
        Stage1::scene->Add(bomb, MOVING);
        if (bombType == TIMED)
            bombStack.push_back(bomb);
    }
}

// ---------------------------------------------------------------------------------

void Player::DetonateBombs()
{
    if (!bombStack.empty()) {
        Bomb * recentBomb = bombStack.front();
        if (recentBomb->bombMode == TIMED)
        {
            bombStack.pop_front();
            recentBomb->Explode();
        }
    }
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
    if (stateBuffer.front() == DYING || 
        stateBuffer.front() == LOSING ||
        stateBuffer.front() == WINNING)
    { return; }

    switch (obj->Type())
    {
    case BLOCK:
        if (blockPass)
            break;
        DefaultCollision(obj);
        break;
    
    // --------------------------------------------------------------------------------------------
    case BOMB:
        if (bombKick)
        {
            Bomb* bomb;
            bomb = dynamic_cast<Bomb*>(obj);
            bomb->bombKicked = true;
            bomb->dirKicked = CollisionDirection(obj);
            break;
        }
        if (bombPass)
            break;
        DefaultCollision(obj);
        break;
    
    // --------------------------------------------------------------------------------------------
    case BUILDING:    
        DefaultCollision(obj);
        break; 
    // --------------------------------------------------------------------------------------------
    case EXPLOSION:
        Die();
        break;
    case PORTAL:
        Portal* portal;
        portal = dynamic_cast<Portal*>(obj);
        portal->HandleCollision(this);
        break;
    // --------------------------------------------------------------------------------------------
    case POWERUPS:
        Powerup* pwr = dynamic_cast<Powerup*>(obj);
        if (pwr->visible)
        {
            Rect* objBox = (Rect*)obj->BBox();
            Rect* plrBox = (Rect*)BBox();
        
            int diffX = abs(plrBox->Left() - objBox->Left());
            int diffY = abs(plrBox->Top() - objBox->Top());

            if ((diffX == 0 && diffY <= 8) || (diffY == 0 && diffX <= 8))
                pwr->PowerUpActions(this);
        }
        break;
    }
}


void Player::DefaultCollision(Object* obj)
{
    Rect* objBox = (Rect*)obj->BBox();
    Rect* plrBox = (Rect*)BBox();
    float diffUp = objBox->Top() - plrBox->Bottom();
    float diffDn = plrBox->Top() - objBox->Bottom();
    float diffLt = objBox->Left() - plrBox->Right();
    float diffRt = plrBox->Left() - objBox->Right();

    float width = plrBox->Right() - plrBox->Left();
    float height = plrBox->Bottom() - plrBox->Top();

    // colis�o pela esquerda
    if (diffLt <= 0 && diffLt >= -1)
    {
        // offset em cima
        if ((diffUp >= -4 && diffUp <= 0))
        {
            if (stateBuffer.front() == WALKRIGHT)
                MoveTo(x, y + diffUp);
        }// offset em baixo
        else if ((diffDn >= -4 && diffDn <= 0))
        {
            if (stateBuffer.front() == WALKRIGHT)
                MoveTo(x, y - diffDn);
        }
        else MoveTo(objBox->Left() - (width / 2.0f), y);
    }

    // colis�o por cima
    if (diffUp <= 0 && diffUp >= -1)
    {   // offset pela esquerda
        if (diffLt >= -4 && diffLt <= 0)
        {
            if (stateBuffer.front() == WALKDOWN)
                MoveTo(x + diffLt, y);
        }// offset pela direita
        else if (diffRt >= -4 && diffRt <= 0)
        {
            if (stateBuffer.front() == WALKDOWN)
                MoveTo(x - diffRt, y);
        }
        else MoveTo(x, objBox->Top() - (height / 2.0f) - 7);
    }

    // colis�o pela direita
    if (diffRt <= 0 && diffRt >= -1)
    {   // offset em cima
        if (diffUp >= -4 && diffUp <= 0)
        {
            if (stateBuffer.front() == WALKLEFT)
                MoveTo(x, y + diffUp);
        }// offset em baixo
        else if (diffDn >= -4 && diffDn <= 0)
        {
            if (stateBuffer.front() == WALKLEFT)
                MoveTo(x, y - diffDn);
        }
        else MoveTo(objBox->Right() + (width / 2.0f), y);
    }

    // colis�o por baixo
    if (diffDn <= 0 && diffDn >= -1)
    {   // offset pela esquerda
        if (diffLt >= -4 && diffLt <= 0)
        {
            if (stateBuffer.front() == WALKUP)
                MoveTo(x + diffLt, y);
        }// offset pela direita
        else if (diffRt >= -4 && diffRt <= 0)
        {
            if (stateBuffer.front() == WALKUP)
                MoveTo(x - diffRt, y);
        }
        else MoveTo(x, objBox->Bottom() + (height / 2.0f) - 7);
    }
}

Directions Player::CollisionDirection(Object* obj)
{
    Rect* objBox = (Rect*)obj->BBox();
    Rect* plrBox = (Rect*)BBox();
    float diffUp = objBox->Top() - plrBox->Bottom();
    float diffDn = plrBox->Top() - objBox->Bottom();
    float diffLt = objBox->Left() - plrBox->Right();
    float diffRt = plrBox->Left() - objBox->Right();

    if (diffUp < 0 && diffUp >= -4)
        return DOWN;
    if (diffDn < 0 && diffDn >= -4)
        return UP;
    if (diffLt < 0 && diffLt >= -4)
        return RIGHT;
    if (diffRt < 0 && diffRt >= -4)
        return LEFT;
}

// --------------------------------------------------------------------------------------------