#include "agl_layermngr.h"
#include "at_basicmanager.h"
#include "graphics.h"

namespace AsciiGL {
AsciiBasicLayerMngr::AsciiBasicLayerMngr()
    : BasicManager<AsciiBasicCanvas, AsciiBasicLayer>() {
  // this->layers = std::make_shared<Layers>();
}

AsciiBasicLayerMngr::AsciiBasicLayerMngr(int length, int width,
                                         const AsciiBasicString &str)
    : BasicManager<AsciiBasicCanvas, AsciiBasicLayer>() {
  AsciiBasicCanvas canvas(length, width, str);

  // this->layers = std::make_shared<Layers>();

  AsciiBasicLayer layer(canvas, Vec2d(0, 0), LABEL_LAYER_BACKGROUND);
  // this->layers->emplace_back(std::move(layer));
  // this->elements->push_back(std::make_shared<AsciiBasicLayer>(
  //    canvas, Vec2d(0, 0), LABEL_LAYER_BACKGROUND));
  this->elements->emplace_back(std::make_shared<AsciiBasicLayer>(layer));
  // this->elements->push_back(layer);
}

/* AsciiBasicLayerMngr::AsciiBasicLayerMngr(const AsciiBasicLayerMngr &mngr) {
  this->layers = std::make_shared<Layers>();
  *this->layers = *mngr.layers;
}

 AsciiBasicLayerMngr::AsciiBasicLayerMngr(
    AsciiBasicLayerMngr &&mngr) noexcept {
  this->layers = std::move(mngr.layers);
  mngr.layers = nullptr;
}*/

AsciiBasicLayerMngr::AsciiBasicLayerMngr(
    const std::initializer_list<AsciiBasicLayer> &layers)
    : BasicManager<AsciiBasicCanvas, AsciiBasicLayer>() {
  for (const auto &index : layers) {
    this->elements->emplace_back(std::make_shared<AsciiBasicLayer>(index));
    // this->elements->push_back(index);
  }
}

/* AsciiBasicLayerMngr::AsciiBasicLayerMngr(
    const std::initializer_list<AsciiBasicLayer> &objs) {
  this->layers = std::make_shared<Layers>();
  for (const auto &index : objs) {
    this->layers->push_back(std::make_shared<AsciiBasicLayer>(index));
    // this->layers->emplace_back(index);
  }
}*/

void AsciiBasicLayerMngr::append(const AsciiBasicLayer &layer) {
  this->elements->emplace_back(std::make_shared<AsciiBasicLayer>(layer));
  // this->elements->push_back(layer);
  //  this->layers->push_back(layer);
}

void AsciiBasicLayerMngr::append(AsciiBasicLayer &&layer) noexcept {
  this->elements->emplace_back(
      std::make_shared<AsciiBasicLayer>(std::move(layer)));
  //  this->elements->emplace_back(std::move(layer));
  // this->layers->emplace_back(std::move(layer));
}

void AsciiBasicLayerMngr::append(
    const std::initializer_list<AsciiBasicLayer> &layers) {
  /* Layers p_layers;
   for (const auto index : layers) {
    p_layers.push_back(std::make_shared<AsciiBasicLayer>(index));
  }
  this->layers->insert(this->layers->end(), p_layers.begin(), p_layers.end());*/
  for (const auto &index : layers) {
    // this->elements->push_back(
    //     std::make_shared<Entity>(index.getLabel(), std::move(index)));
    this->elements->emplace_back(std::make_shared<Entity>(index));
    // this->elements->push_back(index);
  }
}

void AsciiBasicLayerMngr::insert(int layerCnt, const AsciiBasicLayer &layer) {
  if (layerCnt <= 0 || layerCnt > elements->size())
    throw AsciiBasicException("layerCnt不合法!");

  const auto iter = this->elements->begin() + layerCnt - 1;
  elements->emplace(iter, std::make_shared<AsciiBasicLayer>(layer));
  // elements->emplace(layerCnt - 1, layer);
}

void AsciiBasicLayerMngr::insert(
    int layerCnt, const std::initializer_list<AsciiBasicLayer> &layers) {
  if (layerCnt <= 0 || layerCnt > this->elements->size())
    throw AsciiBasicException("layerCnt不合法!");

  const auto iter = this->elements->begin() + layerCnt - 1;

  /* Layers p_layers;
   for (const auto index : layers) {
     p_layers.emplace_back(std::make_shared<AsciiBasicLayer>(index));
   }
   this->elements->insert(iter, p_layers.begin(), p_layers.end());*/
  for (const auto &index : layers) {
    elements->emplace(iter, std::make_shared<AsciiBasicLayer>(index));
    // elements->emplace(layerCnt - 1, index);
  }
}

/*void AsciiBasicLayerMngr::append(const AsciiBasicLayer &layer) {
  this->layers->push_back(std::make_shared<AsciiBasicLayer>(layer));
  // this->layers->push_back(layer);
}

void AsciiBasicLayerMngr::append(AsciiBasicLayer &&layer) noexcept {
  this->layers->emplace_back(
      std::make_shared<AsciiBasicLayer>(std::move(layer)));
  // this->layers->emplace_back(std::move(layer));
}

void AsciiBasicLayerMngr::append(const Layers &layers) {
  this->layers->insert(this->layers->end(), layers.begin(), layers.end());
}

void AsciiBasicLayerMngr::append(Layers &&layers) noexcept {
  // 这个实现会不会丧失右值引用的意义？
  this->layers->insert(this->layers->end(), layers.begin(), layers.end());
}

void AsciiBasicLayerMngr::append(
    const std::initializer_list<AsciiBasicLayer> &layers) {
  for (const auto &index : layers) {
    this->elements->push_back(
        std::make_shared<Entity>(index.getLabel(), std::move(index)));
  }
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

  layers->insert(layers->begin() + layerCnt - 1,
                 std::make_shared<AsciiBasicLayer>(layer));
}

void AsciiBasicLayerMngr::insert(int layerCnt, const Layers &layers) {
  if (layerCnt <= 0 || layerCnt > this->layers->size())
    throw AsciiBasicException(__FUNC__, "layerCnt不合法!");

  const auto iter = this->layers->begin() + layerCnt - 1;
  this->layers->insert(iter, layers.begin(), layers.end());
}

void AsciiBasicLayerMngr::insert(
    int layerCnt, const std::initializer_list<AsciiBasicLayer> &layers) {
  if (layerCnt <= 0 || layerCnt > this->layers->size())
    throw AsciiBasicException(__FUNC__, "layerCnt不合法!");

  const auto iter = this->layers->begin() + layerCnt - 1;

  Layers p_layers;
  for (const auto index : layers) {
    p_layers.push_back(std::make_shared<AsciiBasicLayer>(index));
  }
  this->layers->insert(iter, p_layers.begin(), p_layers.end());
}*/

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas() const {
  static AsciiBasicLayerMngr bffManager;
  static AsciiBasicCanvas bffCanvas;
  // static AsciiBasicCanvas tempCanvas;

  if (elements->size() <= 0)
    throw AsciiBasicException("layers的数量<=0!");

  // 由于AsciiBasicLayer的存储数据类型变成了Vector<std::shared_ptr<AsciiBasicLayer>>
  //  所以在判断两个Vector是否相等时，比较的只是每个元素的地址是否一致（而不是每个元素的内容）
  //  所以建议重写Vector的==运算符(如果不重写，图层管理器的静息运行效率大打折扣)

  if (*this == bffManager)
    return bffCanvas;

  AsciiBasicCanvas ret = *(*elements)[0]->body;
  // AsciiBasicCanvas ret = *(*elements)[0].body;
  Coord2d coord;

  for (const auto &index : *elements) {
    if (!index->isDisplay() /* || tempCanvas == (AsciiBasicCanvas)index*/)
      continue;

    coord = index->getCoordinate();
    coord -= index->getCenterCoordinate();
    ret = overlapCanvas(*index->body, ret, coord);
    // tempCanvas = index;
  }

  bffManager = *this;
  bffCanvas = ret;

  return ret;
}

AsciiBasicCanvas AsciiBasicLayerMngr::getCanvas(const std::string &name) const {
  for (const auto &index : *elements) {
    if (name == index->getLabel())
      return *index->body;
  }
  throw AsciiBasicException("没有该图层!");
}

/* AsciiBasicLayer &AsciiBasicLayerMngr::operator[](const std::string &name) {
  for (auto &index : *layers) {
    if (name == index->getLabel())
      return *index;
  }
  append(AsciiBasicLayer(name));
  return *(*layers)[size() - 1];
}

AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) {
  if (index < 0)
    throw AsciiBasicException(, ArrayOverflow);

  if (index >= layers->size()) {
    const int size = index + 1 - layers->size();
    for (int i = 0; i < size; i++) {
      append(AsciiBasicLayer());
    }
    return *(*layers)[index];
  }
  return *(*layers)[index];
}

const AsciiBasicLayer &
AsciiBasicLayerMngr::operator[](const std::string &name) const {
  for (const auto &index : *layers) {
    if (name == index->getLabel())
      return *index;
  }
  throw AsciiBasicException( "没有这样的图层");
}

const AsciiBasicLayer &AsciiBasicLayerMngr::operator[](int index) const {
  if (index < 0 || index >= layers->size())
    throw AsciiBasicException(__FUNC__, ArrayOverflow);

  return *(*layers)[index];
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
  this->layers = std::move(mngr.layers);
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
    if (name == index->getLabel())
      return true;
  }
  return false;
}

int AsciiBasicLayerMngr::getLayerCount(const std::string &name) const {
  const int size = layers->size();
  for (int i = 0; i < size; i++) {
    if (name == (*layers)[i]->getLabel())
      return i;
  }
  throw AsciiBasicException(__FUNC__, "指定名称的图层不存在!");
}*/

void AsciiBasicLayerMngr::info() const noexcept {
  std::cout << "AsciiBasicLayerMngr对象" << std::endl;
  std::cout << "size:" << this->elements->size() << std::endl;
  std::cout << "layers:" << std::endl;

  for (const auto &index : *elements) {
    std::cout << "图层标签:" << index->getLabel()
              << "\t图层坐标:" << index->getCoordinate().toString()
              << "\t图层中心坐标:" << index->getCenterCoordinate().toString()
              << "\t图层长度:" << index->body->getLength() << "\t图层宽度"
              << index->body->getWidth() << std::endl;
  }
}

std::string AsciiBasicLayerMngr::toString() const noexcept {
  /*********************/
  /*还没实现666*/
  return "AsciiBasicLayerMngr";
}

/* std::string AsciiBasicLayerMngr::getSerializeStr() const {
  return serializeType(*layers);
}

void AsciiBasicLayerMngr::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  if (tokens.size() < 1)
    throw AsciiBasicException(__FUNC__, FileFormatException);

  this->layers = std::make_unique<Layers>();

  // deserializeType(*layers, tokens[0]);
  const auto tokens_layers = bracketMatch(tokens[0]);

  for (const auto &index : tokens_layers) {
    //
buffer的声明不能放倒for循环外面，因为deserializeType函数会重新为buffer申请内存
    AsciiBasicLayer buffer;
    deserializeType(buffer, index);
    this->layers->push_back(
        std::make_shared<AsciiBasicLayer>(std::move(buffer)));
  }
}*/
} // namespace AsciiGL