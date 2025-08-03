#include "agl_BasicLayerMngr.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicLayerMngr::AsciiBasicLayerMngr() {
  this->layers = std::make_shared<Layers>();
}

AsciiBasicLayerMngr::AsciiBasicLayerMngr(int length, int width,
                                         const AsciiBasicString &str) {
  AsciiBasicCanvas canvas(length, width, str);
  AsciiBasicLayer layer(canvas, Vec2d(0, 0), "background_layer");

  this->layers = std::make_shared<Layers>();
  this->layers->emplace_back(layer);
}

AsciiBasicLayerMngr::AsciiBasicLayerMngr(const AsciiBasicLayerMngr &mngr) {
  *this = mngr;
}

AsciiBasicLayerMngr::AsciiBasicLayerMngr(AsciiBasicLayerMngr &&mngr) noexcept {
  *this = mngr;
  mngr.layers = nullptr;
}

void AsciiBasicLayerMngr::append(const AsciiBasicLayer &layer) {
  this->layers->push_back(layer);
}

void AsciiBasicLayerMngr::append(AsciiBasicLayer &&layer) noexcept {
  this->layers->emplace_back(std::move(layer));
}

void AsciiBasicLayerMngr::append(const Layers &layers) {
  this->layers->insert(this->layers->end(), layers.begin(), layers.end());
}

void AsciiBasicLayerMngr::append(Layers &&layers) noexcept {
  this->layers->insert(this->layers->end(), layers.begin(), layers.end());
}

void AsciiBasicLayerMngr::remove(const std::string &name) {
  if (!isExistLayer(name))
    throw AsciiBasicException(__FUNC__, "确定name是否正确，不存在该图层!");

  const int index = getLayerCount(name);
  this->layers->erase(layers->begin() + index);
}

void AsciiBasicLayerMngr::insert(int layerCnt, const AsciiBasicLayer &layer) {
  if (layerCnt <= 0 || layerCnt > layers->size())
    throw AsciiBasicException(__FUNC__, "layerCnt不合法!");

  layers->insert(layers->begin() + layerCnt - 1, layer);
}

void AsciiBasicLayerMngr::insert(int layerCnt, const Layers &layers) {
  if (layerCnt <= 0 || layerCnt > this->layers->size())
    throw AsciiBasicException(__FUNC__, "layerCnt不合法!");

  const auto iter = this->layers->begin() + layerCnt - 1;
  this->layers->insert(iter, layers.begin(), layers.end());
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas() const {
  static AsciiBasicLayerMngr bffManager;
  static AsciiBasicCanvas bffCanvas;
  // static AsciiBasicCanvas tempCanvas;

  if (layers->size() <= 0)
    throw AsciiBasicException(__FUNC__, "layers的数量<=0!");

  if (*this == bffManager)
    return bffCanvas;

  AsciiBasicCanvas ret = (*layers)[0];
  Coord2d coord;

  for (const auto &index : *layers) {
    if (!index.isDisplay() /* || tempCanvas == (AsciiBasicCanvas)index*/)
      continue;

    coord = index.getCoordinate();
    coord -= index.getCenterCoordinate();
    ret = overlapCanvas(index, ret, coord);

    // tempCanvas = index;
  }

  bffManager = *this;
  bffCanvas = ret;

  return ret;
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas(const std::string &name) const {
  for (const auto &index : *layers) {
    if (name == index.getName())
      return index;
  }
  throw AsciiBasicException(__FUNC__, "没有该图层!");
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](const std::string &name) {
  for (auto &index : *layers) {
    if (name == index.getName())
      return index;
  }
  append(AsciiBasicLayer(name));
  return (*layers)[size() - 1];
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) {
  if (index < 0)
    throw AsciiBasicException(__FUNC__, ArrayOverflow);

  if (index >= layers->size()) {
    const int size = index + 1 - layers->size();
    for (int i = 0; i < size; i++) {
      append(AsciiBasicLayer());
    }
    return (*layers)[index];
  }
  return (*layers)[index];
}

const AsciiBasicLayer &
AsciiBasicLayerMngr::operator[](const std::string &name) const {
  for (const auto &index : *layers) {
    if (name == index.getName())
      return index;
  }
  throw AsciiBasicException(__FUNC__, "没有这样的图层");
}

const AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) const {
  if (index < 0 || index >= layers->size())
    throw AsciiBasicException(__FUNC__, ArrayOverflow);

  return (*layers)[index];
}

bool AsciiBasicLayerMngr::operator==(const AsciiBasicLayerMngr &mngr) const {
  return *layers == *mngr.layers;
}

bool AsciiBasicLayerMngr::operator!=(const AsciiBasicLayerMngr &mngr) const {
  return !(*layers == *mngr.layers);
}

AsciiBasicLayerMngr &
AsciiBasicLayerMngr::operator=(const AsciiBasicLayerMngr &mngr) {
  *this->layers = *mngr.layers;
  return *this;
}

AsciiBasicLayerMngr &
AsciiBasicLayerMngr::operator=(AsciiBasicLayerMngr &&mngr) noexcept {
  *this->layers = std::move(*mngr.layers);
  mngr.layers = nullptr;

  return *this;
}

AsciiBasicLayer AsciiBasicLayerMngr::getLayer(const std::string &name) const {
  return (*this)[name];
}

void AsciiBasicLayerMngr::setLayer(const AsciiBasicLayer &layer,
                                   const std::string &name) {
  (*this)[name] = layer;
}

void AsciiBasicLayerMngr::setLayer(const AsciiBasicLayer &layer, int index) {
  (*this)[index] = layer;
}

bool AsciiBasicLayerMngr::isExistLayer(const std::string &name) const {
  for (const auto &index : *layers) {
    if (name == index.getName())
      return true;
  }
  return false;
}

int AsciiBasicLayerMngr::getLayerCount(const std::string &name) const {
  const int size = layers->size();
  for (int i = 0; i < size; i++) {
    if (name == (*layers)[i].getName())
      return i;
  }
  throw AsciiBasicException(__FUNC__, "指定名称的图层不存在!");
}
} // namespace AsciiGL