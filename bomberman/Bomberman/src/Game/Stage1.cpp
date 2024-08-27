#include "../Engine/Engine.h"
#include "Resources.h"
#include "Player.h"
#include "Bomberman.h"
#include "Home.h"
#include "Stage1.h"
#include <iostream>
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()


Scene* Stage1::scene = nullptr;

// -----------------------------------------------------------------------------

void Stage1::Init()
{
    scene = new Scene();

    //backg = new Sprite("Resources/BgStage.png");
    backg = new Background();
    scoreboard = new Scoreboard();
    CreateBoxes();
    CreateBlocks();
    timer.Start();

    scene->Add(backg, STATIC);
    scene->Add(Bomberman::player, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    //Bomberman::audio->Play(MUS_STAGE1);
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{
    Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, timer.Elapsed());
    Bomberman::scoreboard->UpdateBombs(2);
    Bomberman::scoreboard->UpdatePower(2);
    Bomberman::scoreboard->UpdateLives(3);

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

    // toca um sinal de aviso quando o tempo está acabando
    if (timer.Elapsed(Bomberman::timeLimit))
    {
        timeUp = true;
        timer.Reset();
        Bomberman::audio->Play(SE_TIMER);
    }

    // encerra o jogo ao encerrar o tempo
    if (timer.Elapsed(2) && timeUp)
        window->Close();
        

    // atualiza a cena do jogo;
    scene->Update();

    // detecta as colisões na cena
    scene->CollisionDetection();

}

// ------------------------------------------------------------------------------

void Stage1::Draw()
{
    //backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK, 2.0f);

    if (Stage1::viewScene)
        scene->Draw();
    if (Stage1::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Stage1::Finalize()
{
    delete scene;
    //delete backg;
}

// -------------------------------------------------------------------------------

void Stage1::CreateBoxes() 
{
    /*bool grid = * backg->backGrid;*/
    for (auto i = 1; i < 12; i++)
    {
        for (auto j = 2; j < 15; j++)
        {
            if (!backg->backGrid[i][j])
            { 
                float posX = j * 16;
                float posY = (i * 16) + 32;
                Building* build = new Building(posX, posY);
                scene->Add(build, STATIC);
            }
        }
    }
    backg->backGrid[1][2] = false;
    backg->backGrid[1][3] = false;
    backg->backGrid[2][2] = false;
}

void Stage1::CreateBlocks()
{
    {
        auto i = 7, j = 11;
        float posX = j * 16;
        float posY = (i * 16) + 32;
        Block* block = new Block(posX, posY);
        scene->Add(block, STATIC);
        backg->backGrid[i][j] = false;
    }

    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 39; i++)
    {
        int numLine = 1 + rand() % 11;
        int numColm = 2 + rand() % 13;

        if (backg->backGrid[numLine][numColm])
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            Block* block = new Block(posX, posY);
            scene->Add(block, STATIC);
            backg->backGrid[numLine][numColm] = false;
        }
        else i--;
    }

    /*for (auto i = 0; i < 13; i++)
    {
        for (auto j = 0; j < 17; j++)
        {
            if (backg->backGrid[i][j])
            {
                float posX = j * 16;
                float posY = (i * 16) + 32;
                Block * block = new Block(posX, posY);
                scene->Add(block, STATIC);
            }
        }
    }*/
}