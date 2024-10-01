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


Scene* Stage1::scene = nullptr;
Background* Stage1::backg = nullptr;

// -----------------------------------------------------------------------------

void Stage1::Init()
{
    scene = new Scene();
    
    buildingImage = new Image("Resources/stage/building1.png");
    shadowImage = new Image("Resources/stage/building1_shadow.png");

    backg = new Background();
    scoreboard = new Scoreboard();
    
    CreateWalls();
    CreatePortal();
    CreateBlocks();

    scene->Add(backg, STATIC);
    scene->Add(Bomberman::player, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    Bomberman::player->SoftReset();

    Bomberman::audio->Play(MUS_STAGE1, true);
    Bomberman::audio->Volume(MUS_STAGE1, Bomberman::MUSVolume);
    
    timer.Start();
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{
    // atualiza o timer do scoreboard se o tempo não tiver esgotado
    if (!timeUp)
        Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, timer.Elapsed());

    // acelera a musica quando faltar 30 segundos
    if (timer.Elapsed(Bomberman::timeLimit - 30.0f))
        Bomberman::audio->Frequency(MUS_STAGE1, 1.3f);

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

    // toca um sinal de aviso quando o tempo esta acabando
    if (timer.Elapsed(Bomberman::timeLimit))
    {
        timeUp = true;
        timer.Reset();
        Bomberman::audio->Play(SE_TIMER);
    }

    // encerra o jogo ao encerrar o tempo
    if (timer.Elapsed(2) && timeUp)
        window->Close();

    // sai com o pressionar do ESC
    if (window->KeyPress(VK_ESCAPE)) {
        Bomberman::audio->Stop(MUS_STAGE1);
        Bomberman::NextLevel<Home>();
        Bomberman::player->Reset();
    }

    else if (window->KeyPress(VK_F3)) {
        Bomberman::audio->Stop(MUS_STAGE1);
        Bomberman::NextLevel<Home>();
        Bomberman::player->Reset();
    }

    else {

        // atualiza a cena do jogo;
        scene->Update();

        // detecta as colisões na cena
        scene->CollisionDetection();
    }

}

// ------------------------------------------------------------------------------

void Stage1::Draw()
{
    if (Bomberman::viewScene)
        scene->Draw();
    if (Bomberman::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Stage1::Finalize()
{
    scene->Remove(Bomberman::player, MOVING);
    scene->Remove(Bomberman::scoreboard, STATIC);
    delete scene;
}

// -------------------------------------------------------------------------------

void Stage1::CreateWalls()
{
    for (auto i = 0; i <= 12; i++)
    {
        for (auto j = 1; j <= 15; j++)
        {
            Image* buildingImg = nullptr;
            Image* shadowImg = nullptr;

            if (i != 0 && i != 12 && j != 1 && j != 15) {
                buildingImg = buildingImage;
                shadowImg = shadowImage;
            }

            if (backg->CheckGridPosition(i, j, WLL))
            {
                float posX = j * 16.0f;
                float posY = (i * 16.0f) + 32;
                Building* build = new Building(posX, posY, buildingImg, shadowImg);
                scene->Add(build, STATIC);
            }
        }
    }
    backg->OccupyGridPosition(1,2, WLL);
    backg->OccupyGridPosition(1,3, WLL);
    backg->OccupyGridPosition(2,2, WLL);

    CreateExtraWalls();
}

void Stage1::CreateExtraWalls()
{
    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 6; i++)
    {
        int numL = 4 + rand() % 8;
        int numC = 4 + rand() % 11;

        if (backg->CheckGridPosition(numL, numC, MPT))
        {
            if (numC % 2 == 0)
            {
                if (!(backg->CheckGridPosition(numL - 2, numC, MPT)) ||
                    !(backg->CheckGridPosition(numL + 2, numC, MPT)))
                {
                    i--;
                    continue;
                }
            }
            float posX = numC * 16;
            float posY = (numL * 16) + 32;
            Building* build = new Building(posX, posY, buildingImage, shadowImage);
            scene->Add(build, STATIC);
            backg->OccupyGridPosition(numL, numC, WLL);
        }
        else i--;
    }
}

void Stage1::CreateBlocks()
{
    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 39; i++)
    {
        int numLine = 1 + rand() % 11;
        int numColm = 2 + rand() % 13;

        if (backg->CheckGridPosition(numLine, numColm, MPT))
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            
            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            if (i < 20)
            {
                Powerup* powerup = new Powerup(posX, posY, (PowerUpType)i);
                scene->Add(powerup, STATIC);
            }
            backg->OccupyGridPosition(numLine, numColm, FillType::BLK);
        }
        else i--;
    }
    backg->ClearGridPosition(1, 2);
    backg->ClearGridPosition(1, 3);
    backg->ClearGridPosition(2, 2);
}

void Stage1::CreatePortal()
{
    srand(static_cast<uint>(time(0)));
    int numLine;
    int numColm;

    while (portal == nullptr)
    {
        numLine = 1 + rand() % 11;
        numColm = 2 + rand() % 13;

        if (backg->CheckGridPosition(numLine, numColm, MPT))
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            portal = new Portal(posX, posY);
            scene->Add(portal, STATIC);

            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            backg->OccupyGridPosition(posX, posY, FillType::BLK);
        }
    }
}