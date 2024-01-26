#include "AsciiBasicObject.h"

std::string serialize(const AsciiBasicObject *obj) {
  if (obj == nullptr) {
    throw AsciiBasicError(__FUNC__, NotInitialized);
  }
  return obj->getSerializeStr();
}

void deserialize(AsciiBasicObject *obj, const std::string &str) {
  if (obj == nullptr) {
    throw AsciiBasicError(__FUNC__, NotInitialized);
  }
  obj->loadSerializeStr(str);
}
