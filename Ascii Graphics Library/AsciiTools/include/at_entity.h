#pragma once

#include "at_basicobject.h"
#include "at_typeconvert.h"
#include <memory>
#include <string>

namespace AsciiTools {
template <typename T> struct Entity : public AsciiBasicObject {
  std::string label;
  std::shared_ptr<T> body;

  Entity() { this->body = std::make_shared<T>(); }

  Entity(const std::string &label, const T &body = T()) {
    this->label = label;
    this->body = std::make_shared<T>(body);
  }

  Entity(std::string &&label, T &&body) noexcept {
    this->label = std::move(label);
    this->body = std::make_shared<T>(std::move(body));
  }

  Entity(std::string &&label, const T &body) {
    this->label = std::move(label);
    this->body = std::make_shared<T>(body);
  }

  Entity(const Entity<T> &entity) : Entity<T>() {
    this->label = entity.label;
    *this->body = *entity.body;
  }

  Entity(Entity<T> &&entity) noexcept {
    this->label = std::move(entity.label);
    this->body = std::move(entity.body);
    entity.body = nullptr;
  }

  virtual ~Entity() {}

  virtual void info() const override;
  virtual std::string toString() const override;

  Entity<T> &operator=(const Entity<T> &entity) {
    this->label = entity.label;
    this->body = entity.body;
    return *this;
  }

  Entity<T> &operator=(Entity<T> &&entity) noexcept {
    this->label = std::move(entity.label);
    this->body = std::move(entity.body);
    entity.body = nullptr;

    return *this;
  }

  bool operator==(const Entity<T> &entity) const noexcept {
    return (this->label == entity.label && *this->body == *entity.body);
  }

  bool operator!=(const Entity<T> &entity) const noexcept {
    return !(*this == entity);
  }

protected:
  // 获取序列化字符串
  virtual std::string getSerializeStr() const override;
  // 加载序列化字符串
  virtual void loadSerializeStr(const std::string &str) override;
};

template <typename T> inline void Entity<T>::info() const {
  std::cout << "Entity对象" << std::endl;
  std::cout << "label:" << this->label << std::endl;
}

template <typename T> inline std::string Entity<T>::toString() const {
  TypeDecorator<std::string, T> type_decorator(*this->body);
  return type_decorator.toTargetType();
}

template <typename T> inline std::string Entity<T>::getSerializeStr() const {
  // return serializeType(label, *body);
  // return serialize(*body);
  return "null: Entity<T> （序列化）待开发中...";
}

template <typename T>
inline void Entity<T>::loadSerializeStr(const std::string &str) {
  const auto tokens = bracketMatch(str);
  //  if (tokens.size() < 2)
  if (tokens.size() < 1)
    throw AsciiBasicException(FileFormatException);

  this->body = std::make_shared<T>();

  // deserializeType(this->label, tokens[0]);
  // deserializeType(*this->body, tokens[1]);
  /* std::cout << tokens.size() << std::endl;
  for (auto &index : tokens) {
    std::cout << index << std::endl;
  }*/

  // 此条目前不能注释掉，因为不管是entity的还是其派生的实例化对象，只有这唯一一次初始化label的机会，
  // 否则当通过label在管理器遍历对象时会找不到并创建新对象，造成巨大开销
  deserializeType(this->label, tokens[0]);
  // deserializeType(*this->body, tokens[0]);
  deserializeType(*this->body, str);
  // std::cout << "null: Entity<T> (反序列化)待开发中...." << std::endl;
}
} // namespace AsciiTools