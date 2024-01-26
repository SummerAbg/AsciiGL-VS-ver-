#include "AsciiBasicGraphics.h"

AsciiBasicCanvas getCanvas(const AsciiBasicCanvas &canvas, Coordinate2D coord1,
                           Coordinate2D coord2) {
  const int length = abs(coord1.x - coord2.x) + 1;
  const int width = abs(coord1.y - coord2.y) + 1;
  const auto fill = canvas.getFill();

  AsciiBasicCanvas result(length, width, fill);

  for (int i = coord1.y; i <= coord2.y; i++) {
    for (int j = coord1.x; j <= coord2.x; j++) {
      const auto fill = canvas.getAsciiBasicCanvasData({j, i});
      const Coordinate2D coord = {j - coord1.x, i - coord1.y};

      result.setAsciiBasicCanvasData(coord, fill);
    }
  }
  return result;
}

AsciiBasicCanvas overlapCanvas(const AsciiBasicCanvas &canvas,
                               const AsciiBasicCanvas &target,
                               Coordinate2D coord) {
  AsciiBasicCanvas result = target;
  for (int i = coord.y; i < target.getWidth(); i++) {
    for (int j = coord.x; j < target.getLength(); j++) {

      const auto bCanvas =
          canvas.getAsciiBasicCanvasData({j - coord.x, i - coord.y});

      const auto bTarget = target.getAsciiBasicCanvasData({j, i});

      if (bCanvas == bTarget)
        continue;

      const auto cnvTrprData = bCanvas.getTrprData();

      AsciiBasicString fill;
      for (int k = 0; k < cnvTrprData.size(); k++) {
        if (!cnvTrprData[k])
          fill += bCanvas[k];
      }
      result.setAsciiBasicCanvasData({j, i}, fill);
    }
  }

  return result;
}

void setText(AsciiBasicCanvas &canvas, Coordinate2D coord,
             const AsciiBasicString &str) {
  if (str.size() <= canvas.getBlockLength()) {
    canvas.setAsciiBasicCanvasData(coord, str);
    return;
  }

  int strIndex = 0;
  int indexCount = 0;
  const int blockLength = canvas.getBlockLength();
  const int strSize = str.size();

  AsciiBasicString buffer;
  for (int i = 0; i + blockLength <= strSize; i += blockLength) {
    for (int j = 0; j < blockLength; j++) {
      buffer += str[i + j];
      strIndex = i + j;
    }
    canvas.setAsciiBasicCanvasData({coord.x + indexCount, coord.y}, buffer);
    indexCount++;
    buffer = AsciiBasicString();
  }
  if (strIndex != strSize - 1) {
    AsciiBasicString buffer;
    for (int i = strIndex + 1; i < strSize; i++) {
      buffer += str[i];
    }
    canvas.setAsciiBasicCanvasData({coord.x + indexCount, coord.y}, buffer);
  }
}

void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str) {
  const int cLength = canvas.getLength();
  const int cWidth = canvas.getWidth();

  setLine(canvas, {0, 0}, {cLength - 1, 0}, str);
  setLine(canvas, {0, cWidth - 1}, {cLength - 1, cWidth - 1}, str);
  setLine(canvas, {0, 0}, {0, cWidth - 1}, str);
  setLine(canvas, {cLength - 1, 0}, {cLength - 1, cWidth - 1}, str);
}

std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas) {
  std::vector<Point2D> result;

  for (int i = 0; i < target.getWidth(); i++) {
    for (int j = 0; j < target.getLength(); j++) {
      if (target.getAsciiBasicCanvasData({j, i}) !=
          canvas.getAsciiBasicCanvasData({j, i})) {
        result.push_back({j, i});
      }
    }
  }

  return result;
}

void setLine(AsciiBasicCanvas &canvas, Coordinate2D coord1, Coordinate2D coord2,
             const AsciiBasicString &str, int level) {
  const int x1 = coord1.x;
  const int x2 = coord2.x;
  const int y1 = coord1.y;
  const int y2 = coord2.y;

  if (x1 == x2) {

    for (int y = y1; y <= y2; y++) {
      canvas.setAsciiBasicCanvasData({x1, y}, str);
    }
  } else if (y1 == y2) {

    for (int x = x1; x <= x2; x++) {
      canvas.setAsciiBasicCanvasData({x, y1}, str);
    }
  } else {

    const double targetX = abs(x2 - x1) + 1;
    const double deltaX = pow(10, -level);

    for (double i = 0; i < targetX; i += deltaX) {
      const Coordinate2D coord = {
          static_cast<int>((coord1.x < coord2.x) ? x1 + i : x1 - i),
          static_cast<int>(y1 + getY(coord1, coord2, i))};

      canvas.setAsciiBasicCanvasData(coord, str);
    }
  }
}

#if defined(_WIN64) || defined(_WIN32)

void WinAPIDraw(const AsciiBasicCanvas &canvas) {
  static AsciiBasicCanvas canvBuffer;
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

  const auto dffrntPoints = compareCanvas(canvas, canvBuffer);

  for (const auto &index : dffrntPoints) {
    const COORD coord = {(short)(index.x * canvas.getBlockLength()),
                         (short)index.y};
    SetConsoleCursorPosition(hndl, coord);
    std::cout << canvas.getAsciiBasicCanvasData(index);
  }
  canvBuffer = canvas;
}

#endif
