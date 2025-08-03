#include "graphics.h"

namespace AsciiGL {
AsciiBasicCanvas getCanvas(const AsciiBasicCanvas &canvas, Coord2d coordA,
                           Coord2d coordB) {
  if (!canvas.isCoordinate(coordA) || !canvas.isCoordinate(coordB) ||
      coordA == coordB) {
    throw AsciiBasicException(
        __FUNC__, "coordA��coordB������Ƿ�!���ٿ�������Ϊ���л���������Ƿ� "
                  "�ڿ�������Ϊ����������ȣ�");
  }

  const int length = abs(coordA.x - coordB.x) + 1;
  const int width = abs(coordA.y - coordB.y) + 1;
  const auto str = canvas.getBackgroundStr();

  AsciiBasicCanvas ret(length, width, str);

  // ������������Ϊ����ľ��Σ��Ծ������Ϸ��Ķ���Ϊ����������
  Coord2d coord((coordA.x < coordB.x ? coordA.x : coordB.x),
                (coordA.y < coordB.y ? coordA.y : coordB.y));

  AsciiBasicString text;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      text = canvas(coord.x + j, coord.y + i);
      ret.setCanvas(Vec2d(j, i), text);
    }
  }
  return ret;
}

AsciiBasicCanvas overlapCanvas(const AsciiBasicCanvas &canvas,
                               const AsciiBasicCanvas &target, Coord2d coord) {
  AsciiBasicCanvas ret = target;
  AsciiBasicString str_canvas;
  AsciiBasicString str_target;
  AsciiBasicString text;

  const auto coords = compareCanvas(target, canvas, coord);

  for (const auto &index : coords) {
    if (target.isCoordinate(index)) {
      Coord2d coord_target(index);
      Coord2d coord_canvas(index.x - coord.x, index.y - coord.y);

      str_canvas = canvas.getCanvas(coord_canvas);
      str_target = target.getCanvas(coord_target);

      if (str_canvas == str_target)
        continue;

      text = str_canvas;

      const int size_text = text.size();
      AsciiTextColor color;
      AsciiBasicChar index_chr_target;
      for (int i = 0; i < size_text; i++) {
        // ��������
        auto &index_chr_canvas = text[i];
        index_chr_target = str_target[i];
        //  ��͸�����ݵĴ���
        if (index_chr_canvas.isTrpr())
          index_chr_canvas = index_chr_target;

        // ��RGBA���ݵĴ���
        color = mixAsciiTextColor(index_chr_canvas.getColor(),
                                  index_chr_target.getColor());
        index_chr_canvas.setColor(color);
      }

      ret.setCanvas(coord_target, text);
    }
  }

  return ret;
}

void setText(AsciiBasicCanvas &canvas, Coord2d coord,
             const AsciiBasicString &str) {
  if (!canvas.isCoordinate(coord))
    throw AsciiBasicException(__FUNC__, "coord�Ƿ�!");

  if (str.size() <= canvas.getBlockLength()) {
    canvas.setCanvas(coord, str);
    return;
  }

  int strIndex = 0;
  int indexCount = 0;

  const int block_length = canvas.getBlockLength();
  const int strSize = str.size();

  AsciiBasicString buffer;
  for (int i = 0; i + block_length <= strSize; i += block_length) {
    for (int j = 0; j < block_length; j++) {
      buffer += str[i + j];
      strIndex = i + j;
    }
    canvas.setCanvas(Vec2d(coord.x + indexCount, coord.y), buffer);
    indexCount++;
    buffer.clear();
  }
  if (strIndex != strSize - 1) {
    AsciiBasicString buffer;
    for (int i = strIndex + 1; i < strSize; i++) {
      buffer += str[i];
    }
    canvas.setCanvas(Vec2d(coord.x + indexCount, coord.y), buffer);
  }
}

void setText(AsciiBasicLayer &layer, Coord2d coord,
             const AsciiBasicString &text) {
  const int length = getBlockNumber(text.size(), TRPRSTR.size());
  const int width = 1;
  const std::string name = layer.getName();

  AsciiBasicCanvas canvas(length, width);
  setText(canvas, Vec2d(0, 0), text);

  layer = AsciiBasicLayer(canvas, coord, name);
}

void setText(AsciiBasicLayerMngr &mngr, Coord2d coord,
             const AsciiBasicString &text, const std::string &layerName) {
  // Ŀǰ���ڿ����Ƿ��ع���δ��룬��Ϊ���漰���ȶ��Ե�����
  // setText()��Ŀ����Ϊ����ԭ�е�ͼ��Ļ����Ͻ����ı��ĵ��ӣ�
  // Ȼ���˶δ���ȴ���ý�ԭͼ���滻�ķ���ʵ���ı����ӣ�
  // ����ܻᵼ��һЩ���벻�������⣬��ͼ�����ʾ״̬������
  AsciiBasicLayer textLayer(layerName);
  setText(textLayer, coord, text);

  mngr[layerName] = textLayer;
}

void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str) {
  const int cLength = canvas.getLength();
  const int cWidth = canvas.getWidth();

  setLine(canvas, Vec2d(0, 0), Vec2d(cLength - 1, 0), str);
  setLine(canvas, Vec2d(0, cWidth - 1), Vec2d(cLength - 1, cWidth - 1), str);
  setLine(canvas, Vec2d(0, 0), Vec2d(0, cWidth - 1), str);
  setLine(canvas, Vec2d(cLength - 1, 0), Vec2d(cLength - 1, cWidth - 1), str);
}

std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas,
                                   Coord2d coord) {
  std::vector<Point2D> ret;
  const int length = canvas.getLength();
  const int width = canvas.getWidth();

  AsciiBasicString str_target;
  AsciiBasicString str_canvas;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      Coord2d coord_canvas(j, i);
      Coord2d coord_target(j + coord.x, i + coord.y);

      if (!target.isCoordinate(coord_target)) {
        ret.emplace_back(coord_target);
        continue;
      }

      str_target = target.getCanvas(coord_target);
      str_canvas = canvas.getCanvas(coord_canvas);

      if (str_target != str_canvas)
        ret.emplace_back(coord_target);
    }
  }
  return ret;
}

void setLine(AsciiBasicCanvas &canvas, Coord2d coordA, Coord2d coordB,
             const AsciiBasicString &str, int level) {
  const int x1 = coordA.x;
  const int x2 = coordB.x;
  const int y1 = coordA.y;
  const int y2 = coordB.y;

  if (x1 == x2) {
    for (int y = y1; y <= y2; y++) {
      canvas.setCanvas(Vec2d(x1, y), str);
    }
  } else if (y1 == y2) {
    for (int x = x1; x <= x2; x++) {
      canvas.setCanvas(Vec2d(x, y1), str);
    }
  } else {
    const double targetX = abs(x2 - x1) + 1;
    const double deltaX = pow(10, -level);

    for (double i = 0; i < targetX; i += deltaX) {
      const Coord2d coord(
          static_cast<int>((coordA.x < coordB.x) ? x1 + i : x1 - i),
          static_cast<int>(y1 + getY(coordA, coordB, i)));

      canvas.setCanvas(coord, str);
    }
  }
}

void reflect(AsciiBasicCanvas &canvas) {
  const int width = canvas.getWidth();
  const int length = canvas.getLength();
  const int index_w = (width / 2 - ((width == 0) ? 1 : 0));

  Coord2d coord_r;
  Coord2d coord;
  AsciiBasicString str_r;
  AsciiBasicString str;

  for (int i = 0; i < index_w; i++) {
    for (int j = 0; j < length; j++) {
      coord_r.set(j, i);
      coord.set(j, width - i - 1);

      str_r = canvas.getCanvas(coord_r);
      str = canvas.getCanvas(coord);

      canvas.setCanvas(coord_r, str);
      canvas.setCanvas(coord, str_r);
    }
  }
}

#if defined(_WIN64) || defined(_WIN32)

void winApiDraw(const AsciiBasicCanvas &canvas, bool isClean) {
  static AsciiBasicCanvas canvasBuffer;
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);

  if (isClean)
    canvasBuffer.clear();

  const auto coords = compareCanvas(canvasBuffer, canvas);
  if (coords.size() == 0)
    return;

  for (const auto &coord : coords) {
    if (canvas.isCoordinate(coord)) {
      SetConsoleCursorPosition(hndl, canvas.toConsoleCoord(coord));
      std::cout << canvas.getCanvas(coord);
    }
  }
  canvasBuffer = canvas;
}

void winApiDraw(const AsciiBasicLayerMngr &mngr, bool isClean) {
  winApiDraw(mngr.getCanvas(), isClean);
}

void hideCursor() {
  HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO CursorInfo;

  GetConsoleCursorInfo(hndl, &CursorInfo);
  CursorInfo.bVisible = false;

  SetConsoleCursorInfo(hndl, &CursorInfo);
}

#endif
} // namespace AsciiGL