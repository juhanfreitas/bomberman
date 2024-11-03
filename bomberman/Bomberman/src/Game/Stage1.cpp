#include "../Engine/Engine.h"
#include "Resources.h"
#include "Player.h"
#include "Bomberman.h"
#include "Home.h"
#include "Stage1.h"
#include "Powerup.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()


Scene*          Stage1::scene = nullptr;
Background*     Stage1::backg = nullptr;
Directions      Stage1::viewDirMove = UP;
ViewPort        Stage1::gameview = { 0, 0, 272, 208 };
MapGrid*        Stage1::bGrid = nullptr;
float           Stage1::delta = 0;
float           Stage1::speed = 0;
bool            Stage1::canMove = false;

// -----------------------------------------------------------------------------

void Stage1::Init()
{
    scene = new Scene();
    
    buildingImage = new Image("Resources/stage/building1.png");
    shadowImage = new Image("Resources/stage/building1_shadow.png");

    backg = new Background();
    bGrid = new MapGrid(&gameview.left);
    scoreboard = new Scoreboard();
    CreateWalls();
    CreatePortal();
    CreateBlocks();
    
    scene->Add(Bomberman::player1, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    //Bomberman::audio->Play(MUS_STAGE1);
    Size(backg->Width(), backg->Height());
    
    Bomberman::levelTime.Start();
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{
    Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, Bomberman::levelTime.Elapsed());

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

    // toca um sinal de aviso quando o tempo est� acabando
    if (Bomberman::levelTime.Elapsed(Bomberman::timeLimit))
    {
        timeUp = true;
        Bomberman::levelTime.Stop();
        Bomberman::audio->Play(SE_TIMER);
    }

    // encerra o jogo ao encerrar o tempo
    if (Bomberman::levelTime.Elapsed(2) && timeUp)
        window->Close();

    // atualiza a cena do jogo;
    scene->Update();

    // detecta as colis�es na cena
    scene->CollisionDetection();
}

// ------------------------------------------------------------------------------

void Stage1::Draw()
{
    
    if (viewScene)
    {
        backg->Draw(&gameview);
        scene->Draw();
    }
    if (viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Stage1::Finalize()
{
    scene->Remove(backg, STATIC);
    scene->Remove(portal, STATIC);
    scene->Remove(Bomberman::player1, MOVING);
    scene->Remove(Bomberman::scoreboard, STATIC);
    delete scene;
}

// -------------------------------------------------------------------------------

void Stage1::MoveView() 
{
    delta = speed * gameTime;
    float diff;

    switch (viewDirMove)
    {
    case UP:
        gameview.top -= delta;
        gameview.bottom -= delta;
        if (gameview.top < 0)
        {
            diff = gameview.bottom - gameview.top;
            gameview.top = 0;
            gameview.bottom = diff;
        }
        break;
    case DOWN:
        gameview.top += delta;
        gameview.bottom += delta;
        if (gameview.top > backg->Height())
        {
            diff = gameview.bottom - gameview.top;
            gameview.top = 0;
            gameview.bottom = backg->Height();
        }
        break;
    case LEFT:
        Bomberman::xdiff = delta;
        gameview.right -= delta;
        gameview.left -= delta;
        if (gameview.left <= 0)
        {
            diff = gameview.right - gameview.left;
            gameview.left = 0;
            gameview.right = diff;
        }
        break;
    case RIGHT:
        Bomberman::xdiff = delta * -1;
        gameview.right += delta;
        gameview.left += delta;
        if (gameview.right >= backg->Width())
        {
            diff = gameview.right - gameview.left;
            gameview.left = backg->Width() - diff;
            gameview.right = backg->Width();
        }
        break;
    }
}

void Stage1::CreateWalls()
{
    for (auto i = 0; i < 13; i++)
    {
        for (auto j = 0; j < 47; j++)
        {
            Image* bImg = nullptr;
            Image* sImg = nullptr;

            if (i != 0 && i != 12 && j != 0 && j != 46) {
                bImg = buildingImage;
                sImg = shadowImage;
            }

            if (bGrid->CheckGridPosition(i, j, WLL))
            {
                float posX = j * 16.0f + 16;
                float posY = (i * 16.0f) + 32;
                Building* build = new Building(posX, posY, bImg, sImg);
                scene->Add(build, STATIC);
            }
        }
    }
    bGrid->OccupyGridPosition(1,1, WLL);
    bGrid->OccupyGridPosition(1,2, WLL);
    bGrid->OccupyGridPosition(2,1, WLL);

    CreateExtraWalls();
}

void Stage1::CreateExtraWalls()
{
    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 35; i++)
    {
        int numL = 4 + rand() % 8;
        int numC = 4 + rand() % 42;

        if (bGrid->CheckGridPosition(numL, numC, MPT))
        {
            
            if (numL % 2 != 0)
            {
                if (!(bGrid->CheckGridPosition(numL, numC - 2, MPT)) ||
                    !(bGrid->CheckGridPosition(numL, numC + 2, MPT)))
                {
                    i--;
                    continue;
                }
            }

            if (!(bGrid->CheckGridPosition(numL - 2, numC, MPT)) ||
                !(bGrid->CheckGridPosition(numL + 2, numC, MPT)))
            {
                i--;
                continue;
            }
            
            float posX = numC * 16 + 16;
            float posY = (numL * 16) + 32;
            Building* build = new Building(posX, posY, buildingImage, shadowImage);
            scene->Add(build, STATIC);
            bGrid->OccupyGridPosition(numL, numC, WLL);
        }
        else i--;
    }
}

void Stage1::CreateBlocks()
{
    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 100; i++)
    {
        int numLine = 1 + rand() % 11;
        int numColm = 1 + rand() % 46;

        if (bGrid->CheckGridPosition(numLine, numColm, MPT))
        {
            float posX = numColm * 16 + 16;
            float posY = (numLine * 16) + 32;
            
            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            if (i < 5)
                CreatePowerUp(posX, posY);
            
            bGrid->OccupyGridPosition(numLine, numColm, FillType::BLK);
        }
        else i--;
    }
    bGrid->ClearGridPosition(1, 1);
    bGrid->ClearGridPosition(1, 2);
    bGrid->ClearGridPosition(2, 1);
}

void Stage1::CreatePortal()
{
    srand(static_cast<uint>(time(0)));
    int numLine;
    int numColm;

    for (auto i = 0; i < 1; i++)
    {
        numLine = 1 + rand() % 11;
        numColm = 1 + rand() % 46;

        if (bGrid->CheckGridPosition(numLine, numColm, MPT))
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            portal = new Portal(posX, posY);
            scene->Add(portal, STATIC);

            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            bGrid->OccupyGridPosition(posX, posY, FillType::BLK);
        }
        else i--;
    }
}

void Stage1::CreatePowerUp(float posX, float posY)
{
    PowerUpType type = BOMBS;
    uint val = rand() % 3;
    if (val == 0)
        type = BOMBS;
    if (val == 1)
        type = FIRE;
    if (val == 2)
        type = SPD_UP;
    Powerup* powerup = new Powerup(posX, posY, type);
    scene->Add(powerup, STATIC);
}