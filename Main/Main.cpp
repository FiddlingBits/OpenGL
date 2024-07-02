/****************************************************************************************************
 * Define
 ****************************************************************************************************/

#define STB_IMAGE_IMPLEMENTATION

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Demonstration/Basic/Basic.h"
#include "Demonstration/Texture/Texture.h"
#include "Demonstration/Transformation/Transformation.h"
#include "Library/stb/stb_image.h" // Must Be Included Only Once With STB_IMAGE_IMPLEMENTATION Defined
#include <format>
#include <iostream>
#include <string>

/****************************************************************************************************
 * Function Definition
 ****************************************************************************************************/

int main(int argc, char* argv[])
{
    /*** Run ***/
    if((argc == 2) && (strcmp(argv[1], "basic") == 0))
    {
        Basic basic;
        basic.Run("Basic", 512, 512);
    }
    else if((argc == 2) && (strcmp(argv[1], "texture") == 0))
    {
        Texture texture;
        texture.Run("Texture", 512, 512);
    }
    else if((argc == 2) && (strcmp(argv[1], "transformation") == 0))
    {
        Transformation transformation;
        transformation.Run("Transformation", 512, 512);
    }
    else
    {
        std::cout << std::format("usage: {} [OPTION]\n", argv[0]);
        std::cout << std::format("  basic\n");
        std::cout << std::format("  texture\n");
        std::cout << std::format("  transformation\n");
    }
}
