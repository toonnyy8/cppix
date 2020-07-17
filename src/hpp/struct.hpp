#ifndef __CPPIX_STRUCT__
#define __CPPIX_STRUCT__
#include <string>
#include <vector>
namespace cppix
{
    struct Viewport
    {
        const int height;
        const int width;
        int       offset_y;
        int       offset_x;
    };

    struct Pixel
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct PixelMap
    {
        std::vector<std::vector<struct Pixel>> pixels;
        bool                                   is_viewable;
    };

    struct Frame
    {
        int                          height;
        int                          width;
        std::vector<struct PixelMap> layers;
        int                          fps;

        friend struct PixelMap
        frame_view(struct Frame& frame, struct Pixel bg);

      private:
        struct PixelMap view;
        bool            is_valid;
    };

    struct Animation
    {
        int                       height;
        int                       width;
        std::vector<struct Frame> frames;
        std::string               pixel_str = "  ";
    };
}  // namespace cppix
#endif
