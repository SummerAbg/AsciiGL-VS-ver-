#include "agl_Basic.h"
#include "at_Exception.h"

namespace AsciiGL {
double getY(Coord2d coordA, Coord2d coordB, double x) {
  const double y_ = abs(coordA.y - coordB.y) + 1;
  const double x_ = abs(coordA.x - coordB.x) + 1;
  const double k = y_ / x_;

  if (coordA.y < coordB.y) {
    return k * x;
  } else if (coordA.y > coordB.y) {
    return -k * x;
  } else { // coordA.y == coordB.y
    return 0;
  }
}

std::string makeName(const std::string &prefix) {
  static std::vector<std::string> nameLib;
  static std::vector<int> numbers;

  // ��ȡָ��Ԫ�ص��±�
  const int index = getIndex(nameLib, prefix);

  // ��prefix�����ֿ��е�����һ��Ԫ����ͬʱ��������Ԫ���±���ͬ��numbersԪ���Լ�
  if (isExist(nameLib, prefix)) {
    numbers[index]++;
  } else {
    // �����ֿ���û����prefix��ͬ��Ԫ�أ���ô��Ӹ�Ԫ��
    numbers.emplace_back(0);
    numbers.emplace_back(0);
  }
  // auto name = spliceString("_", prefix, numbers[index]);
  std::string name = prefix + "_" + std::to_string(numbers[index]);

  nameLib.emplace_back(prefix);
  nameLib.emplace_back(name);

  return name;
}

int getBlockNumber(size_t strSize, size_t blockLength) {
  double d_str_size = static_cast<double>(strSize);
  double d_block_length = static_cast<double>(blockLength);

  if (strSize < blockLength) {
    return 1;
  } else {
    return static_cast<int>(ceil(d_str_size / d_block_length));
  }
}

std::string getFileData(const std::string &path) {
  std::string ret;
  std::fstream reader(path);
  std::string buffer;

  if (!reader.is_open()) {
    throw AsciiBasicException(__FUNC__, FileNotExist);
  }

  while (std::getline(reader, buffer)) {
    ret += buffer + "\n";
  }

  reader.close();
  return ret;
}
} // namespace AsciiGL