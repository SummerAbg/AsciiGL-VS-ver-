// Ascii Graphics Library(AsciiGL)
//  项目始于2023-08-11
//  作者:  0xZed_

#define DEBUG
#ifndef DEBUG

#include "AsciiBasicGraphics.h"

const std::string AsciiGLVersion = "0.0.1";

void version() {
  std::cout << "Ascii Graphics Library(AsciiGL)\n"
            << "字符串图形库(AsciiGL)" << std::endl;
  std::cout << "版本:\t" << AsciiGLVersion << std::endl;
  std::cout << "作者:\t0xZed_" << std::endl;
}

void help() {
  std::cout << "用法:" << std::endl;
  std::cout << "\tmain [选项] fileName" << std::endl;
  std::cout << "选项:" << std::endl;
  std::cout << "\t--help\t\t显示帮助" << std::endl;
  std::cout << "\t--version\t显示版本" << std::endl;
}

void show(const std::string &path) {
  try {
    const AsciiBasicCanvas canvas(path);
    canvas.show();
  } catch (const AsciiBasicError &error) {
    error.printError();
  }
}

int main(int argc, char **argv) {
  if (argc == 1) {
    debug();
    return 0;
  } else if (argc != 2) {
    std::cout << "命令语法错误!" << std::endl;
    help();
    return 0;
  }

  const std::string option = argv[1];
  if (option == "--help") {
    help();
  } else if (option == "--version") {
    version();
  } else {
    show(option);
  }

  return 0;
}

#else

#include "AsciiBasicGraphics.h"
#include "DebugLibrary.h"
#include <conio.h>

int fps(int deltaTime) // ms
{
  static float avgDuration = 0.f;
  static float alpha = 1.f / 100.f; // 采样数设置为100
  static int frameCount = 0;

  ++frameCount;

  int fps = 0;
  if (1 == frameCount) {
    avgDuration = static_cast<float>(deltaTime);
  } else {
    avgDuration = avgDuration * (1 - alpha) + deltaTime * alpha;
  }

  fps = static_cast<int>(1.f / avgDuration * 1000);
  return fps;
}

void debug() {
  const int length = 59;
  const int width = 29;
  Coordinate2D coord = {8, 8};

  AsciiBasicLayerMngr mngr(length, width);

  AsciiBasicLayer bgb(AsciiBasicCanvas("out\\canvas3.dat"), {0, 0}, "背景框");
  AsciiBasicLayer girl1({1, 1, "荆"}, {length / 2, width / 2}, "成濑荆");
  AsciiBasicLayer girl2({1, 1, "葵"}, {8, 6}, "深作葵");
  AsciiBasicLayer girl3({1, 1, "妙"}, {4, 5}, "野村妙子");
  AsciiBasicLayer me({1, 1, "我"}, coord, "0xZed_");
  AsciiBasicLayer layer_info({10, 15, "  "}, coord, "layer_info");
  AsciiBasicLayer game_info({10, 10, "  "}, {10, 10}, "game_info");

  mngr.addLayer({bgb, layer_info, game_info, girl1, girl2, girl3, me});

  ULONGLONG time_start;
  ULONGLONG time_end;
  int deltaTime;

  char input;

  int bestFPS = 0;
  int FPS = 0;
  int averageFPS = 0;

  size_t sumFPS = 0;
  size_t loopCnt = 0;

  hideCursor();

  while (1) {
    EfficiencyDebug efd;
    try {
      time_start = GetTickCount64();

      if (_kbhit()) {
        input = _getch();

        switch (input) {
        case 'w':
          coord.y--;
          break;
        case 's':
          coord.y++;
          break;
        case 'a':
          coord.x--;
          break;
        case 'd':
          coord.x++;
          break;
        }
        mngr["layer_info"].setCoordinate(coord);
      }

      /* for (int i = 0; i < mngr.size(); i++) {
        setText(mngr["layer_info"], {1, mngr.size() - i - 1},
                std::to_string(i + 1) + "." + mngr[i].getName());
      }*/

      setText(mngr["layer_info"], {0, 9}, std::to_string(FPS));

      WinAPIDraw(mngr.getCanvas());

      /***************************************************/

      mngr["game_info"].clear(false);
      mngr["layer_info"].clear(false);

      auto &canvas = mngr["game_info"];

      setText(canvas, {1, 2}, "averageFPS:" + std::to_string(averageFPS));
      setText(canvas, {1, 3}, "bestFPS:" + std::to_string(bestFPS));
      setText(canvas, {1, 4}, "FPS:" + std::to_string(FPS));
      // setText(canvas, {1, 6}, "changeCount:" + std::to_string(changeCount));

      /***************************************************/

      mngr.deleteLayer("line1");

      AsciiBasicLayer line1({length, width}, {0, 0}, "line1");
      setLine(line1, mngr["成濑荆"].getCoordinate(),
              mngr["layer_info"].getCoordinate(), "[]", 0);
      mngr.insertLayer(2, line1);

      /***************************************************/

      setBorder(mngr["layer_info"], "<>");
      setBorder(mngr["game_info"], "()");

      /***************************************************/

      time_end = GetTickCount64();
      deltaTime = static_cast<int>(time_end - time_start);

      FPS = fps(deltaTime);
      bestFPS = (bestFPS < FPS) ? FPS : bestFPS;
      sumFPS += FPS;
      averageFPS = static_cast<int>(sumFPS / ((loopCnt == 0) ? 1 : loopCnt));

    } catch (const AsciiBasicError &error) {
      error.printError();
    }
    loopCnt++;
  }
}

void WinRGBInit() {                              // 初始化
  HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);   // 输入句柄
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // 输出句柄
  DWORD dwInMode, dwOutMode;
  GetConsoleMode(hIn, &dwInMode);   // 获取控制台输入模式
  GetConsoleMode(hOut, &dwOutMode); // 获取控制台输出模式
  dwInMode |= 0x0200;               // 更改
  dwOutMode |= 0x0004;
  SetConsoleMode(hIn, dwInMode);   // 设置控制台输入模式
  SetConsoleMode(hOut, dwOutMode); // 设置控制台输出模式
}

void AsciiGLInit() {
  AsciiBasicChar::setTrprChr('/');
  AsciiBasicChar::setDefaultColor(ASCII_WORD_COLOR_WHITE);
}

void statement() {
  AsciiBasicString str = {"AsciiGL(Ascii Graphics Library) v1.0.0\nBuilt by "
                          "0xZed_\n老子是AsciiGL之父!嘿嘿嘿嘿hihihihihihihi*n~"
                          "\n私の名は「0xZed_」、年齢15歳。自宅は杜王町北東部"
                          "の別荘地帯にあり。結婚はしていない。",
                          false, ASCII_WORD_COLOR_CYAN_GREEN};
  std::cout << str << std::endl;
}

void test() {
  AsciiBasicLayerMngr mngr(10, 10);
  

  AsciiBasicCanvas canvas1(6, 6);
  setBorder(canvas1, "#");

  AsciiBasicCanvas canvas2(6, 6);
  setBorder(canvas2, {"*", false, ASCII_WORD_COLOR_GREEN});


  AsciiBasicLayer layer1(canvas1, {1, 1}, "layer1");
  layer1.setCenterPoint({3, 3});

  AsciiBasicLayer layer2(canvas2, {1, 1}, "layer2");
  layer2.setCenterPoint({0, 0});


  mngr.addLayer({layer1, layer2});

  setText(mngr, {2, 2}, "Hello world!");

  mngr.getCanvas().show();

  for (const auto &index : mngr) {
    std::cout << index.getName() << std::endl;
  }

  getchar();
}

#include <filesystem>

int main() {
  WinRGBInit();
  AsciiGLInit();
  statement();

  std::string input;

  test();

  try {
    // debug();
    while (1) {
      std::cout << "请输入要访问的文件夹路径: ";
      std::getline(std::cin, input);

      for (auto &index : std::filesystem::directory_iterator(input)) {
        const std::string filePath = index.path().string();
        AsciiBasicCanvas canvas(filePath);

        std::cout << "Loading " << filePath << std::endl;
        {
          EfficiencyDebug efd;
          canvas.show();
        }
      }
      std::cout << "请输入任意键继续 ... " << std::endl;
      getchar();
    }
  } catch (const AsciiBasicError &error) {
    error.printError();
  }

  getchar();

  return 0;
}

#endif