/**********************************************************************************
// Scoreboard (Código Fonte)
//
// Criação:     27 Jan 2013
// Atualização: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto animado
//
**********************************************************************************/

#include "Scoreboard.h"
#include "Bomberman.h"

string Scoreboard::score;
string Scoreboard::timer;
string Scoreboard::lives;
string Scoreboard::bombs;
string Scoreboard::power;


Scoreboard::Scoreboard()
{
	scoreboard = new TileSet("Resources/scoreboard.png", 272, 32, 2, 6);
	anim = new Animation(scoreboard, 0.750f, true);

	uint SeqRunning[4] = { 0, 1, 2, 3 };
	uint SeqVictory[1] = { 4 };
	uint SeqDefeat[1] = { 5 };

	anim->Add(RUNNING, SeqRunning, 4);
	anim->Add(VICTORY, SeqVictory, 1);
	anim->Add(DEFEAT, SeqDefeat, 1);

	state = RUNNING;

	MoveTo(
		window->CenterX() / Bomberman::screenScale,
		scoreboard->TileHeight() / Bomberman::screenScale
	);

	font = new Font("Resources/Tahoma10.png");
	font->Spacing("Resources/Tahoma10.dat");

}

Scoreboard::~Scoreboard()
{
	delete scoreboard;
	delete anim;
}

void Scoreboard::Update()
{
	anim->Select(state);
	anim->NextFrame();
}
void Scoreboard::Draw()
{
	anim->Draw(
		window->CenterX() / Bomberman::screenScale,
		scoreboard->TileHeight() / Bomberman::screenScale,
		Layer::FRONT
	);
	font->Draw(59, scoreboard->TileHeight() / 2.0f + 9, Scoreboard::score);
	font->Draw((scoreboard->TileWidth() / 2.0f) - 6, scoreboard->TileHeight() / 2.0f + 9, Scoreboard::timer);
	font->Draw((scoreboard->TileWidth() / 2.0f) + 50, scoreboard->TileHeight() / 2.0f + 9, Scoreboard::lives);
	font->Draw((scoreboard->TileWidth() / 2.0f) + 90, scoreboard->TileHeight() / 2.0f + 9, Scoreboard::bombs);
	font->Draw((scoreboard->TileWidth() / 2.0f) + 124, scoreboard->TileHeight() / 2.0f + 9, Scoreboard::power);
		
}