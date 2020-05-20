#include "./hpp/func.hpp"
#include "./hpp/struct.hpp"
int main(int argc, char **argv) {
  struct cppix::Viewport vp = {cppix::key_In<int>("viewport height : ", 1),
                               cppix::key_In<int>("viewport width : ", 10), 0,
                               0};
  struct cppix::PixelMap pm = {
      cppix::key_In<int>("height : ", 10), cppix::key_In<int>("width : ", 10),
      std::vector<std::vector<std::vector<struct cppix::RGBA>>>(),
      std::vector<int>()};

  for (int f = 0; f < 10; f++) {
    pm.fps.push_back(10);
  }

  for (int t = 0, frame_num = pm.fps.size(); t < frame_num; t++) {
    pm.maps.push_back(std::vector<std::vector<struct cppix::RGBA>>());
    for (int y = 0; y < pm.height; y++) {
      pm.maps[t].push_back(std::vector<struct cppix::RGBA>());
      for (int x = 0; x < pm.width; x++) {
        pm.maps[t][y].push_back(
            {(char)(x + y), (char)(10 * x), (char)(10 * y), false});
      }
    }
  }

  cppix::play_animation(vp, pm);

  return 0;
}
