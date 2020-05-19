#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct RGBA
{
  char r;
  char g;
  char b;
  bool a;
};
struct Viewport
{
  const int height;
  const int width;
  int offset_y;
  int offset_x;
};
struct PixelMap
{
  const int height;
  const int width;
  std::vector<std::vector<std::vector<struct RGBA>>>
      maps;
  std::vector<int> fps;
};
std::string decode_color(char color_code)
{
  std::string color_str;
  color_str = "";
  int cc;
  cc = (int)color_code;

  color_str = (char)(cc % 10 + 48);
  cc /= 10;
  color_str = (char)(cc % 10 + 48) + color_str;
  cc /= 10;
  color_str = (char)(cc % 10 + 48) + color_str;

  return color_str;
}
std::string color(struct RGBA rgba, std::string pixel_str = "  ")
{
  if (!rgba.a)
    return "\x1b[48;2;" + decode_color(rgba.r) + ";" + decode_color(rgba.g) + ";" +
           decode_color(rgba.b) + "m" + pixel_str + "\x1b[0m";
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

void draw_map(
    struct Viewport vp,
    struct PixelMap pm,
    int frame)
{
  for (int y = vp.offset_y; y < MIN(vp.offset_y + vp.height, pm.height); y++)
  {
    for (int x = vp.offset_x; x < MIN(vp.offset_x + vp.width, pm.width); x++)
    {
      std::cout << color(pm.maps[frame][y][x]);
    }
    std::cout << std::endl;
  }
}

void play_animation(
    struct Viewport vp,
    struct PixelMap pm)
{
  for (int t = 0, frame_num = pm.fps.size(); t < frame_num; t++)
  {
    draw_map(vp, pm, t);
    std::this_thread::sleep_for(
        std::chrono::duration<int, std::milli>(1000 / pm.fps[t]));
    std::cout << "\033[0;0H";
    std::cout << "\033[2J";
  }
}

int main(int argc, char **argv)
{
  struct Viewport vp = {
      key_In<int>("viewport height : ", 1),
      key_In<int>("viewport width : ", 10),
      0,
      0};
  struct PixelMap pm = {
      key_In<int>("height : ", 10),
      key_In<int>("width : ", 10),
      std::vector<std::vector<std::vector<struct RGBA>>>(),
      std::vector<int>()};

  for (int f = 0; f < 10; f++)
  {
    pm.fps.push_back(10);
  }

  for (int t = 0, frame_num = pm.fps.size(); t < frame_num; t++)
  {
    pm.maps.push_back(std::vector<std::vector<struct RGBA>>());
    for (int y = 0; y < pm.height; y++)
    {
      pm.maps[t].push_back(std::vector<struct RGBA>());
      for (int x = 0; x < pm.width; x++)
      {
        pm.maps[t][y].push_back(
            {(char)(x + y), (char)(10 * x), (char)(10 * y), false});
      }
    }
  }

  play_animation(vp, pm);

  return 0;
}
