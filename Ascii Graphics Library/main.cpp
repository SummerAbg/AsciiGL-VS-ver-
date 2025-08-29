// Ascii Graphics Library(AsciiGL)
//  项目始于2023-08-11
//  作者:  0xZed_
/*#include "graphics.h"

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
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
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
*/
#include "at_basicmanager.h"
#include "at_thread.h"
#include "graphics.h"
#include <atomic>
#include <conio.h>

#ifdef _DEBUG
#include "vld.h"
#endif // DEBUG

using namespace AsciiGL;

size_t fps(double deltaTime) {
  return deltaTime != 0.0 ? static_cast<size_t>(1.0 / deltaTime) : 0;
}

void debug() {
  const int length = 59;
  const int width = 29;
  Coord2d coord(17, 3);

  AsciiBasicLayerMngr mngr(length, width, "  ");

  // AsciiBasicLayer bgb(AsciiBasicCanvas("new_out\\canvas3.asc2"), Vec2d(0, 0),
  //                    "背景框");
  AsciiBasicLayer bgb(AsciiBasicCanvas("火焰猫磷.asc2"), Vec2d(0, 0), "背景框");

  // AsciiBasicCanvas bgb_canvas(length, width,
  //                             {"  ", {ASCII_COLOR_GREY, {221, 221, 223}}});
  //  setBorder(bgb_canvas, {"  ", CYAN_BLACK});
  // AsciiBasicLayer bgb(bgb_canvas, Vec2d(0, 0), "背景框");
  AsciiBasicLayer girl1({{"荆", FG_INDIGO}}, Vec2d(length / 2, width / 2),
                        "成濑荆");
  AsciiBasicLayer girl2({{"葵", FG_INDIGO}}, Vec2d(8, 6), "深作葵");
  AsciiBasicLayer girl3({{"妙", FG_INDIGO}}, Vec2d(4, 5), "野村妙子");
  // AsciiBasicLayer me({1, 1, {"吾", BG_RED}}, coord, "0xZed_");
  AsciiBasicLayer me(AsciiBasicCanvas("youmu.asc2"), coord, "0xZed_");
  mngr.append({bgb, me, girl1, girl2, girl3});

  // AsciiBasicLayerMngr mngr;
  // deserializeType(mngr, getFileData("mngr.dat"));

  std::atomic<double> deltaTime = 0.0;

  char input;

  size_t bestFPS = 0;
  size_t FPS = 0;
  size_t averageFPS = 0;

  size_t sumFPS = 0;
  size_t loopCnt = 0;

  hideCursor();

  ThreadDetector thread_detector;
  std::shared_mutex s_mtx;

  auto threadControl = [&]() {
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
      mngr["0xZed_"].setCoordinate(coord);
    }
  };

  auto threadDisplayData = [&]() {
    std::string layers_information;
    std::string threads_information;

    for (const auto &index : mngr) {
      layers_information += index->getLabel() +=
          "\t" + index->getCoordinate().toString() += "\n";
    }

    for (const auto &index : *thread_detector.getWorks()) {
      threads_information += index.label + "\t" +=
          std::to_string(fps(index.delta_t)) + "-" += "\n";
    }

    std::shared_lock<std::shared_mutex> lock(s_mtx);

    winApiText({0, 0}, "threads_information:\n" + threads_information);
    // winApiText({50, 2}, "averageFPS:" + std::to_string(averageFPS));
    // winApiText({50, 3}, "bestFPS:" + std::to_string(bestFPS));
    // winApiText({50, 4}, "FPS:" + std::to_string(FPS));
    winApiText({0, 8}, "layers_information:\n" + layers_information);
  };

  auto threadUpdateData = [&]() {
    // deltaTime = thread_detector.getTasks();
    FPS = fps(deltaTime);
    bestFPS = (bestFPS < FPS) ? FPS : bestFPS;
    sumFPS += FPS;
    averageFPS = static_cast<size_t>(sumFPS / ((loopCnt == 0) ? 1 : loopCnt));
  };

  /* while (1) {
     TimeMeasurer time_measurer(&deltaTime);
    try {
      threadControl();
      winApiDraw(mngr);

      // setText(canvas, {1, 6}, "changeCount:" + std::to_string(changeCount));
      threadDisplayData();

      // mngr.remove("line1");

      // AsciiBasicLayer line1({length, width}, Vec2d(0, 0), "line1");
      // setLine(line1, mngr["成濑荆"].getCoordinate(),
      //         mngr["layer_info"].getCoordinate(), "[]", 0);
      // mngr.insert(2, line1);

      // setBorder(mngr["layer_info"], "<>");
      // setBorder(mngr["game_info"], "()");

      threadUpdateData();
    }
    catch (const AsciiBasicException &e) {
      std::cout << e.what() << std::endl;
    }*/
  thread_detector.append("控制线程", threadControl, 60);
  thread_detector.append(
      "渲染线程",
      [&]() {
        std::unique_lock<std::shared_mutex> lock(s_mtx);
        winApiDraw(mngr);
        loopCnt++;
      },
      0);
  thread_detector.append("调试线程", threadDisplayData, 60);
  //  thread_detector.append("更新线程", threadUpdateData, 120);

  thread_detector.execute();
  thread_detector.join();
}

void statement() {
  AsciiBasicString str = {"AsciiGL(Ascii Graphics Library) v1.0.0\nBuilt by "
                          "0xZed_\n老子是AsciiGL之父!嘿嘿嘿嘿hihihihihihihi*n~"
                          "\n私の名は「0xZed_」、年齢15歳。自宅は杜王町北東部"
                          "の別荘地帯にあり。結婚はしていない。",
                          false,
                          {ASCII_COLOR_CYAN, ASCII_COLOR_BLACK}};
  std::cout << str << std::endl;
}

#include <filesystem>

int main() {
  AsciiGL::initAsciiGL();
  statement();

  std::string input;

  try {
    // throw AsciiBasicException("Hello world");
    debug();
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
          std::cout << std::endl;
        }
      }
      std::cout << "请输入任意键继续 ... " << std::endl;
      getchar();
    }
  } catch (const AsciiBasicException &e) {
    std::cout << e.what() << std::endl;
  }
  AsciiGL::dropAsciiGL();

  getchar();

  return 0;
}