/**********************************************************************************
// Bomberman
//
// Criação:     14 Set 2024
// Atualização: 14 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   Tela de game over do Bomberman
//
**********************************************************************************/

// ------------------------------------------------------------------------------

#include "GameOver.h"
#include "Home.h"
#include "Stage1.h"
#include "Bomberman.h"

// ------------------------------------------------------------------------------

void GameOver::Init()
{
    bgImage = new Sprite("Resources/Sprites/gameover/BgGameOver.png");
    
    bombermanAsset = new TileSet("Resources/Sprites/gameover/AssetSprite.png", 40, 48, 8, 8);
    arrowAsset = new TileSet("Resources/Sprites/gameover/guiArrow.png", 8, 16, 4, 8);

    assetAnimation = new Animation(bombermanAsset, 0.08f, false);
    arrowAnimation = new Animation(arrowAsset, 0.1f, true);

    uint seqDefeat[1] = { 0 };
    uint seqPersist[6] = { 1, 2, 3, 4, 5, 6 };
    uint seqSurrender[5] = { 7, 0, 7, 0, 7 };

    uint seqRight[4] = { 0, 1, 2, 3 };
    uint seqLeft[4] = { 4, 5, 6, 7 };

    assetAnimation->Add(PERSIST,    seqPersist,     6);
    assetAnimation->Add(SURRENDER,  seqSurrender,   5);
    assetAnimation->Add(DEFEAT,     seqDefeat,      1);

    arrowAnimation->Add(RIGHT,      seqRight,       4);
    arrowAnimation->Add(LEFT,       seqLeft,        4);

    yPos = (window->CenterY() + 2.5f * bombermanAsset->Height()) / Bomberman::screenScale;

    // inicia tocando uma música 
    Bomberman::audioManager->Play(MUS_GAMEOVER, true);
    Bomberman::audioManager->Volume(MUS_GAMEOVER, Bomberman::MUSVolume);
}

// ------------------------------------------------------------------------------

void GameOver::Update()
{

    // sai com pressionamento do ESC
    if (choice == DEFEAT && window->KeyPress(VK_LEFT))
        selected = LEFT;
    else if (choice == DEFEAT && window->KeyPress(VK_RIGHT))
        selected = RIGHT;

    arrowAnimation->Select(selected);
    xPos = (window->CenterX() + 24 * (-1.0f + 2.0f * selected)) / Bomberman::screenScale;

    // avança com pressionamento do ENTER
    if (choice == DEFEAT && window->KeyPress(VK_RETURN)) {
        switch (selected)
        {
        case LEFT:
            choice = PERSIST;
            break;
        case RIGHT:
            choice = SURRENDER;
            break;
        }
    }

    assetAnimation->Select(choice);
    arrowAnimation->Select(selected);
    assetAnimation->NextFrame();
    arrowAnimation->NextFrame();
    
    switch (choice)
    {
    case SURRENDER:
        if (assetAnimation->Inactive()) {
            Sleep(500);
            Bomberman::NextLevel<Home>();
        }
        break;

    case PERSIST:
        if (assetAnimation->Frame() == 5)
            assetSpeed = 350.0f;

        yPos += gameTime * -1.0f * assetSpeed;  // movimenta o asset para cima

        if (yPos <= 0)                          // chama a proxima tela quando o asset sai da tela
            Bomberman::NextLevel<Stage1>();
        break;

    case DEFEAT:
    default:
        break;
    }
}

// ------------------------------------------------------------------------------

void GameOver::Draw()
{
    bgImage->Draw(
        window->CenterX() / Bomberman::screenScale,
        window->CenterY() / Bomberman::screenScale,
        Layer::BACK
    );
    assetAnimation->Draw(
        window->CenterX() / Bomberman::screenScale,
        yPos
    );
    arrowAnimation->Draw(
        xPos,
        (window->CenterY() / Bomberman::screenScale) - (arrowAsset->Height() * 3.0f / Bomberman::screenScale),
        Layer::LOWER
    );
}

// ------------------------------------------------------------------------------

void GameOver::Finalize()
{
    Bomberman::audioManager->Stop(MUS_GAMEOVER);
    delete bgImage;
    delete bombermanAsset;
    delete assetAnimation;
    delete arrowAsset;
    delete arrowAnimation;
}