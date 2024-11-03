/**********************************************************************************
// Player (C�digo Fonte)
//
// Cria��o:     27 Jan 2013
// Atualiza��o: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Objeto animado
//
**********************************************************************************/

#include "Player.h"
#include "Bomberman.h"
#include "Intro.h"
#include "Stage1.h"
#include "Powerup.h"


// ---------------------------------------------------------------------------------

Player::Player(int plrNum) : playerNumber(plrNum)
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

    createBomb = createBombPrev = false;

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

    speed = 70.0f;
    bored_timing = 5.0f;
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
    float prevX = Stage1::gameview.left;
    Stage1::gameview.left = 0;
    Stage1::gameview.right = 272;
    Bomberman::xdiff = prevX;
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
        //lives -= 1;
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

    Bomberman::xdiff = 0;
    
    float offset = (Stage1::gameview.right - Stage1::gameview.left) / 2;
    
    
    // ==================== controle da fonte do input ==================== //
    if (stateBuffer.front() != DYING) {
        conOn = Bomberman::ctrlActive;

        if (conOn)
        {
            bool isActive = Bomberman::PlayerActive(playerNumber);
            if (isActive)
            {
                Bomberman::gamepad->XboxUpdateState(playerNumber);
                createBomb = Bomberman::gamepad->XboxButton(ButtonB);
                dtnBmb = Bomberman::gamepad->XboxButton(ButtonA);

                moveUp = (Bomberman::gamepad->XboxButton(DpadUp));
                moveRt = (Bomberman::gamepad->XboxButton(DpadRight));
                moveDn = (Bomberman::gamepad->XboxButton(DpadDown));
                moveLt = (Bomberman::gamepad->XboxButton(DpadLeft));

                notmoveUp = !moveUp;
                notmoveRt = !moveRt;
                notmoveDn = !moveDn;
                notmoveLt = !moveLt;
            }
            crtBmb = (createBomb && createBomb != createBombPrev);
        }
        else 
        {
            moveUp = window->KeyPress(VK_UP);
            notmoveUp = window->KeyUp(VK_UP);

            moveDn = window->KeyPress(VK_DOWN);
            notmoveDn = window->KeyUp(VK_DOWN);
            
            moveLt = window->KeyPress(VK_LEFT);
            notmoveLt = window->KeyUp(VK_LEFT);

            moveRt = window->KeyPress(VK_RIGHT);
            notmoveRt = window->KeyUp(VK_RIGHT);
        }
    }



    // ====================== controle da bomba ====================== //
    if (stateBuffer.front() != DYING) {
        // cria nova bomba
        if ((window->KeyPress(VK_SPACE) && !conOn) || (conOn && crtBmb))
        {
            timer.Reset();
            CreateBomb(bombType);
        }

        // denota a bomba
        if ((window->KeyPress('D') && !conOn) || (conOn && dtnBmb))
            DetonateBombs();
    }
    

    if (invincible && transparencyTimer.Elapsed(10.f))
    {
        invincible = false;
        transparencyTimer.Reset();
        transparencyTimer.Stop();
    }


    // ======================= controle da movimentação ======================= //
    {
        // anda para cima
        if (moveUp)
        {
            if (stateBuffer.size() < 3)
                stateBuffer.push_front(WALKUP);
            else
            {
                stateBuffer.pop_back();
                stateBuffer.push_front(WALKUP);
            }
        }
        if (notmoveUp)
        {
            stateBuffer.remove(WALKUP);
        }
        // ************************************************************


        // anda para baixo
        if (moveDn)
        {
            if (stateBuffer.size() < 3)
                stateBuffer.push_front(WALKDOWN);
            else
            {
                stateBuffer.pop_back();
                stateBuffer.push_front(WALKDOWN);
            }
        }
        if (notmoveDn)
        {
            stateBuffer.remove(WALKDOWN);
        }
        // ************************************************************


        // anda para esquerda
        if (moveLt)
        {
            if (stateBuffer.size() < 3)
                stateBuffer.push_front(WALKLEFT);
            else
            {
                stateBuffer.pop_back();
                stateBuffer.push_front(WALKLEFT);
            }
        }
        if (notmoveLt)
        {
            stateBuffer.remove(WALKLEFT);
        }
        // ************************************************************


        // anda para direita
        if (moveRt)
        {
            if (stateBuffer.size() < 3)
                stateBuffer.push_front(WALKRIGHT);
            else
            {
                stateBuffer.pop_back();
                stateBuffer.push_front(WALKRIGHT);
            }
        }
        if (notmoveRt)
        {
            stateBuffer.remove(WALKRIGHT);
        }
        // ************************************************************


        // player parado
        if (stateBuffer.empty())
        {
            stateBuffer.clear();
            stateBuffer.push_front(STILL);
        }
        else {
            if (stateBuffer.size() > 1)
                stateBuffer.remove(BORED);
        }

    }



    // ========================== tratamento do input ========================== //
    {
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
            if (x >= offset || Stage1::gameview.left == 0)
                Translate(-speed * gameTime, 0);
            else
            {
                Stage1::speed = speed;
                Stage1::viewDirMove = LEFT;
                Stage1::MoveView();
            }
            break;
        case WALKRIGHT:
            timer.Reset();
            if (x <= offset || Stage1::gameview.right == Stage1::backg->Width())
                Translate(speed * gameTime, 0);
            else
            {
                Stage1::speed = speed;
                Stage1::viewDirMove = RIGHT;
                Stage1::MoveView();
            }
            break;
        case WINNING:
            timer.Reset();
            score += 10;
            break;
        case DYING:
            if (anim->Inactive() && alive)
                SoftReset();
            break;
        }
    }

    createBombPrev = createBomb;

    // atualiza anima��o
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

    // colisão pela esquerda
    if (diffLt <= 0 && diffLt >= -5)
    {
        // offset em cima
        if ((diffUp >= -7 && diffUp <= 0))
        {
            if (stateBuffer.front() == WALKRIGHT)
                MoveTo(x, y + diffUp);
        }// offset em baixo
        else if ((diffDn >= -7 && diffDn <= 0))
        {
            if (stateBuffer.front() == WALKRIGHT)
                MoveTo(x, y - diffDn);
        }
        else MoveTo(objBox->Left() - (width / 2.0f), y);
    }

    // colisão por cima
    if (diffUp <= 0 && diffUp >= -5)
    {   // offset pela esquerda
        if (diffLt >= -7 && diffLt <= 1)
        {
            if (stateBuffer.front() == WALKDOWN)
                MoveTo(x + diffLt, y);
        }// offset pela direita
        else if (diffRt >= -7 && diffRt <= 1)
        {
            if (stateBuffer.front() == WALKDOWN)
                MoveTo(x - diffRt, y);
        }
        else MoveTo(x, objBox->Top() - (height / 2.0f) - 7);
    }

    // colisão pela direita
    if (diffRt <= 0 && diffRt >= -5)
    {   // offset em cima
        if (diffUp >= -7 && diffUp <= 0)
        {
            if (stateBuffer.front() == WALKLEFT)
                MoveTo(x, y + diffUp);
        }// offset em baixo
        else if (diffDn >= -7 && diffDn <= 0)
        {
            if (stateBuffer.front() == WALKLEFT)
                MoveTo(x, y - diffDn);
        }
        else MoveTo(objBox->Right() + (width / 2.0f), y);
    }

    // colisão por baixo
    if (diffDn <= 0 && diffDn >= -5)
    {   // offset pela esquerda
        if (diffLt >= -7 && diffLt <= 0)
        {
            if (stateBuffer.front() == WALKUP)
                MoveTo(x + diffLt, y);
        }// offset pela direita
        else if (diffRt >= -7 && diffRt <= 0)
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