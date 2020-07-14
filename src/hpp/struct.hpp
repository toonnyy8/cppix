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
        struct Pixel& operator=(const Pixel& pixel)
        {
            r = pixel.r;
            g = pixel.g;
            b = pixel.b;
            a = pixel.a;
            return *this;
        };
    };

    struct PixelMap
    {
        std::vector<std::vector<struct Pixel>> pixels;
        bool                                   is_viewable;
        struct PixelMap& operator=(const PixelMap& pm)
        {
            pixels      = pm.pixels;
            is_viewable = pm.is_viewable;
            return *this;
        };
    };

    struct Frame
    {
        int                          height;
        int                          width;
        std::vector<struct PixelMap> layers;
        int                          fps;
        struct Frame& operator=(const Frame& frame)
        {
            height = frame.height;
            width  = frame.width;
            layers = frame.layers;
            fps    = frame.fps;
            return *this;
        };

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
