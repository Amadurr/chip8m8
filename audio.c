//
// Created by Kringle on 24.05.2016.
//
#include "app.h"

#define MUS_PATH "beep.wav"

static Uint8* audio_pos;
static Uint32 audio_len;
static bool playing;

void my_audio_callback(void *userdata, Uint8 *Stream, int len);

bool Audio(unsigned char ST)
{
    // local variables
    static Uint32 audio_Length; // length of our sample
    static Uint8 *audio_Buffer; // buffer containing our audio file
    //static SDL_AudioSpec want, have; // the specs of our piece of music
    static SDL_AudioSpec audio; // the specs of our piece of music
    if(ST != 0 && playing == false) {

        if (SDL_LoadWAV("beep.wav", &audio, &audio_Buffer, &audio_Length) == NULL) {
            fprintf(stderr, "Failed to load audio: %s\n", SDL_GetError());
            return false;
        }
        audio.samples = 2048;
        audio.callback = my_audio_callback;
        audio.userdata = NULL;


        audio_pos = audio_Buffer;
        audio_len = audio_Length;

        if (SDL_OpenAudio(&audio, NULL) < 0) {
            printf("SDL failed to open audio device: %s\n", SDL_GetError());
            return false;
        }
        SDL_PauseAudio(0);
        playing = true;
    }
    if(ST == 0 && playing == true)
    {
        SDL_CloseAudio();
        SDL_FreeWAV(audio_Buffer);
        playing = false;

    }
    return true;
}

void my_audio_callback(void *userdata, Uint8 *Stream, int len)
{
    if(audio_len == 0)
        return;
    len = (len > audio_len ? audio_len : len);
    SDL_MixAudioFormat(Stream, audio_pos,AUDIO_F32, len, SDL_MIX_MAXVOLUME);

    audio_pos += len;
    audio_len -= len;
}