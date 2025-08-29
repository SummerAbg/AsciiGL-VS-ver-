#pragma once

#include "at_basicobject.h"
#include "at_serialization.h"
#include <type_traits>

namespace AsciiTools {
template <typename T> class PtrVector : public AsciiBasicObject {
public:
  using Elements = std::vector<std::shared_ptr<T>>;
  using pElements = std::unique_ptr<Elements>;

  PtrVector() { this->elements = std::make_unique<Elements>(); }
  PtrVector(size_t size, bool isNullptr) {
    this->elements = std::make_unique<Elements>(
        size, isNullptr ? nullptr : std::make_shared<T>());
  }

  PtrVector(const std::initializer_list<T> &elements) : PtrVector() {
    for (const auto &index : elements) {
      this->elements->emplace_back(std::make_shared<T>(index));
    }
  }

  PtrVector(const PtrVector &vec) : PtrVector() {
    for (const auto &index : vec) {
      auto element = (index == nullptr) ? nullptr : std::make_shared<T>(*index);
      this->elements->emplace_back(element);
    }
  }

  PtrVector(PtrVector &&vec) noexcept {
    this->elements = std::move(vec.elements);
    vec.elements = nullptr;
  }

  auto begin() const noexcept { return this->elements->begin(); }
  auto end() const noexcept { return this->elements->end(); }

  size_t size() const noexcept { return this->elements->size(); }

  bool isFlow(size_t index) const noexcept {
    return (index < 0 || index >= size());
  }

  bool isNullptr(size_t index) const noexcept {
    return (*this->elements)[index] == nullptr;
  }

  void init(size_t index) { (*this->elements)[index] = std::make_shared<T>(); }

  void init(size_t index, const T &element) {
    (*this->elements)[index] = std::make_shared<T>(element);
  }

  void init(size_t index, T &&element) {
    (*this->elements)[index] = std::make_shared<T>(std::move(element));
  }

  T &operator[](size_t index) {
    if (isFlow(index))
      throw AsciiBasicException(ArrayOverflow);

    if (isNullptr(index))
      (*this->elements)[index] = std::make_shared<T>();
    return *(*this->elements)[index];
  }

  const T &operator[](size_t index) const {
    if (isFlow(index))
      throw AsciiBasicException(ArrayOverflow);

    if (isNullptr(index))
      throw AsciiBasicException(NullptrException);
    return *(*this->elements)[index];
  }

  PtrVector &operator=(const PtrVector &vec) {
    this->elements->clear();
    for (const auto &index : vec) {
      auto element = (index == nullptr) ? nullptr : std::make_shared<T>(*index);
      this->elements->emplace_back(element);
    }
    return *this;
  }

  PtrVector &operator=(PtrVector &&vec) noexcept {
    this->elements = std::move(vec.elements);
    /* for (const auto &index : vec) {
      auto element = (index == nullptr) ? nullptr : std::make_shared<T>(*index);
      this->elements->emplace_back(element);
    }*/
    return *this;
  }

  void clear() noexcept { this->elements->clear(); }

  void push_back() { this->elements->emplace_back(nullptr); }

  void push_back(const T &element) {
    this->elements->emplace_back(std::make_shared<T>(element));
  }

  void push_back(std::shared_ptr<T> &&element) noexcept {
    this->elements->emplace_back(std::move(element));
  }

  void emplace_back(std::shared_ptr<T> &&element) noexcept {
    this->elements->emplace_back(std::move(element));
  }

  void emplace_back(T &&element) noexcept {
    this->elements->emplace_back(std::make_shared<T>(std::move(element)));
  }

  void emplace(T &&element) noexcept {
    this->elements->emplace_back(std::make_shared<T>(std::move(element)));
  }

  void emplace(int index, T &&element) noexcept {
    this->elements->emplace(this->elements->begin() + index,
                            std::make_shared<T>(std::move(element)));
  }

  void emplace(int index, const T &element) noexcept {
    this->elements->emplace(this->elements->begin() + index,
                            std::make_shared<T>(element));
  }

  void erase(int index) noexcept(std::is_nothrow_move_assignable_v<T>) {
    this->elements->erase(this->elements->begin() + index);
  }

  bool operator==(const PtrVector &vec) const noexcept {
    if (this->elements->size() != vec.elements->size())
      return false;

    for (auto it_this = this->elements->begin(), it_vec = vec.elements->begin();
         it_this != this->elements->end(); ++it_this, ++it_vec) {
      if (*it_this == nullptr || *it_vec == nullptr) {
        if (*it_this == nullptr && *it_vec == nullptr)
          continue;
        return false;
      }
      if (**it_this != **it_vec)
        return false;
    }
    return true;
  }

  bool operator!=(const PtrVector &vec) const noexcept {
    return !(*this == vec);
  }

  void info() const override;
  std::string toString() const override;

protected:
  // 获取序列化字符串
  std::string getSerializeStr() const override;
  // 加载序列化字符串
  void loadSerializeStr(const std::string &str) override;

private:
  pElements elements;
};

template <typename T> inline void PtrVector<T>::info() const {
  std::cout << "PtrVector对象" << std::endl;
  std::cout << "size:" << this->size() << std::endl;
  std::cout << "elements:" << std::endl;

  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *this) {
    type_decorator.init(*index);
    std::cout << type_decorator.toTargetType() << "\t";
  }
  std::cout << std::endl;
}

template <typename T> inline std::string PtrVector<T>::toString() const {
  std::string ret;
  TypeDecorator<std::string, T> type_decorator;
  for (const auto &index : *this) {
    type_decorator.init(*index);
    ret += type_decorator.toTargetType() + " ";
  }
  return ret;
}

template <typename T> inline std::string PtrVector<T>::getSerializeStr() const {
  std::string ret;
  for (const auto &index : *this) {
    ret += serializeType(*index);
  }
  return ret;
}

//**此函数可能有一些运行时的问题**
template <typename T>
inline void PtrVector<T>::loadSerializeStr(const std::string &str) {
  auto tokens = bracketMatch(str);
  for (const auto &index : tokens) {
    std::shared_ptr<T> object = std::make_shared<T>();
    deserializeType(*object, index);
    this->elements->emplace_back(object);
  }
}
} // namespace AsciiTools