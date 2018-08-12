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

#ifndef _SDL_orbisvideo_h
#define _SDL_orbisvideo_h

#include "../../SDL_internal.h"
#include "../SDL_sysvideo.h"

typedef struct SDL_VideoData
{
	SDL_bool gl_initialized;   /* OpenGL device initialization status */
	uint32_t gl_refcount;      /* OpenGL reference count              */

} SDL_VideoData;


typedef struct SDL_DisplayData
{

} SDL_DisplayData;


typedef struct SDL_WindowData
{
    SDL_bool uses_gl;			/* if true window must support OpenGL */

} SDL_WindowData;

extern SDL_Window * Orbis_Window;


/****************************************************************************/
/* SDL_VideoDevice functions declaration                                    */
/****************************************************************************/

/* Display and window functions */
int ORBIS_VideoInit(_THIS);
void ORBIS_VideoQuit(_THIS);
void ORBIS_GetDisplayModes(_THIS, SDL_VideoDisplay * display);
int ORBIS_SetDisplayMode(_THIS, SDL_VideoDisplay * display, SDL_DisplayMode * mode);
int ORBIS_CreateWindow(_THIS, SDL_Window * window);
int ORBIS_CreateWindowFrom(_THIS, SDL_Window * window, const void *data);
void ORBIS_SetWindowTitle(_THIS, SDL_Window * window);
void ORBIS_SetWindowIcon(_THIS, SDL_Window * window, SDL_Surface * icon);
void ORBIS_SetWindowPosition(_THIS, SDL_Window * window);
void ORBIS_SetWindowSize(_THIS, SDL_Window * window);
void ORBIS_ShowWindow(_THIS, SDL_Window * window);
void ORBIS_HideWindow(_THIS, SDL_Window * window);
void ORBIS_RaiseWindow(_THIS, SDL_Window * window);
void ORBIS_MaximizeWindow(_THIS, SDL_Window * window);
void ORBIS_MinimizeWindow(_THIS, SDL_Window * window);
void ORBIS_RestoreWindow(_THIS, SDL_Window * window);
void ORBIS_SetWindowGrab(_THIS, SDL_Window * window, SDL_bool grabbed);
void ORBIS_DestroyWindow(_THIS, SDL_Window * window);

/* Window manager function */
SDL_bool ORBIS_GetWindowWMInfo(_THIS, SDL_Window * window,
                             struct SDL_SysWMinfo *info);


/* ORBIS on screen keyboard */
SDL_bool ORBIS_HasScreenKeyboardSupport(_THIS);
void ORBIS_ShowScreenKeyboard(_THIS, SDL_Window *window);
void ORBIS_HideScreenKeyboard(_THIS, SDL_Window *window);
SDL_bool ORBIS_IsScreenKeyboardShown(_THIS, SDL_Window *window);

void ORBIS_PumpEvents(_THIS);

#endif /* _SDL_orbisvideo_h */

/* vi: set ts=4 sw=4 expandtab: */
