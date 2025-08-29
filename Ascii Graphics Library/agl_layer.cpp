#include "agl_layer.h"

namespace AsciiGL {
AsciiBasicLayer::AsciiBasicLayer()
    : Entity<AsciiBasicCanvas>(generateLabel(LABEL_LAYER_DEFAULT)) {
  // this->label = generateLabel(LABEL_LAYER_DEFAULT);
  this->display_state = true;
  this->center_coord.set(0, 0);
  this->coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(std::string &&label,
                                 const AsciiBasicCanvas &canvas)
    : Entity<AsciiBasicCanvas>(generateLabel(LABEL_LAYER_DEFAULT), canvas) {
  this->display_state = true;
  this->center_coord.set(0, 0);
  this->coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas,
                                 const Coord2d &coord)
    : /* Entity<AsciiBasicCanvas>(generateLabel(LABEL_LAYER_DEFAULT),
                                    canvas) */
      AsciiBasicLayer(canvas, coord, generateLabel(LABEL_LAYER_DEFAULT)) {
  // this->coord = coord;
  //  this->label = ;
  // this->display_state = true;
  // this->center_coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(AsciiBasicCanvas &&canvas,
                                 const Coord2d &coord)
    : AsciiBasicLayer(std::move(canvas), coord,
                      generateLabel(LABEL_LAYER_DEFAULT)) {}

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicCanvas &canvas,
                                 const Coord2d &coord, const std::string &label,
                                 bool display_state)
    : Entity<AsciiBasicCanvas>(label, canvas) {
  this->coord = coord;
  // this->label = label;
  this->display_state = display_state;
  this->center_coord.set(0, 0);
}

AsciiBasicLayer::AsciiBasicLayer(AsciiBasicCanvas &&canvas,
                                 const Coord2d &coord, std::string &&label,
                                 bool display_state)
    : Entity<AsciiBasicCanvas>(std::move(label), std::move(canvas)) {
  this->coord = coord;
  this->display_state = display_state;
  this->center_coord.set(0, 0);
}

/* AsciiBasicLayer::AsciiBasicLayer(const std::string &label)
    : Entity<AsciiBasicCanvas>(label) {
  // this->label = label;
  this->coord.set(0, 0);
  this->display_state = true;
  this->center_coord.set(0, 0);
}*/

AsciiBasicLayer::AsciiBasicLayer(const AsciiBasicLayer &layer)
    : Entity<AsciiBasicCanvas>(layer.label, *layer.body) {
  this->coord = layer.coord;
  // this->label = layer.label;
  this->center_coord = layer.center_coord;
  this->display_state = layer.display_state;
}

AsciiBasicLayer::AsciiBasicLayer(AsciiBasicLayer &&layer) noexcept
    : Entity<AsciiBasicCanvas>(std::move(layer.label), std::move(*layer.body)) {
  this->coord = layer.coord;
  // this->label = layer.label;
  this->center_coord = layer.center_coord;
  this->display_state = layer.display_state;

  layer.coord.set(0, 0);
  layer.label = "";
  layer.center_coord.set(0, 0);
  layer.display_state = true;
}

bool AsciiBasicLayer::operator==(const AsciiBasicLayer &layer) const noexcept {
  // std::cout << this->label << "\t" << layer.label << std::endl;
  // std::cout << this->coord.toString() << "\t" << layer.coord.toString()
  //<< std::endl;
  return (Entity<AsciiBasicCanvas>::operator==(layer) &&
          this->coord == layer.coord && /* this->label == layer.label &&*/
          this->center_coord == layer.center_coord &&
          this->display_state == layer.display_state);
}

bool AsciiBasicLayer::operator!=(const AsciiBasicLayer &layer) const noexcept {
  return !(*this == layer);
}

AsciiBasicLayer &AsciiBasicLayer::operator=(const AsciiBasicLayer &layer) {
  // AsciiBasicCanvas::operator=(layer);
  Entity<AsciiBasicCanvas>::operator=(layer);
  this->coord = layer.coord;
  // this->label = layer.label;
  this->display_state = layer.display_state;
  this->center_coord = layer.center_coord;

  return *this;
}

AsciiBasicLayer &AsciiBasicLayer::operator=(AsciiBasicLayer &&layer) noexcept {
  // AsciiBasicCanvas::operator=(std::move(layer));
  Entity<AsciiBasicCanvas>::operator=(std::move(layer));
  this->coord = layer.coord;
  // this->label = layer.label;
  this->display_state = layer.display_state;
  this->center_coord = layer.center_coord;

  layer.coord.set(0, 0);
  // layer.label = "";
  layer.center_coord.set(0, 0);
  layer.display_state = true;

  return *this;
}

void AsciiBasicLayer::info() const {
  std::cout << "AsciiBasicLayer¶ÔÏó" << std::endl;
  std::cout << "length:" << body->getLength() << std::endl
            << "width:" << body->getWidth() << std::endl
            << "block_length:" << body->getBlockLength() << std::endl
            << "background_element:"
            << "(\"" << body->getBackgroundStr() << "\")" << std::endl
            << "size:" << body->size() << std::endl
            << "coord:" << coord.toString() << std::endl
            << "center_coord:" << center_coord.toString() << std::endl
            << "label:" << label << std::endl
            << "display_state:" << spliceString(display_state) << std::endl;
}

std::string AsciiBasicLayer::getSerializeStr() const {
  return serializeType(label, coord, center_coord, display_state,
                       (AsciiBasicCanvas) * this->body);
}

void AsciiBasicLayer::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  /* std::cout << tokens.size() << std::endl;
  for (auto &index : tokens) {
    std::cout << index << std::endl;
  }*/
  if (tokens.size() <= 4)
    throw AsciiBasicException(FileFormatException);

  deserializeType(label, tokens[0]);
  deserializeType(coord, tokens[1]);
  deserializeType(center_coord, tokens[2]);
  deserializeType(display_state, tokens[3]);
  // AsciiBasicCanvas::loadSerializeStr(tokens[4]);
  // Entity<AsciiBasicCanvas>::loadSerializeStr(tokens[4]);
  deserializeType(*body, tokens[4]);
}
} // namespace AsciiGL