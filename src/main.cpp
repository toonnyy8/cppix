// #include "../lua/install/include/lua.hpp"
#include "./hpp/func.hpp"
#include "./hpp/struct.hpp"
#include <string>
#include <thread>
#include <vector>

#include <ctime>
#include <random> /* 亂數函式庫 */

// lua_State* L;

int main(int argc, char** argv)
{
    // L = luaL_newstate();

    /* 亂數產生器 */
    std::default_random_engine generator(time(NULL));

    /* 亂數的機率分布 */
    std::uniform_int_distribution<short> unif(0, 255);

    struct cppix::Viewport vp = {
        cppix::key_In<int>("viewport height : ", 3),
        cppix::key_In<int>("viewport width : ", 10), 0, 0};

    struct cppix::Animation anim = {
        cppix::key_In<int>("height : ", 10),
        cppix::key_In<int>("width : ", 10),
        std::vector<struct cppix::Frame>(),
        cppix::key_In<std::string>("pixel string : ",
                                   "  ")};
    struct cppix::RGBA bg = {
        (unsigned char)100,
        (unsigned char)0,
        (unsigned char)0,
        (unsigned char)255,
    };
    for (int t = 0; t < 10; t++)
    {
        anim.frames.push_back(
            {{0, std::vector<struct cppix::PixelLine>()},
             10});
    }
    for (int t = 0, frame_num = anim.frames.size();
         t < frame_num; t++)
    {
        anim.frames[t].pm.feature_num = 1;
        for (int y = 0; y < anim.height; y++)
        {
            anim.frames[t].pm.pls.push_back(
                {std::vector<cppix::PixelFeature>()});
            for (int x = 0; x < anim.width; x++)
            {
                anim.frames[t].pm.pls[y].pfs.push_back(
                    {std::vector<struct cppix::Pixel>()});

                for (int f = 0;
                     f < anim.frames[t].pm.feature_num; f++)
                {
                    anim.frames[t]
                        .pm.pls[y]
                        .pfs[x]
                        .pxs.push_back(
                            {{
                                 (unsigned char)unif(
                                     generator),
                                 (unsigned char)unif(
                                     generator),
                                 (unsigned char)unif(
                                     generator),
                                 (unsigned char)unif(
                                     generator),
                             },
                             true});
                }

                anim.frames[t].pm.pls[y].pfs[x].update();
                cppix::pixel_feature_view(
                    anim.frames[t].pm.pls[y].pfs[x], bg);
            }
        }
    }

    for (int t = 0, frame_num = anim.frames.size();
         t < frame_num; t++)
    {
        std::cout << "\033[0;0H";
        std::cout << "\033[2J";
        cppix::draw_pixel_map(vp, anim.frames[t].pm, bg,
                              anim.pixel_str);
        std::this_thread::sleep_for(
            std::chrono::duration<int, std::micro>(
                1000000 / anim.frames[t].fps));
    }
    std::cout << "\033[0;0H";
    std::cout << "\033[2J";

    return 0;
}
