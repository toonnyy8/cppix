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

    struct RGBA
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };

    struct Pixel
    {
        struct RGBA rgba;
        bool        is_viewable;
    };

    class PixelFeature
    {
      public:
        PixelFeature(std::vector<struct Pixel> pixels)
            : pxs(pixels){};
        std::vector<struct Pixel> pxs;
        friend struct RGBA
             pixel_feature_view(PixelFeature& pf, RGBA bg);
        void update()
        {
            is_valid = false;
        };

      private:
        bool        is_valid = true;
        struct RGBA view     = {
            (unsigned char)255,
            (unsigned char)255,
            (unsigned char)255,
            (unsigned char)255,
        };
    };

    struct PixelLine
    {
        std::vector<PixelFeature> pfs;
    };

    struct PixelMap
    {
        int                           feature_num;
        std::vector<struct PixelLine> pls;
    };

    struct Frame
    {
        struct PixelMap pm;
        int             fps;
    };

    struct Animation
    {
        const int                 height;
        const int                 width;
        std::vector<struct Frame> frames;
        std::string               pixel_str = "  ";
    };
}  // namespace cppix
#endif
