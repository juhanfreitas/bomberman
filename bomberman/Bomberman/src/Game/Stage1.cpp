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

    backg = new Background();
    scoreboard = new Scoreboard();
    CreateBoxes();
    CreatePortal();
    CreateBlocks();
    timer.Start();

    scene->Add(backg, STATIC);
    scene->Add(portal, STATIC);
    scene->Add(Bomberman::player, MOVING);
    scene->Add(Bomberman::scoreboard, STATIC);

    //Bomberman::audio->Play(MUS_STAGE1);
}

// ------------------------------------------------------------------------------

void Stage1::Update()
{

    Bomberman::scoreboard->UpdateTimer(Bomberman::timeLimit, timer.Elapsed());

    // sai com o pressionar do ESC
    if (window->KeyDown(VK_ESCAPE))
        window->Close();
    /*if (window->KeyPress('P'))
        Stage1::OnPause();*/

    if (window->KeyPress(VK_F1))
        viewBBox = !viewBBox;

    if (window->KeyPress(VK_F2))
        viewScene = !viewScene;

    if (window->KeyPress(VK_F3))
        Bomberman::NextLevel<Home>();

    // toca um sinal de aviso quando o tempo est� acabando
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

    // detecta as colis�es na cena
    scene->CollisionDetection();

}

// ------------------------------------------------------------------------------

void Stage1::Draw()
{
    
    if (viewScene)
        scene->Draw();
    if (viewBBox)
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
            if (!backg->backGrid[i][j])
            {
                float posX = j * 16.0f;
                float posY = (i * 16.0f) + 32;
                Building* build = new Building(posX, posY);
                scene->Add(build, STATIC);
            }
        }
    }
    backg->backGrid[1][2] = false;
    backg->backGrid[1][3] = false;
    backg->backGrid[2][2] = false;

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
            backg->backGrid[numL][numC] = false;
        }
        else i--;
    }
}

void Stage1::CreateBlocks()
{
    float posX = portal->X();
    float posY = portal->Y();
    Block* block = new Block(posX-8, posY-8);
    scene->Add(block, MOVING);
    int numColm = (int)posX / 16;
    int numLine = ((int)posY - 32) / 16;
    backg->backGrid[numLine][numColm] = false;
    

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
            scene->Add(block, MOVING);
            backg->backGrid[numLine][numColm] = false;
        }
        else i--;
    }
}

void Stage1::CreatePortal()
{
    srand(static_cast<uint>(time(0)));

    for (auto i = 0; i < 1; i++)
    {
        int numLine = 1 + rand() % 11;
        int numColm = 2 + rand() % 13;

        if (backg->backGrid[numLine][numColm])
        {
            float posX = numColm * 16;
            float posY = (numLine * 16) + 32;
            portal = new Portal(posX, posY);
        }
        else i = 0;
    }
}