/* Copyright: (c) Kayne Ruse 2014
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source
 * distribution.
*/
#include "character_data.hpp"

void CharacterData::Update(double delta) {
	if (motion.x && motion.y) {
		origin += motion * delta * CHARACTER_WALKING_MOD;
	}
	else if (motion != 0) {
		origin += motion * delta;
	}
#ifdef GRAPHICS
	sprite.Update(delta);
#endif
}

#ifdef GRAPHICS

void CharacterData::DrawTo(SDL_Surface* const dest, int camX, int camY) {
	sprite.DrawTo(dest, origin.x - camX, origin.y - camY);
}

void CharacterData::CorrectSprite() {
	//NOTE: These must correspond to the sprite sheet in use
	if (motion.y > 0) {
		sprite.SetYIndex(0);
	}
	else if (motion.y < 0) {
		sprite.SetYIndex(1);
	}
	else if (motion.x > 0) {
		sprite.SetYIndex(3);
	}
	else if (motion.x < 0) {
		sprite.SetYIndex(2);
	}

	//animation
	if (motion != 0) {
		sprite.SetDelay(0.1);
	}
	else {
		sprite.SetDelay(0);
		sprite.SetXIndex(0);
	}
}

#endif