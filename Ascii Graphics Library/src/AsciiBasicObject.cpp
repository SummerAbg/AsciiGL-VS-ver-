#include "AsciiBasicObject.h"

std::string serialize(const AsciiBasicObject *obj) {
  if (obj == nullptr) {
    throw AsciiBasicError("serialize()", NotInitialized);
  }
  return obj->getSerializeStr();
}

void deserialize(AsciiBasicObject *obj, const std::string &str) {
  if (obj == nullptr) {
    throw AsciiBasicError("deserialize()", NotInitialized);
  }
  obj->loadSerializeStr(str);
}
