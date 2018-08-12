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

#if SDL_THREAD_ORBIS

/* ORBIS thread management routines for SDL */

#include <stdio.h>
#include <stdlib.h>

#include "SDL_error.h"
#include "SDL_thread.h"
#include "../SDL_systhread.h"
#include "../SDL_thread_c.h"
#include <kernel.h>


void * ThreadEntry(void *arg)
{
    SDL_RunThread(arg);
    return 0;
}

int SDL_SYS_CreateThread(SDL_Thread *thread, void *args)
{
    int priority = 0;
	int ret=0;
    ScePthread thid; 
    thid = scePthreadSelf();
    if (scePthreadGetprio(thid, &priority) == 0 && priority>1) {
		ret=scePthreadCreate(&thread->handle, NULL, ThreadEntry, NULL, NULL);
		if(ret==0)
		{
			scePthreadSetprio(thread->handle, priority);
			return 0;
		}	
		else
		{
	        return SDL_SetError("scePthreadCreate() failed");
		}	
    }
    return -1;
}

void SDL_SYS_SetupThread(const char *name)
{
    /* Do nothing. */
}

SDL_threadID SDL_ThreadID(void)
{
    return (SDL_threadID) scePthreadSelf();
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
    scePthreadJoin(thread->handle, NULL);
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
    scePthreadDetach(thread->handle);
}

/*void SDL_SYS_KillThread(SDL_Thread *thread)
{
    scePthreadExit(NULL);
}
*/
int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
    int ret=0;

    ScePthread thid; 
    thid = scePthreadSelf();
	ret=scePthreadSetprio(thid, priority);
	if(ret<0)
	{
		return -1;
	}
	return ret;
}

#endif /* SDL_THREAD_ORBIS */

/* vim: ts=4 sw=4
 */
