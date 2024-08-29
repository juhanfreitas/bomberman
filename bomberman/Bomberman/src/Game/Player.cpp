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

    BBox(CreateBBox());
    MoveTo(40, 48);

    //MoveTo(40, 48);
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

    /*if (state == DYING && timer.Elapsed(1.5f)){
        MoveTo(40, 48);
        state = STILL;
        anim->ChangeLoop(TRUE);

    }*/

    HandleBombs();
    HandleExplosions();

    // anda para cima
    if (window->KeyPress(VK_UP))
    {
        if (listState.size() < 3)
            listState.push_front(WALKUP);
        else
        {
            listState.pop_back();
            listState.push_front(WALKUP);
        }
    }
    if (window->KeyUp(VK_UP))
    {
        listState.remove(WALKUP);
    }


    // anda para baixo
    if (window->KeyPress(VK_DOWN))
    {
        if (listState.size() < 3)
            listState.push_front(WALKDOWN);
        else
        {
            listState.pop_back();
            listState.push_front(WALKDOWN);
        }
    }
    if (window->KeyUp(VK_DOWN))
    {
        listState.remove(WALKDOWN);
    }


    // anda para esquerda
    if (window->KeyPress(VK_LEFT))
    {
        if (listState.size() < 3)
            listState.push_front(WALKLEFT);
        else
        {
            listState.pop_back();
            listState.push_front(WALKLEFT);
        }
    }
    if (window->KeyUp(VK_LEFT))
    {
        listState.remove(WALKLEFT);
    }


    // anda para direita
    if (window->KeyPress(VK_RIGHT))
    {
        if (listState.size() < 3)
            listState.push_front(WALKRIGHT);
        else
        {
            listState.pop_back();
            listState.push_front(WALKRIGHT);
        }
    }
    if (window->KeyUp(VK_RIGHT))
    {
        listState.remove(WALKRIGHT);
    }


    if (window->KeyPress(VK_SPACE))
    {
        /*timer.Reset();
        state = DYING;
        anim->ChangeLoop(FALSE);*/
        timer.Reset();
        CreateBomb(NORMAL);
    }

    if (window->KeyPress('N'))
    {
        if (listState.size() < 3)
            listState.push_front(WINNING);
        else
        {
            listState.pop_back();
            listState.push_front(WINNING);
        }
    }

    if (listState.empty())
    {
        listState.push_front(STILL);
    }

    switch (listState.front())
    {
    case STILL:
        if (timer.Elapsed(bored_timing))
        {
            listState.clear();
            listState.push_front(BORED);
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
        if (timer.Elapsed(1.5f))
        {
            MoveTo(40, 48);
            state = STILL;
            anim->ChangeLoop(TRUE);
        }
        break;
    }

    // atualiza animação
    anim->Select(listState.front());
    anim->NextFrame();

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
        if (y > window->Height() / 2.0f - 32)
            MoveTo(x, window->Height() / 2.0f - 32);
    }




    //// anda para cima
    //if (window->KeyDown(VK_UP) && state != DYING)
    //{
    //    timer.Reset();
    //    lastState = state;
    //    state = WALKUP;
    //    Translate(0, -speed * gameTime);
    //}

    //// anda para baixo
    //if (window->KeyDown(VK_DOWN) && state != DYING)
    //{
    //    timer.Reset();
    //    lastState = state;
    //    state = WALKDOWN;
    //    Translate(0, speed * gameTime);
    //}

    //// anda para esquerda
    //if (window->KeyDown(VK_LEFT) && state != DYING)
    //{
    //    timer.Reset();
    //    lastState = state;
    //    state = WALKLEFT;
    //    Translate(-speed * gameTime, 0);
    //}

    //// anda para direita
    //if (window->KeyDown(VK_RIGHT) && state != DYING)
    //{
    //    timer.Reset();
    //    lastState = state;
    //    state = WALKRIGHT;
    //    Translate(speed * gameTime, 0);
    //}

    //if (window->KeyPress(VK_SPACE) && state != DYING)
    //{
    //    timer.Reset();
    //    CreateBomb(NORMAL);
    //}

    //if (window->KeyDown('N'))
    //{
    //    timer.Reset();
    //    state = WINNING;
    //    score += 10;
    //}

    //// se todas as teclas estão liberadas, mude para o estado parado
    //if (window->KeyUp(VK_UP)
    //    && window->KeyUp(VK_DOWN)
    //    && window->KeyUp(VK_LEFT)
    //    && window->KeyUp(VK_RIGHT)
    //    && window->KeyUp(VK_SPACE)
    //    && window->KeyUp('N')
    //    && state != DYING)
    //{
    //    state = STILL;
    //}

    //// se o bomberman estiver parado a tempo demais, mude para o estado entediado
    //if (state == STILL && timer.Elapsed(bored_timing)) {
    //    state = BORED;
    //}

    //// atualiza animação
    //anim->Select(state);
    //anim->NextFrame();

    //// mantém personagem dentro da tela
    //if (x > window->Width()/2.0f - 40)
    //    MoveTo(window->Width()/2.0f - 40, y);

    //if (x < 40)
    //    MoveTo(40, y);

    //if (y > window->Height()/2.0f - 31)
    //    MoveTo(x, window->Height()/2.0f - 31);

    //if (y < 48)
    //    MoveTo(x, 48);
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
    l = -1.0f * playerTiles->TileWidth() / 2.0f + 4;
    r = 1.0f * playerTiles->TileWidth() / 2.0f - 4;
    t = -1.0f * playerTiles->TileHeight() / 2.0f + 15;
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
                if (listState.front() == WALKRIGHT)
                {
                    MoveTo(x, y + diffUp);
                }
            }
            else if ((diffDn >= -4 && diffDn <= 0))
            {
                if (listState.front() == WALKRIGHT)
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
                if (listState.front() == WALKDOWN)
                {
                    MoveTo(x + diffLt, y);
                }
            }
            else if (diffRt >= -4 && diffRt <= 0)
            {
                if (listState.front() == WALKDOWN)
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
                if (listState.front() == WALKLEFT)
                {
                    MoveTo(x, y + diffUp);
                }
            }
            else if (diffDn >= -4 && diffDn <= 0)
            {
                if (listState.front() == WALKLEFT)
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
                if (listState.front() == WALKUP)
                {
                    MoveTo(x + diffLt, y);
                }
            }
            else if (diffRt >= -4 && diffRt <= 0)
            {
                if (listState.front() == WALKUP)
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
        if (state == WALKLEFT || lastState == WALKLEFT)
            Translate(speed * gameTime, 0);
        
        if (state == WALKRIGHT || lastState == WALKRIGHT)
            Translate(-speed * gameTime, 0);
        
        if (state == WALKUP || lastState == WALKUP)
            Translate(0, speed * gameTime);

        if (state == WALKDOWN || lastState == WALKDOWN)
            Translate(0, -speed * gameTime);

        break;
    // --------------------------------------------------------------------------------------------
    case EXPLOSION:
        if (state != DYING) {
            state = DYING;
            anim->ChangeLoop(FALSE);
            timer.Reset();
            if (lives == 0) {
                state = WINNING;
            }
            lives -= 1;
        }
        
        break;
    case POWERUPS:

        break;
    // --------------------------------------------------------------------------------------------
    }
}

// --------------------------------------------------------------------------------------------