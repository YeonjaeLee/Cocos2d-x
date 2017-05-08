#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class AstarItem : public Node
{
public:
	cocos2d::Vec2 mPos;	// ��ǥ
	int g;				// ���������κ����� �Ÿ�
	int h;				// ��ǥ�������� �Ÿ�
	int f;				// �Ÿ��� �� : f = g + h
	cocos2d::Vec2 pPos;	// �θ���ǥ

	AstarItem()
	{
		g = 0;
		h = 0;
		f = 0;
	}
};