#pragma once

#include "at_basic.h"
#include "at_entity.h"
#include "at_ptrvector.h"
#include "at_vector.h"

namespace AsciiTools {
template <typename T, typename EntityType = Entity<T>>
class BasicManager : public AsciiBasicObject {
public:
  static_assert(!(std::is_same_v<EntityType, Entity<T>> ||
                  std::is_base_of_v<EntityType, Entity<T>>),
                "EntityType is base of Entity<T> or Entity<T> itself!");

  using Entity = EntityType;
  using Elements = Vector<std::shared_ptr<Entity>>;
  // using Elements = PtrVector<Entity>;
  using pElements = std::unique_ptr<Elements>;

  BasicManager() { this->elements = std::make_unique<Elements>(); }
  BasicManager(const std::initializer_list<Entity> &list) : BasicManager() {
    for (const auto &index : list) {
      this->elements->emplace_back(std::make_shared<Entity>(index));
      // this->elements->push_back(index);
    }
  }

  BasicManager(const BasicManager &mngr) : BasicManager() {
    *this->elements = *mngr.elements;
  }

  BasicManager(BasicManager &&mngr) noexcept {
    this->elements = std::move(mngr.elements);
  }

  virtual ~BasicManager() {}

  virtual void info() const override;
  virtual std::string toString() const override;

  size_t size() const noexcept { return elements->size(); }

  auto begin() const noexcept { return elements->begin(); }
  auto end() const noexcept { return elements->end(); }

  bool isExistElement(const std::string &label) const noexcept;

  int getElementIndex(const std::string &label) const noexcept;
  EntityType getElement(const std::string &label) const;
  EntityType getElement(int index) const;

  void setElement(const T &element, const std::string &label) noexcept;
  void setElement(const T &element, int index) noexcept;

  virtual void append(const Entity &element);
  virtual void append(Entity &&element) noexcept;
  virtual void append(const T &element, const std::string &label);
  virtual void append(T &&element, std::string &&label) noexcept;
  virtual void append(const std::initializer_list<Entity> &list);

  virtual void remove(const std::string &label);
  virtual void insert(int index, const Entity &element);

  EntityType &operator[](const std::string &label) noexcept;
  EntityType &operator[](int index);
  const EntityType &operator[](const std::string &label) const;
  const EntityType &operator[](int index) const;

  bool operator==(const BasicManager &mngr) const noexcept {
    return *elements == *mngr.elements;
  }

  bool operator!=(const BasicManager &mngr) const noexcept {
    return !(*elements == *mngr.elements);
  }

  BasicManager &operator=(const BasicManager &mngr);
  BasicManager &operator=(BasicManager &&mngr) noexcept;

protected:
  // 获取序列化字符串
  virtual std::string getSerializeStr() const override;
  // 加载序列化字符串
  virtual void loadSerializeStr(const std::string &str) override;

protected:
  pElements elements;
};

template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::info() const {
  std::cout << "BasicManager<T, EntityType>对象" << std::endl;
  std::cout << "size:" << this->elements->size() << std::endl;
  std::cout << "elements:" << std::endl;

  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *elements) {
    type_decorator.init(*index->body);
    std::cout << index->label << "\t" << type_decorator.toTargetType()
              << std::endl;
  }
}

template <typename T, typename EntityType>
inline std::string BasicManager<T, EntityType>::toString() const {
  return "BasicManager<T, EntityType>";
}

template <typename T, typename EntityType>
inline bool BasicManager<T, EntityType>::isExistElement(
    const std::string &label) const noexcept {
  for (const auto &index : *elements) {
    if (label == index->label)
      return true;
  }
  return false;
}

template <typename T, typename EntityType>
inline int BasicManager<T, EntityType>::getElementIndex(
    const std::string &label) const noexcept {
  for (const auto &index : *elements) {
    if (label == index->label)
      return true;
  }
  return false;
}

template <typename T, typename EntityType>
inline EntityType
BasicManager<T, EntityType>::getElement(const std::string &label) const {
  return (*this)[label];
}

template <typename T, typename EntityType>
inline EntityType BasicManager<T, EntityType>::getElement(int index) const {
  return (*this)[index];
}

template <typename T, typename EntityType>
inline void
BasicManager<T, EntityType>::setElement(const T &element,
                                        const std::string &label) noexcept {
  *((*this)[label].body) = element;
}

template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::setElement(const T &element,
                                                    int index) noexcept {
  *((*this)[index].body) = element;
}

template <typename T, typename EntityType>
inline void
AsciiTools::BasicManager<T, EntityType>::append(const Entity &element) {
  this->elements->emplace_back(std::make_shared<Entity>(element));
  // this->elements->push_back(element);
}

template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::append(Entity &&element) noexcept {
  // this->elements->push_back(std::make_shared<Entity>(std::move(element)));
  this->elements->emplace_back(std::make_shared<Entity>(std::move(element)));
  // this->elements->emplace_back(std::move(element));
}

/*******************/
template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::append(const T &element,
                                                const std::string &label) {
  this->elements->emplace_back(std::make_shared<Entity>(label, element));
  // this->elements->emplace_back({label, element});
}

/*****************************/
template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::append(T &&element,
                                                std::string &&label) noexcept {
  this->elements->emplace_back(
      std::make_shared<Entity>(std::move(label), std::move(element)));
  // this->elements->emplace_back({std::move(label), std::move(element)});
}

template <typename T, typename EntityType>
inline void
BasicManager<T, EntityType>::append(const std::initializer_list<Entity> &list) {
  for (const auto &index : list) {
    this->elements->emplace_back(std::make_shared<Entity>(index));
    // this->elements->push_back(index);
  }
}

template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::remove(const std::string &label) {
  if (!isExistElement(label))
    throw AsciiBasicException("确定label是否正确，不存在该元素!");

  const int index = getElementIndex(label);
  this->elements->erase(elements->begin() + index);
  // this->elements->erase(index);
}

/***************************************/
template <typename T, typename EntityType>
inline void BasicManager<T, EntityType>::insert(int index,
                                                const Entity &element) {
  if (index <= 0 || index > elements->size())
    throw AsciiBasicException("index不合法!");

  elements->emplace(elements->begin() + index - 1,
                    std::make_shared<Entity>(element));
  // this->elements->emplace(index - 1, element);
}

template <typename T, typename EntityType>
inline EntityType &
BasicManager<T, EntityType>::operator[](const std::string &label) noexcept {
  for (auto &index : *elements) {
    if (label == index->label)
      return *index;
  }
  append(T(), label);
  return *((*elements)[size() - 1]);
  // return (*elements)[size() - 1];
}

template <typename T, typename EntityType>
inline EntityType &BasicManager<T, EntityType>::operator[](int index) {
  if (index < 0)
    throw AsciiBasicException(ArrayOverflow);

  // 当index超出manager的元素个数时，自动扩充（扩充元素的label为自身index）
  if (index >= elements->size()) {
    const size_t size = index + 1 - elements->size();
    for (size_t i = 0; i < size; i++) {
      append(T(), std::to_string(i));
    }
    return *((*elements)[index]);
    // return (*elements)[index];
  }
  return *((*elements)[index]);
  // return (*elements)[index];
}

template <typename T, typename EntityType>
inline const EntityType &
BasicManager<T, EntityType>::operator[](const std::string &label) const {
  for (const auto &index : *elements) {
    if (label == index->label)
      return *index;
  }
  throw AsciiBasicException("没有这样的元素");
}

template <typename T, typename EntityType>
inline const EntityType &
BasicManager<T, EntityType>::operator[](int index) const {
  if (index < 0 || index >= elements->size())
    throw AsciiBasicException(ArrayOverflow);

  return *((*elements)[index]);
  // return (*elements)[index];
}

template <typename T, typename EntityType>
inline BasicManager<T, EntityType> &BasicManager<T, EntityType>::operator=(
    const BasicManager<T, EntityType> &mngr) {
  *this->elements = *mngr.elements;
  return *this;
}

template <typename T, typename EntityType>
inline BasicManager<T, EntityType> &BasicManager<T, EntityType>::operator=(
    BasicManager<T, EntityType> &&mngr) noexcept {
  this->elements = std::move(mngr.elements);
  mngr.elements = nullptr;

  return *this;
}

template <typename T, typename EntityType>
inline std::string BasicManager<T, EntityType>::getSerializeStr() const {
  return serializeType(*elements);
}

template <typename T, typename EntityType>
inline void
BasicManager<T, EntityType>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  if (tokens.size() < 1)
    throw AsciiBasicException(FileFormatException);

  this->elements = std::make_unique<Elements>();

  const auto tokens_elements = bracketMatch(tokens[0]);

  /* std::cout << tokens_elements.size() << std::endl;
   for (auto &index : tokens_elements) {
     std::cout << index << std::endl;
   }*/

  for (const auto &index : tokens_elements) {
    // buffer的声明不能放倒for循环外面，因为deserializeType函数会重新为buffer申请内存
    Entity buffer;
    deserializeType(buffer, index);
    this->elements->emplace_back(std::make_shared<Entity>(std::move(buffer)));
    // this->elements->emplace_back(std::move(buffer));
  }
}
} // namespace AsciiTools