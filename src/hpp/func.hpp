#ifndef __CPPIX_FUNC__
#define __CPPIX_FUNC__
#include "./struct.hpp"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
namespace cppix
{
    std::string decode_color(unsigned char color_code)
    {
        std::string color_str;
        color_str = "";
        short cc;
        cc = (short)color_code;

        color_str = (char)(cc % 10 + 48);
        cc /= 10;
        color_str = (char)(cc % 10 + 48) + color_str;
        cc /= 10;
        color_str = (char)(cc % 10 + 48) + color_str;

        return color_str;
    }

    std::string decode_color(short color_code)
    {
        std::string color_str;
        color_str = "";

        color_str = (char)(color_code % 10 + 48);
        color_code /= 10;
        color_str =
            (char)(color_code % 10 + 48) + color_str;
        color_code /= 10;
        color_str =
            (char)(color_code % 10 + 48) + color_str;

        return color_str;
    }

    std::string color(struct cppix::RGBA rgba,
                      std::string        pixel_str = "  ")
    {
        if (!rgba.a)
            return "\x1b[48;2;" + decode_color(rgba.r) +
                   ";" + decode_color(rgba.g) + ";" +
                   decode_color(rgba.b) + "m" + pixel_str +
                   "\x1b[0m";
        else
            return pixel_str;
    }

    unsigned char mix_color(unsigned char  c1,
                            unsigned short a,
                            unsigned short c2)
    {
        return (
            unsigned char)(((short)c1 * (short)a +
                            (short)c2 * (255 - (short)a)) /
                           255);
    }

    short mix_color(short c1, short a, short c2)
    {
        return (c1 * a + c2 * (255 - a)) / 255;
    }

    std::string color(struct cppix::Pixel pixel,
                      struct cppix::Pixel bg,
                      std::string         pixel_str = "  ")
    {
        return "\x1b[48;2;" +
               decode_color(mix_color((short)pixel.r,
                                      (short)pixel.a,
                                      (short)bg.r)) +
               ";" +
               decode_color(mix_color((short)pixel.g,
                                      (short)pixel.a,
                                      (short)bg.g)) +
               ";" +
               decode_color(mix_color((short)pixel.b,
                                      (short)pixel.a,
                                      (short)bg.b)) +
               "m" + pixel_str + "\x1b[0m";
    }

    template <typename T>
    T key_In(void)
    {
        T value;
        std::cin >> value;
        return value;
    }

    template <typename T>
    T key_In(std::string message)
    {
        std::cout << message;
        T value;
        std::cin >> value;
        return value;
    }

    template <typename T>
    T key_In(std::string message, T value)
    {
        std::cout << message << value << std::endl;
        return value;
    }

    void draw_fig(struct cppix::Viewport                vp,
                  std::vector<std::vector<struct RGBA>> fig,
                  std::string pixel_str = "  ")
    {
        for (int y = vp.offset_y, fig_height = fig.size();
             y < MIN(vp.offset_y + vp.height, fig_height);
             y++)
        {
            for (int x         = vp.offset_x,
                     fig_width = fig[y].size();
                 x < MIN(vp.offset_x + vp.width, fig_width);
                 x++)
            {
                std::cout << color(fig[y][x], pixel_str);
            }
            std::cout << std::endl;
        }
    }

}  // namespace cppix
#endif
