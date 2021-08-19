#include "Lightning.hpp"

std::vector<int> Lightning::getLightColour( float lum )
{
    std::vector<int> fg_col;
    fg_col.reserve( 3 );
    int pixCol = (int)(255.0f * lum);
    if (pixCol < 0)
        pixCol = 0;
    if (pixCol > 255 )
        pixCol = 255;

    for(int i = 0; i< 3; i++)
        fg_col[i] = pixCol;

    return fg_col;
}
