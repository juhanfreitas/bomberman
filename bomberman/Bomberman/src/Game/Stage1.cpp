#include "../Engine/Engine.h"
#include "../Engine/Random.h"
#include "Bomberman.h"
#include "Player.h"
#include "Home.h"
#include "GameOver.h"
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

    enemypool = { PUROPEN, DENKYUN };
    
    CreateWalls();
    CreatePortal();
    CreateEnemies(PUROPEN, 3);
    CreateEnemies(DENKYUN, 2);
    CreateBlocks();

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
        Bomberman::player->State(LOSING);
        Bomberman::audioManager->Play(SE_TIMER);
    }

    // verifica se o player pode passar de fase
    if (portal->Transition() && !transitioning) {
        transitioning = true;
        transitionTimer.Start();
        Bomberman::player->State(WINNING);
    }

    // ------------------------------------------------
    // mudança de tela
    // ------------------------------------------------

    // encerra o jogo ao encerrar o tempo
    if (!Bomberman::audioManager->Playing(SE_TIMER) && timeUp && Bomberman::player->IsAlive())
        Bomberman::NextLevel<Stage1>();

    // verifica situações de game over
    else if (!Bomberman::player->IsAlive() && (!timeUp || !Bomberman::audioManager->Playing(SE_TIMER)))
        Bomberman::NextLevel<GameOver>();

    else if (transitionTimer.Elapsed(2.0f) && transitioning)
        Bomberman::NextLevel<GameOver>();

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

void Stage1::CreateEnemies(uint enemyType, int ammount)
{
    int count = 0;
    RandI lineDist{ 1, 8 };
    RandI columnDist{ 1, 11 };
    enemyType = EnemyTypes(enemyType);

    while (count < ammount) {
        int line = lineDist.Rand();
        int column = columnDist.Rand();

        if (backg->CheckGridPosition(line, column, MPT))
        {
            count++;

            float posX = column * 16 + 8;
            float posY = line * 16 + 32;

            Bomberman::enemyFactory->CreateEnemy(enemyType, posX, posY, this->scene);

            backg->OccupyGridPosition(line, column, WLL);
            enemyPositions.push_back(pair(column, line));
        }
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
            portal = new Portal(posX, posY, this->scene, &enemypool);
            scene->Add(portal, STATIC);

            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            backg->OccupyGridPosition(posX, posY, FillType::BLK);
        }
    }
}