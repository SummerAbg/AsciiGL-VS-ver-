#include "AsciiBasicCanvas.h"

AsciiBasicCanvas::AsciiBasicCanvas() {
  length = 0;
  width = 0;
  defaultFill = "";
  blockLength = 0;
}

AsciiBasicCanvas::AsciiBasicCanvas(int length, int width,
                                   const AsciiBasicString &fill) {
  this->length = length;
  this->width = width;
  defaultFill = fill;
  blockLength = defaultFill.size();
  bDatas = BlockData(length * width, fill);
}

AsciiBasicCanvas::AsciiBasicCanvas(const std::string &canvasFilePath) {
  length = 0;
  width = 0;
  defaultFill = TRPRSTR;
  blockLength = defaultFill.size();
  load(canvasFilePath);
}

void AsciiBasicCanvas::info() const {
  std::cout << "Length:" << length << std::endl
            << "Width:" << width << std::endl
            << "DefaultFill:" << defaultFill << std::endl
            << "Size:" << bDatas.size() << std::endl
            << "BlockLength:" << blockLength << std::endl;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      const auto block = bDatas[i * length + j];
      for (const auto &index : block) {
        std::cout << "(" << index.getColor() << ")";
      }
    }
    std::cout << std::endl;
  }
}

std::string AsciiBasicCanvas::toString() const {
  std::string result;

  AsciiBasicString buffer = this->getAsciiBasicString();
  result = buffer.toString();

  return result;
}

void AsciiBasicCanvas::setAsciiBasicCanvasData(Coordinate2D coord,
                                               const AsciiBasicString &fill) {
  if (!isCoordinateLegality(coord))
    return;

  if (fill.size() >= blockLength) {
    AsciiBasicString buffer;
    for (int i = 0; i < blockLength; i++) {
      buffer += fill[i];
    }
    bDatas[coord.y * length + coord.x] = buffer;
  }

  if (fill.size() < blockLength) {
    AsciiBasicString buffer = fill;
    const AsciiBasicString sourceFill = bDatas[coord.y * length + coord.x];
    const int size = blockLength - fill.size();

    for (int i = 0; i < size; i++) {
      const int index = blockLength - size + i;
      buffer += sourceFill[index];
    }
    bDatas[coord.y * length + coord.x] = buffer;
  }
}

AsciiBasicString
AsciiBasicCanvas::getAsciiBasicCanvasData(Coordinate2D coord) const {
  if (!isCoordinateLegality(coord))
    return "";
  return bDatas[coord.y * length + coord.x];
}

AsciiBasicString AsciiBasicCanvas::getAsciiBasicString() const {
  AsciiBasicString result;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      result += bDatas[i * length + j];
    }
    result += AsciiBasicString("\n", false, AsciiBasicChar::getDefaultColor());
  }
  return result;
}

void AsciiBasicCanvas::clear(bool flag) {
  if (flag) {
    *this = AsciiBasicCanvas();
  } else {
    this->bDatas = BlockData(length * width, defaultFill);
  }
}

void AsciiBasicCanvas::save(const std::string &canvasFilePath) const {
  std::ofstream outFile(canvasFilePath.c_str());

  if (!outFile.is_open())
    throw AsciiBasicError(__FUNC__, FileNotExist);

  outFile << serialize(this);

  outFile.close();
}

void AsciiBasicCanvas::load(const std::string &canvasFilePath) {
  std::ifstream inFile(canvasFilePath.c_str());

  if (!inFile.is_open())
    throw AsciiBasicError(__FUNC__, FileNotExist);

  *this = AsciiBasicCanvas();

  std::string fileData;
  std::string buffer;
  while (std::getline(inFile, buffer)) {
    fileData += buffer + "\n";
  }

  deserialize(this, fileData);

  inFile.close();
}

void AsciiBasicCanvas::show() const {
  std::cout << this->getAsciiBasicString();
}

bool AsciiBasicCanvas::isCoordinateLegality(Coordinate2D coord) const {
  if (coord.x >= 0 && coord.x < length && coord.y >= 0 && coord.y < width)
    return true;
  return false;
}

bool AsciiBasicCanvas::operator==(const AsciiBasicCanvas &canvas) const {
  if (this->length == canvas.getLength() && this->width == canvas.getWidth() &&
      this->blockLength == canvas.getBlockLength() &&
      this->defaultFill == canvas.getFill() &&
      this->bDatas == BlockData(canvas.begin(), canvas.end())) {
    return true;
  }
  return false;
}

bool AsciiBasicCanvas::operator!=(const AsciiBasicCanvas &canvas) const {
  return !(*this == canvas);
}

std::string AsciiBasicCanvas::getSerializeStr() const {
  std::string result;
  result += std::to_string(length) + "\n";
  result += std::to_string(width) + "\n";
  result += std::to_string(blockLength) + "\n";

  result += serialize(&defaultFill) + "\n";

  result += this->toString();
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      const auto trprData = bDatas[i * length + j].getTrprData();

      for (const auto &index : trprData) {
        result += std::to_string(index);
      }
    }
    result += "\n";
  }

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      const auto colorData = bDatas[i * length + j].getColorData();

      for (const auto &index : colorData) {
        result += std::to_string(index.r) + ",";
        result += std::to_string(index.g) + ",";
        result += std::to_string(index.b) + ";";
      }
    }
    result += "\n";
  }
  return result;
}

void AsciiBasicCanvas::loadSerializeStr(const std::string &str) {
  const auto tokens = split(str, '\n');

  if (tokens.size() < 4) {
    throw AsciiBasicError(__FUNC__, FileFormatError);
  }

  this->length = stringToInt(tokens[0]);
  this->width = stringToInt(tokens[1]);
  this->blockLength = stringToInt(tokens[2]);

  // 是否有完整颜色数据
  bool clr_flag = (tokens.size() == 4 + width * 3);

  deserialize(&defaultFill, tokens[3]);

  // 颜色块
  std::vector<std::string> colorBlocks;

  for (int fileLine = 4; fileLine < width + 4; fileLine++) {
    if (clr_flag)
      colorBlocks = split(tokens[fileLine + width * 2], ';');

    for (int i = 0; i < length; i++) {

      std::string text;
      TrprData trprData;
      ColorData color;

      for (int j = 0; j < blockLength; j++) {

        const int index = i * blockLength + j;

        text += tokens[fileLine][index];
        ////////////////////////////////////////////////text
        bool isTrpr = (tokens.size() >= 4 + width * 2)
                          ? charToBool(tokens[fileLine + width][index])
                          : false;
        trprData.push_back(isTrpr);
        ////////////////////////////////////////////////trprData

        ColorRGB clr;

        if (clr_flag) {
          const auto colorVals = split(colorBlocks[index], ',');

          const int r = stringToInt(colorVals[0]);
          const int g = stringToInt(colorVals[1]);
          const int b = stringToInt(colorVals[2]);

          clr = {r, g, b};
        } else {
          clr = AsciiBasicChar::getDefaultColor();
        }

        color.push_back(clr);
        ////////////////////////////////////////////////color
      }
      AsciiBasicString data = {text, color, trprData};
      bDatas.push_back(data);
    }
  }
}