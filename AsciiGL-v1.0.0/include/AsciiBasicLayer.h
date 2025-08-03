#pragma once

#include "AsciiBasicCanvas.h"

// �ַ�����ͼ����
class AsciiBasicLayer : public AsciiBasicCanvas {
public:
  // �����ַ�����ͼ��
  AsciiBasicLayer();
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coordinate2D coord);
  AsciiBasicLayer(const AsciiBasicCanvas &canvas, Coordinate2D coord,
                  const std::string &name);

  // ����ͼ���л���������
  void setCoordinate(Coordinate2D coord) { this->coord = coord; }
  // ��ȡͼ���л���������
  Coordinate2D getCoordinate() const { return coord; }

  // ��������
  void setName(const std::string &name) { this->name = name; }
  // ��ȡ����
  std::string getName() const { return name; }

private:
  Coordinate2D coord; // ����
  std::string name;   // ����
};