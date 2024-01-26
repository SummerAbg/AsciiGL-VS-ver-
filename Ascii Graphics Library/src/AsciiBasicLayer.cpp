#include "AsciiBasicLayer.h"

AsciiBasicLayer::AsciiBasicLayer() { coord = {0, 0}; }

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas,
                                 Coordinate2D coord)
    : AsciiBasicCanvas(canvas) {
  this->coord = coord;

  static int index = 0;
  name = "untitled_" + std::to_string(index++);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas,
                                 Coordinate2D coord, const std::string &name)
    : AsciiBasicCanvas(canvas) {
  this->coord = coord;
  this->name = name;
}

bool AsciiBasicLayer::operator==(const AsciiBasicLayer &layer) const {
  if ((AsciiBasicCanvas)(*this) == (AsciiBasicCanvas)layer &&
      this->coord == layer.getCoordinate() && this->name == layer.getName()) {
    return true;
  }
  return false;
}

bool AsciiBasicLayer::operator!=(const AsciiBasicLayer &layer) const {
  return !(*this == layer);
}
