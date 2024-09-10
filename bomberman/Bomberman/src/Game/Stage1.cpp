#include "../Engine/Engine.h"
#include "Resources.h"
#include "Player.h"
#include "Bomberman.h"
#include "Home.h"
#include "Stage1.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()


Scene* Stage1::scene = nullptr;
Background* Stage1::backg = nullptr;

// -----------------------------------------------------------------------------

void Stage1::Init()
{
    scene = new Scene();

    backg = new Background();
    scoreboard = new Scoreboard();

    CreateBoxes();
    CreatePortal();
    CreateBlocks();

    timer.Start();

    scene->Add(backg, STATIC);
    scene->Add(Bomberman::player, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    Bomberman::player->SoftReset();

    Bomberman::audio->Play(MUS_STAGE1, true);
    Bomberman::audio->Volume(MUS_STAGE1, Bomberman::MUSVolume);
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

void Stage1::CreateBoxes()
{
    for (auto i = 1; i < 12; i++)
    {
        for (auto j = 2; j < 15; j++)
        {
            if (!backg->CheckGridPosition(i, j))
            {
                float posX = j * 16.0f;
                float posY = (i * 16.0f) + 32;
                Building* build = new Building(posX, posY);
                scene->Add(build, STATIC);
            }
        }
    }
    backg->OccupyGridPosition(1, 2);
    backg->OccupyGridPosition(1, 3);
    backg->OccupyGridPosition(2, 2);

    CreateExtraBoxes();
}

void Stage1::CreateExtraBoxes()
{
    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 6; i++)
    {
        int numL = 4 + rand() % 8;
        int numC = 4 + rand() % 11;

        if (backg->backGrid[numL][numC])
        {
            float posX = numC * 16;
            float posY = (numL * 16) + 32;
            Building* build = new Building(posX, posY);
            scene->Add(build, STATIC);
            backg->OccupyGridPosition(numL, numC);
        }
        else i--;
    }
}

void Stage1::CreateBlocks()
{
    float posX = portal->X();
    float posY = portal->Y();
    Block* block = new Block(posX - 8, posY - 8);
    scene->Add(block, STATIC);
    backg->OccupyGridPosition(posX, posY);

    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 39; i++)
    {
        int numLine = 1 + rand() % 11;
        int numColm = 2 + rand() % 13;

        if (backg->CheckGridPosition(numLine, numColm))
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            backg->OccupyGridPosition(numLine, numColm);
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

        if (backg->CheckGridPosition(numLine, numColm))
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            portal = new Portal(posX, posY);
            scene->Add(portal, STATIC);
        }
    }
}