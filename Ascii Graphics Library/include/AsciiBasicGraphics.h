#pragma once

#include "AsciiBasicLayerMngr.h"

// ��ȡָ������Ļ���(ʧ��ʱ����һ���յĻ����ַ�������)
AsciiBasicCanvas getCanvas(const AsciiBasicCanvas &canvas, Coordinate2D coord1,
                           Coordinate2D coord2);

// �ص���������
// �Ὣcanvas�ص���target��(x,y)�ϣ����ջ�����С��targetΪ��׼
AsciiBasicCanvas overlapCanvas(const AsciiBasicCanvas &canvas,
                               const AsciiBasicCanvas &target,
                               Coordinate2D coord);


// �����ı�(�����ͼ��,��ԭ�л��������޸�)
void setText(AsciiBasicCanvas &canvas, Coordinate2D coord,
             const AsciiBasicString &text);

// �����ı�(�����ͼ��,��ԭ��ͼ������޸�)
// ��ϸ˵��:��ĳͼ�㱻���øú���ʱ��ͼ��ԭ�е����ݽ������ǣ�
void setText(AsciiBasicLayer &layer, Coordinate2D coord,
             const AsciiBasicString &text);

// �����ı�(���ͼ��)
// ��ϸ˵��:��ĳ����ͼ�㱻�ú�������ʱ�����������ͼ��Ĳ���
void setText(AsciiBasicLayerMngr &mngr, Coordinate2D coord,
             const AsciiBasicString &text,
             const std::string &layerName = "textLayer");


// ���û����߿�
void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str);

// �Ƚ�target��canvas�Ĳ�ͬ����������target��Χ�в�ͬ����Point2D  <Warning>
std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas);

// ��������(levelΪ���ƾ�׼�ȣ�Խ��Խ�ã�level����С��-15)
void setLine(AsciiBasicCanvas &canvas, Coordinate2D coord1, Coordinate2D coord2,
             const AsciiBasicString &str, int level = 1);

// ��ӳ����
void reflect(AsciiBasicCanvas &canvas);

#if defined(_WIN64) || defined(_WIN32)
// ����WinAPI����ѡ�����������(�ɴ���������)
// isCleanΪtrueʱ����ջ�����
void WinAPIDraw(const AsciiBasicCanvas &canvas, bool isClean = false);

// ���ع��
void hideCursor();

#endif