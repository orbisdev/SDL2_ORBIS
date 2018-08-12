/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2015 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#if SDL_AUDIO_DRIVER_ORBIS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SDL_audio.h"
#include "SDL_error.h"
#include "SDL_timer.h"
#include "../SDL_audio_c.h"
#include "../SDL_audiodev_c.h"
#include "../SDL_sysaudio.h"
#include "SDL_orbisaudio.h"

#include <kernel.h>
#include <orbisAudio.h>


/* The tag name used by VITA audio */
#define ORBISAUD_DRIVER_NAME         "orbisaudio"

static int
ORBISAUD_OpenDevice(_THIS, void *handle, const char *devname, int iscapture)
{
    int i;
    this->hidden = (struct SDL_PrivateAudioData *)
        SDL_malloc(sizeof(*this->hidden));
    if (this->hidden == NULL) {
        return SDL_OutOfMemory();
    }
    SDL_memset(this->hidden, 0, sizeof(*this->hidden));
    switch (this->spec.format & 0xff) {
        case 16:
            this->spec.format = AUDIO_S16LSB;
            break;
        default:
            return SDL_SetError("Unsupported audio format");
    }
    OrbisAudioConfig *audioConf=orbisAudioGetConf();
    if(audioConf!=NULL)
    {
        if(audioConf->channels[ORBISAUDIO_CHANNEL_MAIN]->orbisaudiochannel_initialized==1)
        {
            this->spec.channels = audioConf->channels[ORBISAUDIO_CHANNEL_MAIN]->stereo*2;  
            this->spec.size = audioConf->channels[ORBISAUDIO_CHANNEL_MAIN]->samples[0]*16*this->spec.channels;
            this->spec.freq = 48000;
            this->spec.silence = 0x00;
            this->hidden->channel=audioConf->channels[ORBISAUDIO_CHANNEL_MAIN]->audioHandle;

            /* Allocate the mixing buffer.  Its size and starting address must
            be a multiple of ORBISAUDIO_MIN_LEN bytes.  Our sample count is already a multiple of
            ORBISAUDIO_MIN_LEN, so spec->size should be a multiple of ORBISAUDIO_MIN_LEN as well. */
            this->hidden->rawbuf = (Uint8 *) SDL_malloc(this->spec.size * NUM_BUFFERS);
            // this->hidden->rawbuf = (Uint8 *) memalign(ORBISAUDIO_MIN_LEN, mixlen);
            if (this->hidden->rawbuf == NULL) {
                return SDL_SetError("Couldn't allocate mixing buffer");
            }
        }
        else
        {
            free(this->hidden->rawbuf);
            this->hidden->rawbuf = NULL;
            return SDL_SetError("Couldn't reserve hardware channel");
        }
    }
    memset(this->hidden->rawbuf, 0, this->spec.size * NUM_BUFFERS);
    for (i = 0; i < NUM_BUFFERS; i++) {
        this->hidden->mixbufs[i] = &this->hidden->rawbuf[i * this->spec.size];
    }

    this->hidden->next_buffer = 0;
    return 0;
}

static void ORBISAUD_PlayDevice(_THIS)
{

    orbisAudioPlayBlock(ORBISAUDIO_CHANNEL_MAIN,ORBISAUDIO_VOLUME_MAX,ORBISAUDIO_VOLUME_MAX,this->hidden->mixbufs[this->hidden->next_buffer]);
    this->hidden->next_buffer = (this->hidden->next_buffer + 1) % NUM_BUFFERS;
}

/* This function waits until it is possible to write a full sound buffer */
static void ORBISAUD_WaitDevice(_THIS)
{
    /* Because we block when sending audio, there's no need for this function to do anything. */
}
static Uint8 *ORBISAUD_GetDeviceBuf(_THIS)
{
    return this->hidden->mixbufs[this->hidden->next_buffer];
}

static void ORBISAUD_CloseDevice(_THIS)
{
    if (this->hidden->channel >= 0) {
        orbisAudioStop();
        this->hidden->channel = -1;
    }

    if (this->hidden->rawbuf != NULL) {
        free(this->hidden->rawbuf);
        this->hidden->rawbuf = NULL;
    }
}
static void ORBISAUD_ThreadInit(_THIS)
{
    /* Increase the priority of this audio thread by 1 to put it
       ahead of other SDL threads. */
    ScePthread thid; 
    int priority=0;
    thid = scePthreadSelf();
    if (scePthreadGetprio(thid, &priority) == 0 && priority>1) {
        scePthreadSetprio(thid, priority - 1);
    }
}


static int
ORBISAUD_Init(SDL_AudioDriverImpl * impl)
{

    /* Set the function pointers */
    impl->OpenDevice = ORBISAUD_OpenDevice;
    impl->PlayDevice = ORBISAUD_PlayDevice;
    impl->WaitDevice = ORBISAUD_WaitDevice;
    impl->GetDeviceBuf = ORBISAUD_GetDeviceBuf;
    impl->CloseDevice = ORBISAUD_CloseDevice;
    impl->ThreadInit = ORBISAUD_ThreadInit;

    /* ORBIS audio device */
    impl->OnlyHasDefaultOutputDevice = 1;
/*
    impl->HasCaptureSupport = 1;

    impl->OnlyHasDefaultInputDevice = 1;
*/
    /*
    impl->DetectDevices = DSOUND_DetectDevices;
    impl->Deinitialize = DSOUND_Deinitialize;
    */
    if(orbisAudioGetStatus(ORBISAUDIO_CHANNEL_MAIN)==1)
    { 
        return 1;   /* this audio target is available. */
    }
    else
    {
        return -1;
    }
}

AudioBootStrap ORBISAUD_bootstrap = {
    "orbisaudio", "Orbis audio driver", ORBISAUD_Init, 0
};

 /* SDL_AUDI */

#endif /* SDL_AUDIO_DRIVER_ORBIS */

/* vi: set ts=4 sw=4 expandtab: */
