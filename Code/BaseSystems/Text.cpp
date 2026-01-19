#include "../BaseSystems/Text.hpp"

void Text::Init()
{
    //Load all our fonts here:
	fonts[CINZEL] = AEGfxCreateFont("Assets/Fonts/CinzelDecorative-Regular.ttf",72);
}

void Text::Draw(Fonts font, const char* text, AEVec2 pos, float scale, Color4 color)
{
    //AEGfxGetPrint
    AEGfxPrint(font,     // font handle given by AEGfxCreateFont()
        text,            // null-terminated c-string to print
        pos.x,           // x position on normalized coordinates, ranging from -1.f to 1.f 
        pos.y,           // y position in normalized coordinates, ranging from -1.f to 1.f 
        scale,           // how much to scale the text by 
        color.r,         // percentage of red, ranging from 0.f to 1.f 
        color.g,         // percentage of green, ranging from 0.f to 1.f
        color.b,         // percentage of blue, ranging from 0.f to 1.f 
        color.a);        // percentage of alpha, ranging from 0.f to 1.f
}

void Text::Exit()
{
    //Free all the fonts loaded
    for (int i = 0; i < NUM_FONTS; i++)
    {
        AEGfxDestroyFont(fonts[i]);
    }
}

Text::Text()
{
}

Text::~Text()
{
}
