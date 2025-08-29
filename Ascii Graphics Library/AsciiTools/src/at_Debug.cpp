#include "at_debug.h"

void AsciiTools::debug_log(const std::string &str) {
  AsciiBasicString prefix("[ debug ]", false,
                          {ASCII_COLOR_RED, ASCII_COLOR_YELLOW_GREEN});
  AsciiBasicString log = prefix + " " + str;
  std::cout << log << std::endl;
}

void AsciiTools::winApiText(const COORD &coord, const std::string &str) {
  static std::string buffer;

  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  // SetConsoleCursorPosition(hndl, coord);

  buffer = str;

  SetConsoleCursorPosition(hndl, coord);
  setWordColor(ASCII_COLOR_WHITE);
  setBackgroundColor(ASCII_COLOR_GREY);
  std::cout << str;
  setColor(AsciiBasicChar::getDefaultColor());
}