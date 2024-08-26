/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     27 Jan 2013
// Atualização: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto animado
//
**********************************************************************************/
#pragma once
#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "../Engine/Types.h"                      // tipos específicos da engine
#include "../Engine/Object.h"                     // interface de Object
#include "../Engine/Animation.h"                  // animação de sprites
#include "../Engine/Font.h"

#include <sstream>
#include <iomanip>

// ------------------------------------------------------------------------------

enum TimerState { RUNNING, VICTORY, DEFEAT };

// ---------------------------------------------------------------------------------

class Scoreboard : public Object
{
private:
    TileSet* scoreboard;                // folha de sprites do personagem
    Animation* anim;                   // animação do personagem
    Font * font;
    static string score;
    static string timer;
    static string lives;
    static string bombs;
    static string power;

public:
    uint state;                         // estado atual do personagem
    uint scoreboardHeight;

    Scoreboard();                             // construtor
    ~Scoreboard();                            // destrutor

    static void UpdateScore(uint score);
    static void UpdateTimer(float timeLimit, float gameTime);
    static void UpdateLives(uint lives);
	static void UpdateBombs(uint bombs);
	static void UpdatePower(uint power);

    void Update();                      // atualização do objeto
    void Draw();                        // desenho do objeto

    uint Height() const;
	static std::string SetBoardText(uint value, uint lenght);
	static std::string SetBoardText(uint value, uint secondValue, string separator, uint lenght);
};

// ---------------------------------------------------------------------------------
// Função Membro Inline

// retorna a altura do objeto

inline uint Scoreboard::Height() const
{
	return scoreboardHeight;
}

inline std::string Scoreboard::SetBoardText(
	uint value,
	uint lenght)
{
	std::stringstream ss;
	ss << std::setw(lenght) << std::setfill('0') << value;
	return ss.str();
}

inline std::string Scoreboard::SetBoardText(
	uint firstValue,
	uint secondValue,
	string separator,
	uint lenght)
{
	std::stringstream ss;
	ss << firstValue << separator << std::setw(lenght) << std::setfill('0') << secondValue;
	return ss.str();
}

inline void Scoreboard::UpdateScore(uint score)
{
	Scoreboard::score = SetBoardText(score, 5);
}
inline void Scoreboard::UpdateTimer(float timeLimit, float gameTime) {
	uint remainingTime = static_cast<uint>((timeLimit - gameTime > 0) ? timeLimit - gameTime : 0);
	uint minutes = remainingTime / 60;
	uint seconds = remainingTime % 60;
	Scoreboard::timer = SetBoardText(minutes, seconds, ":", 2);
}
inline void Scoreboard::UpdateLives(uint lives) {
	Scoreboard::lives = SetBoardText(lives, 2);
}
inline void Scoreboard::UpdateBombs(uint bombs) {
	Scoreboard::bombs = SetBoardText(bombs, 1);
}
inline void Scoreboard::UpdatePower(uint power) {
	Scoreboard::power = SetBoardText(power, 1);
}

// ---------------------------------------------------------------------------------

#endif _SCOREBOARD_H_