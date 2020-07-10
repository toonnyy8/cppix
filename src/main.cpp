#include "../lua/include/lua.hpp"
#include "./hpp/func.hpp"
#include "./hpp/struct.hpp"
#include <string>
#include <thread>
#include <vector>
lua_State* L;

int main(int argc, char** argv)
{
    L                         = luaL_newstate();
    struct cppix::Viewport vp = {
        cppix::key_In<int>("viewport height : ", 3),
        cppix::key_In<int>("viewport width : ", 10), 0, 0};

    struct cppix::PixelMap pm = {
        cppix::key_In<int>("height : ", 10),
        cppix::key_In<int>("width : ", 10),
        std::vector<
            std::vector<std::vector<struct cppix::RGBA>>>(),
        std::vector<int>(),
        cppix::key_In<std::string>("pixel string : ",
                                   "  ")};
    for (int f = 0; f < 10; f++)
    {
        pm.fps.push_back(10);
    }

    for (int t = 0, frame_num = pm.fps.size();
         t < frame_num; t++)
    {
        pm.figs.push_back(
            std::vector<std::vector<struct cppix::RGBA>>());
        for (int y = 0; y < pm.height; y++)
        {
            pm.figs[t].push_back(
                std::vector<struct cppix::RGBA>());
            for (int x = 0; x < pm.width; x++)
            {
                pm.figs[t][y].push_back(
                    {(unsigned char)(20 * t),
                     (unsigned char)(10 * x),
                     (unsigned char)(10 * y), false});
            }
        }
    }

    for (int f = 0, frame_num = pm.fps.size();
         f < frame_num; f++)
    {
        cppix::draw_fig(vp, pm.figs[f], pm.pixel_str);
        std::this_thread::sleep_for(
            std::chrono::duration<int, std::micro>(
                1000000 / pm.fps[f]));
        std::cout << "\033[0;0H";
        std::cout << "\033[2J";
    }

    return 0;
}
