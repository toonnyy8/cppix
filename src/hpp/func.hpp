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

    std::string color(struct Pixel pixel,
                      std::string  pixel_str = "  ")
    {
        return "\x1b[48;2;" + decode_color(pixel.r) + ";" +
               decode_color(pixel.g) + ";" +
               decode_color(pixel.b) + "m" + pixel_str +
               "\x1b[0m";
    }

    unsigned char mix_alpha(unsigned char top_a,
                            unsigned char bottom_a)
    {
        return (short)top_a +
               (255 - (short)top_a) * (short)bottom_a / 255;
    }

    unsigned char mix_color(unsigned char top_c,
                            unsigned char top_a,
                            unsigned char bottom_c,
                            unsigned char bottom_a)
    {
        short c1 = (short)top_c * (short)top_a;
        short c2 = (short)bottom_c * (short)bottom_a *
                   (255 - (short)top_a);
        short out = (c1 + c2 / 255) /
                    (short)mix_alpha(top_a, bottom_a);
        return (unsigned char)out;
    }

    struct Pixel mix_pixel(struct Pixel top_pixel,
                           struct Pixel bottom_pixel)
    {
        return {mix_color(top_pixel.r, top_pixel.a,
                          bottom_pixel.r, bottom_pixel.a),
                mix_color(top_pixel.g, top_pixel.a,
                          bottom_pixel.g, bottom_pixel.a),
                mix_color(top_pixel.b, top_pixel.a,
                          bottom_pixel.b, bottom_pixel.a),
                mix_alpha(top_pixel.a, bottom_pixel.a)};
    }

    struct PixelMap new_layer(int height, int width)
    {
        struct PixelMap pm = {
            std::vector<std::vector<struct Pixel>>(
                height, std::vector<struct Pixel>(
                            width,
                            {
                                (unsigned char)0,
                                (unsigned char)0,
                                (unsigned char)0,
                                (unsigned char)0,
                            })),
            true};
        return pm;
    }

    struct PixelMap new_layer(int          height,
                              int          width,
                              struct Pixel init_pixel)
    {
        struct PixelMap pm = {
            std::vector<std::vector<struct Pixel>>(
                height, std::vector<struct Pixel>(
                            width, init_pixel)),
            true};
        return pm;
    }

    struct PixelMap frame_view(struct Frame& frame,
                               struct Pixel  bg)
    {
        if (frame.is_valid)
            return frame.view;
        else
        {
            frame.view =
                new_layer(frame.height, frame.width, bg);
            for (int y = 0; y < frame.height; y++)
            {
                for (int x = 0; x < frame.width; x++)
                {
                    for (int l = frame.layers.size() - 1;
                         l >= 0; l--)
                    {
                        if (frame.layers.at(l).is_viewable)
                            frame.view.pixels.at(y).at(x) =
                                mix_pixel(
                                    frame.layers.at(l)
                                        .pixels.at(y)
                                        .at(x),
                                    frame.view.pixels.at(y)
                                        .at(x));
                    }
                }
            }
            frame.is_valid = true;

            return frame.view;
        }
    };

    void draw_pixel_map(struct Viewport vp,
                        struct PixelMap pm,
                        std::string     pixel_str = "  ")
    {
        for (int y          = vp.offset_y,
                 fig_height = pm.pixels.size();
             y < MIN(vp.offset_y + vp.height, fig_height);
             y++)
        {
            for (int x         = vp.offset_x,
                     fig_width = pm.pixels.at(y).size();
                 x < MIN(vp.offset_x + vp.width, fig_width);
                 x++)
            {
                std::cout << color(pm.pixels.at(y).at(x),
                                   pixel_str);
            }
            std::cout << std::endl;
        }
    }

    struct Frame del_layer(struct Frame frame, int where)
    {
        frame.layers.erase(frame.layers.begin() + where);

        return frame;
    }

    struct Frame add_layer(struct Frame frame, int where)
    {
        frame.layers.insert(
            frame.layers.begin() + where,
            new_layer(frame.height, frame.width));

        return frame;
    }

    struct PixelMap copy_buffer(struct PixelMap pm,
                                int             left,
                                int             top,
                                int             right,
                                int             bottom)
    {
        int height = abs(top - bottom);
        int width  = abs(left - right);

        struct PixelMap out = new_layer(height, width);

        pm.pixels.assign(pm.pixels.begin() + top,
                         pm.pixels.begin() + bottom);

        for (int y = 0; y < height; y++)
        {
            out.pixels.at(y).assign(
                pm.pixels.at(y).begin() + left,
                pm.pixels.at(y).begin() + right);
        }

        return out;
    }

    struct PixelMap paste_buffer(struct PixelMap target_pm,
                                 struct PixelMap source_pm,
                                 int             left,
                                 int             top)
    {
        for (int y = top; y < (int)source_pm.pixels.size(); y++)
        {
            for (int x = left;
                 x < (int)source_pm.pixels.at(y).size(); x++)
            {
                target_pm.pixels.at(y).at(x) =
                    mix_pixel(source_pm.pixels.at(y).at(x),
                              target_pm.pixels.at(y).at(x));
            }
        }
        return target_pm;
    }

    struct PixelMap
    replace_buffer(struct PixelMap target_pm,
                   struct PixelMap source_pm,
                   int             left,
                   int             top)
    {
        for (int y = top; y < (int)source_pm.pixels.size(); y++)
        {
            for (int x = left;
                 x < (int)source_pm.pixels.at(y).size(); x++)
            {
                target_pm.pixels.at(y).at(x) =
                    source_pm.pixels.at(y).at(x);
            }
        }
        return target_pm;
    }

    struct Frame new_frame(int height, int width, int fps)
    {
        struct Frame frame;
        frame.height = height;
        frame.width  = width;
        frame.fps    = fps;
        frame.layers = std::vector<struct PixelMap>();

        return frame;
    }

    struct Animation
    add_frame(struct Animation anim, int fps, int where)
    {
        anim.frames.insert(
            anim.frames.begin() + where,
            new_frame(anim.height, anim.width, fps));
        return anim;
    }

    struct Animation del_frame(struct Animation anim,
                               int              where)
    {
        anim.frames.erase(anim.frames.begin() + where);
        return anim;
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

}  // namespace cppix
#endif
