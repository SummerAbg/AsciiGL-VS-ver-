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
  for (int i = 0; i < canvas.getLength(); i++) {
    canvas.setAsciiBasicCanvasData({i, 0}, str);
    canvas.setAsciiBasicCanvasData({i, canvas.getWidth() - 1}, str);
  }
  for (int i = 1; i < canvas.getWidth() - 1; i++) {
    canvas.setAsciiBasicCanvasData({0, i}, str);
    canvas.setAsciiBasicCanvasData({canvas.getLength() - 1, i}, str);
  }
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
             const AsciiBasicString &str) {
  /* const int x1 = abs(coord1.x);
  const int x2 = abs(coord2.x);
  const int y1 = abs(coord1.y);
  const int y2 = abs(coord2.y);*/
}

void WinAPIDraw(const AsciiBasicCanvas &canvas) {
  static AsciiBasicCanvas canvBuffer;
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

  const auto dffrntPoints = compareCanvas(canvas, canvBuffer);

  for (const auto &index : dffrntPoints) {
    COORD coord = {(short)(index.x * canvas.getBlockLength()), (short)index.y};
    SetConsoleCursorPosition(hndl, coord);
    std::cout << canvas.getAsciiBasicCanvasData(index);
  }
  canvBuffer = canvas;
}
