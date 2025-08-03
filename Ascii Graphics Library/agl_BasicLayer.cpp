#include "agl_BasicLayer.h"

namespace AsciiGL {
AsciiBasicLayer::AsciiBasicLayer() : AsciiBasicCanvas() {
  this->name = makeName("untitled_layer");
  this->display_state = true;
  this->center_coord.set(0, 0);
  this->coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas,
                                 const Coord2d &coord)
    : AsciiBasicCanvas(canvas) {
  this->coord = coord;
  this->name = makeName("untitled_layer");
  this->display_state = true;
  this->center_coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas,
                                 const Coord2d &coord, const std::string &name,
                                 bool display_state)
    : AsciiBasicCanvas(canvas) {
  this->coord = coord;
  this->name = name;
  this->display_state = display_state;
  this->center_coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const std::string &name) : AsciiBasicCanvas() {
  this->name = name;
  this->coord.set(0, 0);
  this->display_state = true;
  this->center_coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicLayer &layer)
    : AsciiBasicCanvas(layer) {
  this->coord = layer.coord;
  this->name = layer.name;
  this->center_coord = layer.center_coord;
  this->display_state = layer.display_state;
}

AsciiBasicLayer::AsciiBasicLayer(AsciiBasicLayer &&layer) noexcept
    : AsciiBasicCanvas(std::move(layer)) {
  this->coord = layer.coord;
  this->name = layer.name;
  this->center_coord = layer.center_coord;
  this->display_state = layer.display_state;

  layer.coord.set(0, 0);
  layer.name = "";
  layer.center_coord.set(0, 0);
  layer.display_state = true;
}

void AsciiBasicLayer::setCenterCoordinate(const Coord2d &coord) {
  this->center_coord = coord;
}

bool AsciiBasicLayer::operator==(const AsciiBasicLayer &layer) const {
  return (AsciiBasicCanvas::operator==(layer) && this->coord == layer.coord &&
          this->name == layer.name &&
          this->center_coord == layer.center_coord &&
          this->display_state == layer.display_state)
             ? true
             : false;
}

bool AsciiBasicLayer::operator!=(const AsciiBasicLayer &layer) const {
  return !(*this == layer);
}

AsciiBasicLayer &AsciiBasicLayer::operator=(const AsciiBasicLayer &layer) {
  AsciiBasicCanvas::operator=(layer);
  this->coord = layer.coord;
  this->name = layer.name;
  this->display_state = layer.display_state;
  this->center_coord = layer.center_coord;

  return *this;
}

AsciiBasicLayer &AsciiBasicLayer::operator=(AsciiBasicLayer &&layer) noexcept {
  AsciiBasicCanvas::operator=(std::move(layer));
  this->coord = layer.coord;
  this->name = layer.name;
  this->display_state = layer.display_state;
  this->center_coord = layer.center_coord;

  layer.coord.set(0, 0);
  layer.name = "";
  layer.center_coord.set(0, 0);
  layer.display_state = true;

  return *this;
}
void AsciiBasicLayer::info() const {
  std::cout << "AsciiBasicLayer¶ÔÏó" << std::endl;
  std::cout << "length:" << datas->getLength() << std::endl
            << "width:" << datas->getWidth() << std::endl
            << "block_length:" << block_length << std::endl
            << "background_element:" << datas->getBackgroundElement()
            << std::endl
            << "size:" << datas->size() << std::endl
            << "coord:" << coord.toString() << std::endl
            << "center_coord:" << center_coord.toString() << std::endl
            << "name:" << name << std::endl
            << "display_state:" << spliceString(display_state) << std::endl;
}
} // namespace AsciiGL