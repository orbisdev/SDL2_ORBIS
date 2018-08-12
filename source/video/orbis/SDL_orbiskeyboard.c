/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2017 Sam Lantinga <slouken@libsdl.org>

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

#if SDL_VIDEO_DRIVER_ORBIS
#include <types/userservice.h>
#include <orbisKeyboard.h>


#include "SDL_events.h"
#include "SDL_log.h"
#include "SDL_orbisvideo.h"
#include "SDL_orbiskeyboard.h"
#include "../../events/SDL_keyboard_c.h"

int keyboard_hid_handle = -1;
Uint8 prev_key = 0;
Uint8 prev_modifiers = 0;


void 
ORBIS_InitKeyboard(void)
{
	//check if liborbis have opened keyboard already
	if(orbisKeyboardGetStatus() == 0) {
		keyboard_hid_handle = orbisKeyboardGetHandle();
	}
	else
	{
		keyboard_hid_handle = -1;
	}
}

void 
ORBIS_PollKeyboard(void)
{
	// We skip polling keyboard if no window is created
	if (Orbis_Window == NULL)
		return;

	if (keyboard_hid_handle == 0)
	{
		orbisKeyboardUpdate();
		
		// Numlock and Capslock state changes only on a SDL_PRESSED event
		if (orbisKeyboardGetCapsKey()) {
			SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_CAPSLOCK);				
		}
		else {		
			SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_CAPSLOCK);
			SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_CAPSLOCK);
			SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_CAPSLOCK);	
		}
		/*
		if () {	
			SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_SCROLLLOCK);
		}
		else {	
			SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_SCROLLLOCK);
					
		}*/

		Uint8 changed_modifiers = orbisKeyboardGetSpecials() ^ prev_modifiers;
		prev_modifiers = orbisKeyboardGetSpecials();

		if(changed_modifiers & 0x01) {
			if (orbisKeyboardGetControlKeyLeft()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_LCTRL);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_LCTRL);
			}
		}
		if(changed_modifiers & 0x02) {
			if (orbisKeyboardGetControlKeyRight()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_RCTRL);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_RCTRL);
			}
		}
		if(changed_modifiers & 0x04) {
			if (orbisKeyboardGetShiftKeyLeft()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_LSHIFT);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_LSHIFT);
			}
		}
		if(changed_modifiers & 0x08) {
			if (orbisKeyboardGetShiftKeyRight()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_RSHIFT);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_RSHIFT);
			}
		}
		if(changed_modifiers & 0x10) {
			if (orbisKeyboardGetAltKeyLeft()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_LALT);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_LALT);
			}
		}
		if(changed_modifiers & 0x20) {
			if (orbisKeyboardGetAltKeyRight()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_RALT);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_RALT);
			}
		}
		if(changed_modifiers & 0x40) {
			if (orbisKeyboardGetCmdKeyLeft()) {	
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_LGUI);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_LGUI);
			}
		}
		if(changed_modifiers & 0x80) {
			if (orbisKeyboardGetCmdKeyRight()) {
				SDL_SendKeyboardKey(SDL_PRESSED, SDL_SCANCODE_RGUI);
			}
			else {
				SDL_SendKeyboardKey(SDL_RELEASED, SDL_SCANCODE_RGUI);
			}
		}
			
		int keyCode = orbisKeyboardGetKey();
		if (keyCode != prev_key) {
			if (prev_key) {
				SDL_SendKeyboardKey(SDL_RELEASED, prev_key);
			}
			if (keyCode) {
				SDL_SendKeyboardKey(SDL_PRESSED, keyCode);
			}
			prev_key = keyCode;
		}
	}
}

#endif /* SDL_VIDEO_DRIVER_ORBIS */

/* vi: set ts=4 sw=4 expandtab: */
