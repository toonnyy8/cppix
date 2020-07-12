#ifndef __CPPIX_STRUCT__
#define __CPPIX_STRUCT__
#include <string>
#include <vector>
namespace cppix
{
    struct RGBA
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        bool          a;
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

    struct Pixel
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct PixelLine
    {
        std::vector<struct Pixel> pxs;
    };

    struct PixelMap_
    {
        std::vector<struct PixelLine> pls;
    };

    struct PixelFrame
    {
        std::vector<struct PixelMap_> pms;
        int                           fps;
    };

    struct PixelAnimation
    {
        const int                      height;
        const int                      width;
        std::vector<struct PixelFrame> pfs;
        std::string                    pixel_str = "  ";
    };
}  // namespace cppix
#endif
