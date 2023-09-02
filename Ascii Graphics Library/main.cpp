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

void hideCursor() {
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CursorInfo;

  GetConsoleCursorInfo(hndl, &CursorInfo);
  CursorInfo.bVisible = false;

  SetConsoleCursorInfo(hndl, &CursorInfo);
}

void WinAPIText(COORD coord, const std::string &str) {
  static std::string laststr;

  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hndl, coord);

  std::cout << "                 ";

  SetConsoleCursorPosition(hndl, coord);
  std::cout << str;

  laststr = str;
}

void debug() {
  Coordinate2D coord = {8, 8};

  AsciiBasicChar::setTrprChr('.');

  AsciiBasicCanvas cImage("out\\scene2.dat");

  AsciiBasicLayer lImage1(cImage, {6, 6}, "image1");

  AsciiBasicLayerMngr mngr(50, 29);
  mngr.addLayer({lImage1});

  hideCursor();
  WinAPIDraw(mngr.getCanvas());

  ULONGLONG time_start;
  ULONGLONG time_end;
  int deltaTime;

  char input;

  int bestFPS = 0;
  int FPS = 0;
  int averageFPS = 0;

  unsigned long long sumFPS = 0;
  unsigned long long loopCnt = 0;

  while (1) {
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
        mngr["image1"].setCoordinate(coord);
      }

      WinAPIDraw(mngr.getCanvas());

      time_end = GetTickCount64();
      deltaTime = time_end - time_start;

      FPS = fps(deltaTime);
      bestFPS = (bestFPS < FPS) ? FPS : bestFPS;
      sumFPS += FPS;
      averageFPS = sumFPS / ((loopCnt == 0) ? 1 : loopCnt);

      /***************************************************/

      WinAPIText({100, 0}, "loopCnt:\t" + std::to_string(loopCnt));
      WinAPIText({100, 1}, "sumFPS:\t" + std::to_string(sumFPS));
      WinAPIText({100, 2}, "averageFPS:\t" + std::to_string(averageFPS));
      WinAPIText({100, 3}, "bestFPS:\t" + std::to_string(bestFPS));
      WinAPIText({100, 4}, "FPS:\t" + std::to_string(FPS));
      WinAPIText({100, 5}, "deltaTime:\t" + std::to_string(deltaTime) + "ms");

    } catch (const AsciiBasicError &error) {
      error.printError();
    }
    loopCnt++;
  }
}

int main() {
  debug();
  /* AsciiBasicChar::setTrprChr('.');
  AsciiBasicCanvas canvas(10, 10);

  setLine(canvas, {0, 0}, {2, 9}, "[]");

  canvas.show();

  getchar();*/

  return 0;
}

#endif