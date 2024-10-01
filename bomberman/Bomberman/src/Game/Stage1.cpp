#include "../Engine/Engine.h"
#include "../Engine/Random.h"
#include "Bomberman.h"
#include "Player.h"
#include "Home.h"
#include "GameOver.h"
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

    enemypool = { PUROPEN, DENKYUN };

    CreateBoxes();
    CreatePortal();
    CreateBlocks();
    CreateEnemies(PUROPEN, 3);
    CreateEnemies(DENKYUN, 2);

    // Limpa as posições no fundo
    for (const auto& position : enemyPositions) {
        int column = position.first;
        int line = position.second;
        backg->ClearGridPosition(line, column);
    }

    timer.Start();

    scene->Add(backg, STATIC);
    scene->Add(Bomberman::player, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    Bomberman::player->Reset();

    Bomberman::audioManager->Frequency(MUS_WORLD1, 1.0f);
    Bomberman::audioManager->Volume(MUS_WORLD1, Bomberman::MUSVolume);
    Bomberman::audioManager->Play(MUS_WORLD1, true);
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{
    // verifica se todos os inimigos foram derrotados
    ValidateEnemyStatus();

    // ativa o portal caso não haja mais inimigos na tela
    portal->Activate(enemiesCleared);

    // atualiza o timer do scoreboard se o tempo não tiver esgotado
    if (!timeUp)
        Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, timer.Elapsed());

    // acelera a musica quando faltar 30 segundos
    if (timer.Elapsed(Bomberman::timeLimit - 30.0f))
        Bomberman::audioManager->Frequency(MUS_WORLD1, 1.3f);

    // toca um sinal de aviso quando o tempo esta acabando
    if (timer.Elapsed(Bomberman::timeLimit))
    {
        timeUp = true;
        timer.Reset();
        Bomberman::player->Die(LOSING);
        Bomberman::audioManager->Play(SE_TIMER);
    }

    // encerra o jogo ao encerrar o tempo
    if (!Bomberman::audioManager->Playing(SE_TIMER) && timeUp && Bomberman::player->IsAlive())
        Bomberman::NextLevel<Stage1>();

    // verifica situações de game over
    else if (!Bomberman::player->IsAlive() && (!timeUp || !Bomberman::audioManager->Playing(SE_TIMER)))
        Bomberman::NextLevel<GameOver>();

    else if (portal->Transition())
        OutputDebugString("");

    // sai com o pressionar do ESC
    else if (window->KeyPress(VK_ESCAPE))
        Bomberman::NextLevel<Home>();

    else if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

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
    Bomberman::audioManager->Stop(MUS_WORLD1);
    Bomberman::player->Reset();
    scene->Remove(Bomberman::player, MOVING);
    scene->Remove(Bomberman::scoreboard, STATIC);
    delete scene;
}

// -------------------------------------------------------------------------------

void Stage1::ValidateEnemyStatus()
{
    if (scene->MovingSize() == 1 && !enemiesCleared)
        enemiesCleared = true;
}

void Stage1::CreateBoxes()
{
    for (auto i = 0; i < 13; i++)
    {
        for (auto j = 1; j < 16; j++)
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

void Stage1::CreateEnemies(uint enemyType, int ammount)
{
    int count = 0;
    RandI lineDist{ 1, 8 };
    RandI columnDist{ 1, 11 };
    enemyType = EnemyTypes(enemyType);

    while (count < ammount) {
        int line = lineDist.Rand();
        int column = columnDist.Rand();

        if (backg->CheckGridPosition(line, column))
        {
            count++;

            float posX = column * 16 + 8;
            float posY = line * 16 + 32;

            Bomberman::enemyFactory->CreateEnemy(enemyType, posX, posY, this->scene);

            backg->OccupyGridPosition(line, column);
            enemyPositions.push_back(pair(column, line));
        }
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
            portal = new Portal(posX, posY, this->scene, &enemypool);
            scene->Add(portal, STATIC);
        }
    }
}