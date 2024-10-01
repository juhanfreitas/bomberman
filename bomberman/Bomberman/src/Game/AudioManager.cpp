/**********************************************************************************
// Gerenciador de Áudio (Código Fonte)
//
// Criação:     16 Set 2024
// Atualização: 16 Set 2024
// Compilador:  Visual C++ 2022
//
// Descrição:   
//
**********************************************************************************/

#include "AudioManager.h"

#include <list>
using namespace std;


AudioManager::AudioManager() : audioRefreshRate(0.1f)
{
	audio = new Audio();
    timer.Start();

    // --------------------------
    // Voices
    // --------------------------
    audio->Add(VO_INTRO, "Resources/Sounds/Voices/By Hudson.wav");

    // --------------------------
    // Musics
    // --------------------------
    audio->Add(MUS_TITLE, "Resources/Sounds/Music/Title Theme.wav");
    audio->Add(MUS_WORLD1, "Resources/Sounds/Music/World 1.wav");
    audio->Add(MUS_GAMEOVER, "Resources/Sounds/Music/Game Over.wav");
    audio->Add(MUS_PASSWORD, "Resources/Sounds/Music/Password.wav");
    audio->Add(MUS_STAGESTART, "Resources/Sounds/Music/Stage Start.wav");
    audio->Add(MUS_STAGECLEAR, "Resources/Sounds/Music/Stage Clear.wav");

    // --------------------------
    // Sound Effects
    // --------------------------
    audio->Add(SE_TIMER, "Resources/Sounds/Sound Effects/Timer.wav");
    audio->Add(SE_SELECT, "Resources/Sounds/Sound Effects/Menu Select.wav");
    audio->Add(SE_BOMBEXPLOSION, "Resources/Sounds/Sound Effects/Bomb Explodes.wav");
    audio->Add(SE_BOMBPLACE, "Resources/Sounds/Sound Effects/Place Bomb.wav");
    audio->Add(SE_PLAYERDEATH, "Resources/Sounds/Sound Effects/Player Death.wav");
    audio->Add(SE_ENEMYDEATH, "Resources/Sounds/Sound Effects/Enemy Death.wav");
}

AudioManager::~AudioManager()
{
    delete audio;
}

void AudioManager::HandleAudio()
{
    
    if (timer.Elapsed(audioRefreshRate)) {

        // --------------------------
        // Fade
        // --------------------------
        if (!fadeOutTable.empty()) {
            Fade(fadeOutTable);
            timer.Reset();
        }
        if (!fadeInTable.empty()) {
            Fade(fadeInTable);
            timer.Reset();
        }
    }
}

// ------------------------------------------------------------------------------

void AudioManager::FadeOut(uint id, float delay)
{
    // cria nova informação do efeito
    float volumeStep = -1.0f * (audio->Volume(id) / delay * audioRefreshRate);
    FadeInfo fadeInfo(volumeStep, 0.0f);

    // insere informação do efeito
    fadeOutTable[id] = fadeInfo;
}

void AudioManager::FadeIn(uint id, float delay, float desiredVolume)
{
    audio->Volume(id, 0.0f);

    // cria nova informação do efeito
    float volumeStep = desiredVolume / delay * audioRefreshRate;
    FadeInfo fadeInfo(volumeStep, desiredVolume);

    // insere informação do efeito
    fadeInTable[id] = fadeInfo;
}

void AudioManager::Fade(FadeTable fadeTable)
{
    list<uint> deletionQueue;

    for (auto it = fadeTable.begin(); it != fadeTable.end(); ++it) {
        uint soundId = it->first;
        FadeInfo fadeInfo = it->second;

        float volumeStep = fadeInfo.first;
        float desiredVolume = fadeInfo.second;

        audio->Volume(soundId, audio->Volume(soundId) + volumeStep);

        // fade out - desiredVolume = 0
        if (volumeStep < 0 && audio->Volume(soundId) <= desiredVolume) {
            audio->Stop(soundId);
            deletionQueue.push_back(soundId);
        }
        // fade in
        else if (volumeStep > 0 && audio->Volume(soundId) >= desiredVolume) {
            audio->Volume(soundId, desiredVolume);  // se certifica que o volume será exatamente o desejado
            deletionQueue.push_back(soundId);
        }
    }

    for (uint soundId : deletionQueue) {
        fadeTable.erase(soundId);
    }
}

// ------------------------------------------------------------------------------

void AudioManager::Play(uint id, bool repeat)
{
    // se certifica de parar a aplicação de efeitos no som
    fadeInTable.erase(id);
    fadeOutTable.erase(id);
    audio->Play(id, repeat);
}

void AudioManager::Stop(uint id)
{ audio->Stop(id); }

void AudioManager::Resume(uint id)
{ audio->Resume(id); }

void AudioManager::Volume(uint id, float level)
{ audio->Volume(id, level); }

void AudioManager::Frequency(uint id, float level)
{ audio->Frequency(id, level); }

bool AudioManager::Playing(uint id)
{ return audio->Playing(id); }