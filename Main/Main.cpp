/****************************************************************************************************
 * Define
 ****************************************************************************************************/

#define STB_IMAGE_IMPLEMENTATION

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "Demonstration/Basic/Basic.h"
#include "Demonstration/Depth/Depth.h"
#include "Demonstration/Lighting/Basic/LightingBasic.h"
#include "Demonstration/Lighting/Map/LightingMap.h"
#include "Demonstration/Lighting/Material/LightingMaterial.h"
#include "Demonstration/Texture/Texture.h"
#include "Demonstration/Transform/Transform.h"
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
        Basic basic {};
        basic.Run("Basic", 512, 512);
    }
    else if((argc == 2) && (strcmp(argv[1], "depth") == 0))
    {
        Depth depth {};
        depth.Run("Depth", 512, 512);
    }
    else if((argc == 3) && (strcmp(argv[1], "lighting") == 0) && (strcmp(argv[2], "basic") == 0))
    {
        LightingBasic lightingBasic {};
        lightingBasic.Run("Lighting (Basic)", 512, 512);
    }
    else if((argc == 3) && (strcmp(argv[1], "lighting") == 0) && (strcmp(argv[2], "map") == 0))
    {
        LightingMap lightingMap {};
        lightingMap.Run("Lighting (Map)", 512, 512);
    }
    else if((argc == 3) && (strcmp(argv[1], "lighting") == 0) && (strcmp(argv[2], "material") == 0))
    {
        LightingMaterial lightingMaterial {};
        lightingMaterial.Run("Lighting (Material)", 512, 512);
    }
    else if((argc == 2) && (strcmp(argv[1], "texture") == 0))
    {
        Texture texture {};
        texture.Run("Texture", 512, 512);
    }
    else if((argc == 2) && (strcmp(argv[1], "transform") == 0))
    {
        Transform transform {};
        transform.Run("Transform", 512, 512);
    }
    else
    {
        std::cout << std::format("usage: {} [OPTION]\n", argv[0]);
        std::cout << std::format("  basic\n");
        std::cout << std::format("  depth\n");
        std::cout << std::format("  lighting\n");
        std::cout << std::format("    basic\n");
        std::cout << std::format("    map\n");
        std::cout << std::format("    material\n");
        std::cout << std::format("  texture\n");
        std::cout << std::format("  transform\n");
    }
}
