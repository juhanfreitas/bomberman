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
        bGrid->ClearGridPosition(line, column);
    }

    timer.Start();
    scene->Add(backg, STATIC);
    
    scene->Add(Bomberman::player1, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    Size(backg->Width(), backg->Height());
    

    Bomberman::audioManager->Frequency(MUS_WORLD1, 1.0f);
    Bomberman::audioManager->Volume(MUS_WORLD1, Bomberman::MUSVolume);
    Bomberman::audioManager->Play(MUS_WORLD1, true);
    Bomberman::levelTime.Start();
    Bomberman::player->Reset();
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{
    // verifica se todos os inimigos foram derrotados
    ValidateEnemyStatus();

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();
    // ativa o portal caso não haja mais inimigos na tela
    portal->Activate(enemiesCleared);

    // atualiza o timer do scoreboard se o tempo não tiver esgotado
    if (!timeUp)
        Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, timer.Elapsed());

    // acelera a musica quando faltar 30 segundos
    if (timer.Elapsed(Bomberman::timeLimit - 30.0f))
        Bomberman::audioManager->Frequency(MUS_WORLD1, 1.3f);

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
        Bomberman::player1->State(LOSING);
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
    {
        backg->Draw(&gameview);
        scene->Draw();
    }
    if (Bomberman::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Stage1::Finalize()
{
    Bomberman::audioManager->Stop(MUS_WORLD1);
    Bomberman::player1->Reset();
    scene->Remove(Bomberman::player1, MOVING);
    scene->Remove(backg, STATIC);
    scene->Remove(portal, STATIC);
    scene->Remove(Bomberman::scoreboard, STATIC);
    delete scene;
}

// -------------------------------------------------------------------------------

void Stage1::ValidateEnemyStatus()
{
    if (scene->MovingSize() == 1 && !enemiesCleared)
        enemiesCleared = true;
}

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

    while (!portal)
    {
        numLine = 1 + rand() % 11;
        numColm = 1 + rand() % 46;

        if (bGrid->CheckGridPosition(numLine, numColm, MPT))
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            portal = new Portal(posX, posY, this->scene, &enemypool);
            scene->Add(portal, STATIC);

            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            bGrid->OccupyGridPosition(posX, posY, FillType::BLK);
        }
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