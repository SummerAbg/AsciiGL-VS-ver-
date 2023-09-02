#include "AsciiBasicLayerMngr.h"
#include "AsciiBasicGraphics.h"

AsciiBasicLayerMngr::AsciiBasicLayerMngr(int length, int width) {
  AsciiBasicCanvas canvas = {length, width};
  AsciiBasicLayer layer = {canvas, {0, 0}, "background_layer"};
  layers.push_back(layer);
}

void AsciiBasicLayerMngr::addLayer(const DataType &layers) {
  for (const auto &index : layers) {
    this->layers.push_back(index);
  }
}

void AsciiBasicLayerMngr::deleteLayer(const std::string &name) {
  if (!isExistLayer(name)) {
    return;
  }
  const int index = getLayerCount(name) - 1;
  layers.erase(layers.begin() + index);
}

void AsciiBasicLayerMngr::insertLayer(int layerCnt,
                                      const AsciiBasicLayer &layer) {
  if (layerCnt <= 0 || layerCnt > layers.size())
    return;
  layers.insert(layers.begin() + layerCnt - 1, layer);
}

void AsciiBasicLayerMngr::insertLayer(int layerCnt, const DataType &layers) {
  if (layerCnt <= 0 || layerCnt > layers.size())
    return;
  for (int i = 0; i < layers.size(); i++) {
    const auto position = this->layers.begin() + layerCnt - 1 + i;
    this->layers.insert(position, layers[i]);
  }
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas() const {
  if (layers.size() <= 0)
    return AsciiBasicCanvas();

  AsciiBasicCanvas result = layers[0];
  for (const auto &index : layers) {
    const Coordinate2D coord = index.getCoordinate();
    result = overlapCanvas(index, result, coord);
  }

  return result;
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas(const std::string &name) const {
  for (const auto &index : layers) {
    if (name == index.getName())
      return index;
  }
  return AsciiBasicCanvas();
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](const std::string &name) {
  for (auto &index : layers) {
    if (name == index.getName())
      return index;
  }
  return layers[0];
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) {
  if (index < 0 || index >= layers.size())
    return layers[0];
  return layers[index];
}

const AsciiBasicLayer &
AsciiBasicLayerMngr::operator[](const std::string &name) const {
  for (const auto &index : layers) {
    if (name == index.getName())
      return index;
  }
  return layers[0];
}

const AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) const {
  if (index < 0 || index >= layers.size())
    return layers[0];
  return layers[index];
}

bool AsciiBasicLayerMngr::isExistLayer(const std::string &name) const {
  for (const auto &index : layers) {
    if (name == index.getName())
      return true;
  }
  return false;
}

int AsciiBasicLayerMngr::getLayerCount(const std::string &name) const {
  int result = -1;
  for (int i = 0; i < layers.size(); i++) {
    if (name == layers[i].getName()) {
      result = i + 1;
      break;
    }
  }
  return result;
}
