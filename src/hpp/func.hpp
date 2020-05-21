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
