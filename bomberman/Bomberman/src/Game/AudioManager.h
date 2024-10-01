/**********************************************************************************
// Gerenciador de Áudio (Arquivo de Cabeçalho)
//
// Criação:     16 Set 2024
// Atualização: 16 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:
//
**********************************************************************************/
#ifndef _BOMBERMAN_AUDIOMANAGER_H_
#define _BOMBERMAN_AUDIOMANAGER_H_

#include "../Engine/Audio.h"
#include "../Engine/Timer.h"

#include <unordered_map>         // biblioteca STL                
using std::unordered_map;        // usando tabelas de dispersão
using std::pair;

// informação <volumeStep, desiredVolume>
using FadeInfo = pair<float, float>;

// tabela de dispersão <uint, FadeInfo>
using FadeTable = unordered_map<uint, FadeInfo>;

// ------------------------------------------------------------------------------

enum Sounds {
    VO_INTRO,
    MUS_TITLE,
    MUS_STAGESTART,
    MUS_STAGECLEAR,
    MUS_WORLD1,
    MUS_GAMEOVER,
    MUS_PASSWORD,
    SE_SELECT,
    SE_TIMER,
    SE_BOMBEXPLOSION,
    SE_BOMBPLACE,
    SE_PLAYERDEATH,
    SE_ENEMYDEATH
};

// ------------------------------------------------------------------------------

class AudioManager
{
private:
    Audio* audio = nullptr;
    Timer timer;

    float audioRefreshRate;

    FadeTable fadeOutTable;
    FadeTable fadeInTable;

    void Fade(FadeTable fadeTable);

public:

    AudioManager();
    ~AudioManager();

    void Play(uint id, bool repeat = false);                // inicia a reprodução do som
    void Stop(uint id);                                     // para a reprodução do som
    void Resume(uint id);
    void Volume(uint id, float level);                      // ajusta volume do som
    void Frequency(uint id, float level);                   // ajusta a frequência do som
    bool Playing(uint id);

    void HandleAudio();                                      // atualização
    void FadeOut(uint id, float delay);                      // aplica um efeito de fade out na musica e a encerra
    void FadeIn(uint id, float delay, float desiredVolume);  // aplica um efeito de fade in na musica
};

#endif