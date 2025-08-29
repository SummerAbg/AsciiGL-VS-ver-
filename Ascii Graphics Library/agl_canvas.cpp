#include "agl_canvas.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicCanvas::AsciiBasicCanvas() {
  this->block_length = 0;
  this->datas = std::make_unique<CanvasData>();
}

AsciiBasicCanvas::AsciiBasicCanvas(int length, int width,
                                   const AsciiBasicString &str) {
  this->block_length = static_cast<int>(str.size());
  this->datas = std::make_unique<CanvasData>(length, width, str);
}

AsciiBasicCanvas::AsciiBasicCanvas(std::string &&path) {
  this->block_length = 0;
  this->datas = std::make_unique<CanvasData>();
  load(path);
}

AsciiBasicCanvas::AsciiBasicCanvas(const AsciiBasicString &content) {
  this->block_length = static_cast<int>(content.size());
  this->datas = std::make_unique<CanvasData>(1, 1, content);
}

AsciiBasicCanvas::AsciiBasicCanvas(const AsciiBasicCanvas &canvas) {
  this->block_length = canvas.block_length;
  this->datas = std::make_unique<CanvasData>(*canvas.datas);
}

AsciiBasicCanvas::AsciiBasicCanvas(AsciiBasicCanvas &&canvas) noexcept {
  this->block_length = canvas.block_length;
  this->datas = std::move(canvas.datas);

  canvas.datas = nullptr;
  canvas.block_length = 0;
}

void AsciiBasicCanvas::info() const noexcept {
  std::cout << "AsciiBasicCanvas对象" << std::endl;
  std::cout << "length:" << datas->getLength() << std::endl
            << "width:" << datas->getWidth() << std::endl
            << "block_length:" << block_length << std::endl
            << "background_element:" << datas->getBackgroundElement()
            << std::endl
            << "size:" << datas->size() << std::endl;
  this->show();
}

std::string AsciiBasicCanvas::toString() const noexcept {
  return this->toAsciiBasicString().toString();
}

AsciiBasicString &AsciiBasicCanvas::operator[](const Coord2d &coord) {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  return (*datas)[coord];
}

const AsciiBasicString &
AsciiBasicCanvas::operator[](const Coord2d &coord) const {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  return (*datas)[coord];
}

const AsciiBasicString &AsciiBasicCanvas::operator()(int x, int y) const {
  if (!isCoordinate(Vec2d(x, y)))
    throw AsciiBasicException("coord非法!");

  return (*datas)(x, y);
}

void AsciiBasicCanvas::setCanvas(const Coord2d &coord,
                                 const AsciiBasicString &fill) {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  if (fill == datas->getElement(coord))
    return;

  auto &index = (*datas)[coord];

  if (fill.size() > block_length)
    index = cutText(fill, block_length - 1);
  else if (fill.size() == block_length)
    index = fill;
  else
    index = overlapText(index, fill, 0, true);
}

AsciiBasicString AsciiBasicCanvas::getCanvas(const Coord2d &coord) const {
  if (!isCoordinate(coord))
    throw AsciiBasicException("coord非法!");

  return this->datas->getElement(coord);
}

AsciiBasicString AsciiBasicCanvas::toAsciiBasicString() const noexcept {
  AsciiBasicString ret;
  const int length = datas->getLength();
  const int width = datas->getWidth();

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < length; j++) {
      bool is_element = datas->isCoordinate(j, i);
      const auto buffer =
          is_element ? datas->getElement(j, i) : datas->getBackgroundElement();

      ret += buffer;
    }
    ret += "\n";
  }
  return ret;
}

void AsciiBasicCanvas::clear() noexcept {
  this->block_length = 0;
  this->datas->clear();
}

void AsciiBasicCanvas::save(const std::string &path) const {
  std::ofstream outFile(path.c_str());

  if (!outFile.is_open())
    throw AsciiBasicException(FileNotExist);

  outFile << serialize(*this);

  outFile.close();
}

void AsciiBasicCanvas::load(const std::string &path) {
  const std::filesystem::path file_path(path);
  if (file_path.extension().string() != ".asc2")
    throw AsciiBasicException("该文件不是asc2文件!");

  const std::string fileData = getFileData(path);
  deserializeType(*this, fileData);
}

void AsciiBasicCanvas::show() const noexcept {
  std::cout << this->toAsciiBasicString();
}

bool AsciiBasicCanvas::isCoordinate(const Coord2d &coord) const noexcept {
  return datas->isCoordinate(coord);
}

COORD AsciiBasicCanvas::toConsoleCoord(const Coord2d &coord) const noexcept {
  COORD ret;
  ret.X = static_cast<short>(coord.x * block_length);
  ret.Y = static_cast<short>(coord.y);
  return ret;
}

bool AsciiBasicCanvas::operator==(
    const AsciiBasicCanvas &canvas) const noexcept {
  return (*this->datas == *canvas.datas &&
          this->block_length == canvas.block_length);
}

bool AsciiBasicCanvas::operator!=(
    const AsciiBasicCanvas &canvas) const noexcept {
  return !(*this == canvas);
}

AsciiBasicCanvas &AsciiBasicCanvas::operator=(const AsciiBasicCanvas &canvas) {
  this->block_length = canvas.block_length;
  *this->datas = *canvas.datas;

  return *this;
}

AsciiBasicCanvas &
AsciiBasicCanvas::operator=(AsciiBasicCanvas &&canvas) noexcept {
  this->block_length = canvas.block_length;
  this->datas = std::move(canvas.datas);

  canvas.datas = nullptr;
  canvas.block_length = 0;
  return *this;
}

std::string AsciiBasicCanvas::getSerializeStr() const {
  return serializeType(block_length, *datas);
}

void AsciiBasicCanvas::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  if (tokens.size() < 2)
    throw AsciiBasicException(FileFormatException);

  deserializeType(block_length, tokens[0]);
  deserializeType(*datas, tokens[1]);
}
} // namespace AsciiGL