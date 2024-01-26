#pragma once

#include "AsciiBasicLayer.h"

// �ַ�����ͼ���������
class AsciiBasicLayerMngr {
public:
  using DataType = std::vector<AsciiBasicLayer>;

  // �����ַ�����ͼ�������
  AsciiBasicLayerMngr() {}
  AsciiBasicLayerMngr(const DataType &layers) { this->layers = layers; }
  AsciiBasicLayerMngr(int length, int width);

  // ��ȡͷβ��ַ�ĺ���(Ϊ���ܹ�ʹ��c++11��������)
  auto begin() const { return layers.begin(); }
  auto end() const { return layers.end(); }

  // ���ͼ��
  void addLayer(const AsciiBasicLayer &layer) { layers.push_back(layer); }
  void addLayer(const DataType &layers);

  // ɾ��ͼ��
  void deleteLayer(const std::string &name);

  // ����ͼ��(ʧ��ʱ��ʵ�ֲ��빦��)
  void insertLayer(int layerCnt, const AsciiBasicLayer &layer);
  void insertLayer(int layerCnt, const DataType &layers);

  // ��ȡ��ͼ��ϲ������ɵĻ���(ʧ��ʱ���ؿջ���)
  AsciiBasicCanvas getCanvas() const;
  AsciiBasicCanvas getCanvas(const std::string &name) const;

  // �±����������(��ȡ/�޸�ָ�����Ƶ�ͼ��)[ʧ��ʱ���ص�һ��ͼ��]
  AsciiBasicLayer &operator[](const std::string &name);
  AsciiBasicLayer &operator[](int index);
  // �±����������(��ȡָ�����Ƶ�ͼ��)[ʧ��ʱ���ص�һ��ͼ��]
  const AsciiBasicLayer &operator[](const std::string &name) const;
  const AsciiBasicLayer &operator[](int index) const;
  // �±����������(==)
  bool operator==(const AsciiBasicLayerMngr &mngr) const;
  bool operator!=(const AsciiBasicLayerMngr &mngr) const;

  // ��ȡ������ͼ����
  int size() const { return static_cast<int>(layers.size()); }

  // ��ȡ������������ͼ��
  DataType getLayers() const;

  // �ж��Ƿ����ָ��ͼ��
  bool isExistLayer(const std::string &name) const;
  // ��ȡָ��ͼ�����ڲ���(ʧ��ʱ����-1)
  int getLayerCount(const std::string &name) const;

private:
  DataType layers;
};