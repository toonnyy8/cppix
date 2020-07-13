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

    std::string color(struct RGBA rgba,
                      std::string pixel_str = "  ")
    {
        return "\x1b[48;2;" + decode_color(rgba.r) + ";" +
               decode_color(rgba.g) + ";" +
               decode_color(rgba.b) + "m" + pixel_str +
               "\x1b[0m";
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

    struct RGBA pixel_feature_view(PixelFeature& pf,
                                   struct RGBA   bg)
    {
        if (pf.is_valid)
            return pf.view;
        else
        {
            struct RGBA bg_ = {bg.r, bg.g, bg.b, bg.a};
            pf.is_valid     = true;
            for (std::vector<struct Pixel>::iterator it =
                     pf.pxs.begin();
                 it != pf.pxs.end(); it++)
            {
                auto n = *it;
                if (n.is_viewable)
                {
                    bg_ = {mix_color(n.rgba.r, n.rgba.a,
                                     bg_.r),
                           mix_color(n.rgba.g, n.rgba.a,
                                     bg_.g),
                           mix_color(n.rgba.b, n.rgba.a,
                                     bg_.b),
                           false};
                }
            }
            pf.view = bg_;
            return pf.view;
        }
    };

    void draw_pixel_map(struct Viewport vp,
                        struct PixelMap pm,
                        struct RGBA     bg,
                        std::string     pixel_str = "  ")
    {
        for (int y          = vp.offset_y,
                 fig_height = pm.pls.size();
             y < MIN(vp.offset_y + vp.height, fig_height);
             y++)
        {
            for (int x         = vp.offset_x,
                     fig_width = pm.pls[y].pfs.size();
                 x < MIN(vp.offset_x + vp.width, fig_width);
                 x++)
            {
                std::cout
                    << color(pixel_feature_view(
                                 pm.pls[y].pfs[x], bg),
                             pixel_str);
            }
            std::cout << std::endl;
        }
    }

    struct PixelMap del_pixel_feature(struct PixelMap pm,
                                      int             where)
    {
        for (int y = 0; y < pm.pls.size(); y++)
        {
            for (int x = 0; x < pm.pls[y].pfs.size(); x++)
            {
                pm.pls[y].pfs[x].pxs.erase(
                    pm.pls[y].pfs[x].pxs.begin() + where);
                pm.pls[y].pfs[x].update();
            }
        }
        pm.feature_num -= 1;

        return pm;
    }

    struct PixelMap add_pixel_feature(struct PixelMap pm,
                                      int             where)
    {
        for (int y = 0; y < pm.pls.size(); y++)
        {
            for (int x = 0; x < pm.pls[y].pfs.size(); x++)
            {
                pm.pls[y].pfs[x].pxs.insert(
                    pm.pls[y].pfs[x].pxs.begin() + where,
                    {{
                         (unsigned char)0,
                         (unsigned char)0,
                         (unsigned char)0,
                         (unsigned char)0,
                     },
                     true});
                pm.pls[y].pfs[x].update();
            }
        }
        pm.feature_num += 1;

        return pm;
    }
    struct PixelMap
    copy_pixel_feature(struct PixelMap target_pm,
                       int             target,
                       struct PixelMap source_pm,
                       int             source)
    {
        for (int y = 0; y < target_pm.pls.size(); y++)
        {
            for (int x = 0; x < target_pm.pls[y].pfs.size();
                 x++)
            {
                target_pm.pls[y].pfs[x].pxs[target] =
                    source_pm.pls[y].pfs[x].pxs[source];
                target_pm.pls[y].pfs[x].update();
            }
        }

        return target_pm;
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
