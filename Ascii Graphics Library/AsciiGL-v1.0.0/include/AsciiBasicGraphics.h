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

// �����ı�
void setText(AsciiBasicCanvas &canvas, Coordinate2D coord,
             const AsciiBasicString &text);

// ���û����߿�
void setBorder(AsciiBasicCanvas &canvas, const AsciiBasicString &str);

// �Ƚ�target��canvas�Ĳ�ͬ����������target��Χ�в�ͬ����Point2D  <Warning>
std::vector<Point2D> compareCanvas(const AsciiBasicCanvas &target,
                                   const AsciiBasicCanvas &canvas);

// ��������(����)
void setLine(AsciiBasicCanvas &canvas, Coordinate2D coord1, Coordinate2D coord2,
             const AsciiBasicString &str);

// ����WinAPI�������(�ɴ���������)
void WinAPIDraw(const AsciiBasicCanvas &canvas);