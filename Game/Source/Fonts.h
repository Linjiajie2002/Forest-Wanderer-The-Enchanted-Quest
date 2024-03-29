#pragma once
#ifndef __FONTS_H__
#define __FONTS_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"
#include "App.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

struct SDL_Texture;

struct Font
{
	// Lookup table. All characters displayed in the same order as the texture
	char table[MAX_FONT_CHARS];

	// The font texture
	SDL_Texture* texture = nullptr;

	// Font setup data
	uint totalLength;
	uint rows, columns;
	uint char_w, char_h;
};


class Fonts : public Module
{
public:

	// Constructor
	Fonts();

	// Destructor
	~Fonts();

	// Loads a font file from a texture
	// Returns a font index from the fonts array
	// Param texturePath	- The path to the texture file
	// Param characters		- The lookup table. All characters displayed in the same order as the texture
	// Param rows			- The amount of character rows in the texture
	int Load(const char* texturePath, const char* characters, uint rows = 1);

	// Removes a font by its index
	// Unloads the texture and removes it from the fonts array
	void UnLoad(int fontIndex);

	// Create a surface from text
	void BlitText(int x, int y, int fontIndex, const char* text) const;

private:
	// An array to keep track and store all loaded fonts
	Font fonts[MAX_FONTS];
public:
	int total_time = 180;
};


#endif // __ModuleFonts_H__