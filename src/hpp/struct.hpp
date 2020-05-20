#ifndef __CPPIX_STRUCT__
#define __CPPIX_STRUCT__
#include <string>
#include <vector>
namespace cppix
{
    struct RGBA
    {
        char r;
        char g;
        char b;
        bool a;
    };

    struct Viewport
    {
        const int height;
        const int width;
        int       offset_y;
        int       offset_x;
    };

    struct PixelMap
    {
        const int height;
        const int width;
        std::vector<std::vector<std::vector<struct RGBA>>>
                         figs;
        std::vector<int> fps;
        std::string      pixel_str = "  ";
    };

}  // namespace cppix
#endif
