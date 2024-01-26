#pragma once

#include "AsciiBasicString.h"

// �����ַ���������
class AsciiBasicCanvas : public AsciiBasicObject {
public:
  using BlockData = std::vector<AsciiBasicString>;

  // ��������ַ�������
  AsciiBasicCanvas();
  AsciiBasicCanvas(int length, int width,
                   const AsciiBasicString &fill = TRPRSTR);
  AsciiBasicCanvas(const std::string &canvasFilePath);

  // ��ȡͷβ��ַ�ĺ���(Ϊ���ܹ�ʹ��c++11��������)
  auto begin() const { return bDatas.begin(); }
  auto end() const { return bDatas.end(); }

  // �����Ϣ(DEBUG)
  void info() const;
  // ��ȡ������ɵ��ַ���
  std::string toString() const;

  // ���û�����ָ�����������
  void setAsciiBasicCanvasData(Coordinate2D coord,
                               const AsciiBasicString &fill);
  // ��ȡ������ָ�����������(ʧ��ʱ���ؿ��ַ���)
  AsciiBasicString getAsciiBasicCanvasData(Coordinate2D coord) const;

  // ��ȡ������ɵ�AsciiBasicString�ַ���
  AsciiBasicString getAsciiBasicString() const;

  // ��ȡ��������
  int getLength() const { return length; }
  // ��ȡ�������
  int getWidth() const { return width; }
  // ��ȡ�鳤��
  int getBlockLength() const { return blockLength; }
  // ��ȡĬ������ַ���
  AsciiBasicString getFill() const { return defaultFill; }

  // ���ļ�����ʽ���滭��
  void save(const std::string &canvasFilePath) const;
  // ���ļ�����ʽ���ػ���
  void load(const std::string &canvasFilePath);

  // ��ջ�������(flagΪ��ʱ,�����������,flagΪ��ʱ������ָ�Ĭ������)
  void clear(bool flag = true);

  // չʾ����
  void show() const;

  // �ж������Ƿ�Ϸ�
  bool isCoordinateLegality(Coordinate2D coord) const;

  // ���������
  virtual bool operator==(const AsciiBasicCanvas &canvas) const;
  virtual bool operator!=(const AsciiBasicCanvas &canvas) const;

private:
  std::string getSerializeStr() const;
  void loadSerializeStr(const std::string &str);

private:
  int length;      // ��������
  int width;       // �������
  int blockLength; // �鳤��(�������ȵ�Ԫ)

  AsciiBasicString defaultFill; // ����Ĭ������ַ���

  BlockData bDatas; // ����������
};