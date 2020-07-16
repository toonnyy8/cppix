#include "./hpp/func.hpp"
#include "./hpp/struct.hpp"
#include "./lua/lua.hpp"
#include "./sol/sol.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include <ctime>
#include <random> /* 亂數函式庫 */

int main(int argc, char** argv)
{
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
    struct cppix::Pixel bg = {
        (unsigned char)0,
        (unsigned char)0,
        (unsigned char)0,
        (unsigned char)255,
    };

    for (int t = 0, frame_num = 10; t < frame_num; t++)
    {
        anim = cppix::add_frame(anim, 10, t);
    }

    for (int t = 0, frame_num = anim.frames.size();
         t < frame_num; t++)
    {
        anim.frames.at(t) =
            cppix::add_layer(anim.frames.at(t), 0);
    }

    anim.frames.at(0) =
        cppix::del_layer(anim.frames.at(0), 0);
    anim.frames.at(0) =
        cppix::add_layer(anim.frames.at(0), 0);

    for (int t = 0, frame_num = anim.frames.size();
         t < frame_num; t++)
    {
        std::cout << "\033[0;0H";
        std::cout << "\033[2J";
        cppix::draw_pixel_map(
            vp, cppix::frame_view(anim.frames[t], bg),
            anim.pixel_str);
        std::this_thread::sleep_for(
            std::chrono::duration<int, std::micro>(
                1000000 / anim.frames[t].fps));
    }
    std::cout << "\033[0;0H";
    std::cout << "\033[2J";

    return 0;
}
