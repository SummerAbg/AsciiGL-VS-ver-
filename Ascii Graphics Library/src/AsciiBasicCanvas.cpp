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

std::string AsciiBasicCanvas::getString() const {
  std::string result;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      auto blockData = bDatas[i * length + j];
      auto trprData = blockData.getTrprData();

      for (int k = 0; k < blockData.size(); k++) {
        bool isTrpr = trprData[k];

        if (isTrpr)
          result += AsciiBasicChar::getTrprChr();
        else
          result += blockData[k].getChr();
      }
    }
    result += (i == width - 1) ? "" : "\n";
  }
  return result;
}

void AsciiBasicCanvas::clear() { *this = AsciiBasicCanvas(); }

void AsciiBasicCanvas::save(const std::string &canvasFilePath) const {
  std::ofstream outFile(canvasFilePath.c_str());

  if (!outFile.is_open())
    throw AsciiBasicError("AsciiBasicCanvas::save()", FileNotExist);

  outFile << serialize(this);

  outFile.close();
}

void AsciiBasicCanvas::load(const std::string &canvasFilePath) {
  std::ifstream inFile(canvasFilePath.c_str());

  if (!inFile.is_open())
    throw AsciiBasicError("AsciiBasicCanvas::load()", FileNotExist);

  *this = AsciiBasicCanvas();

  std::string fileData;
  std::string buffer;
  while (std::getline(inFile, buffer)) {
    fileData += buffer + "\n";
  }

  deserialize(this, fileData);

  inFile.close();
}

void AsciiBasicCanvas::show() const { std::cout << this->getString(); }

bool AsciiBasicCanvas::isCoordinateLegality(Coordinate2D coord) const {
  if (coord.x >= 0 && coord.x < length && coord.y >= 0 && coord.y < width)
    return true;
  return false;
}

std::string AsciiBasicCanvas::getSerializeStr() const {
  std::string result;
  result += std::to_string(length) + "\n";
  result += std::to_string(width) + "\n";
  result += std::to_string(blockLength) + "\n";

  result += serialize(&defaultFill) + "\n";

  for (const auto &index : bDatas) {
    const auto buffer = serialize(&index) + "\n";
    result += buffer;
  }
  return result;
}

void AsciiBasicCanvas::loadSerializeStr(const std::string &str) {
  const auto tokens = split(str, '\n');

  if (tokens.size() < 4) {
    throw AsciiBasicError("AsciiBasicCanvas::loadSerializeStr()",
                          FileFormatError);
  }

  this->length = atoi(tokens[0].c_str());
  this->width = atoi(tokens[1].c_str());
  this->blockLength = atoi(tokens[2].c_str());
  deserialize(&defaultFill, tokens[3]);

  for (int i = 4; i < tokens.size(); i++) {
    AsciiBasicString str;
    deserialize(&str, tokens[i]);
    bDatas.push_back(str);
  }
}
