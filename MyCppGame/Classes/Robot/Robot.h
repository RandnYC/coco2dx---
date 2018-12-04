#pragma once

#include "headfileSet.h"
#include "Snake\Snake.h"
using namespace cocos2d;
using namespace std;

class Robot :public Snake
{
	//enum judgementTag { safe, warning, dangerous };
	Size area;
	int cnt;	//�Ƿ�����
	float risk;
	RotateBy* last_action;	//��¼����ת������ת

	typedef pair<Vec2, degree> PR;
	typedef pair<float, float>PFF;

public:

	Robot(const Size&);

	static Robot* create(const Size&);

	void disappear() override;

	virtual void move();
	virtual void moveTowardCenter();
	virtual void headForFood(const BodyNode*);
	virtual BodyNode* getFoodInfomation(const list<BodyNode*>&)const;
	virtual bool evalueFood(const BodyNode*)const;

	virtual Action* runAction(RotateBy* , int);	//����ԭ����runAction

	virtual float evalueWall(degree,float =0.0) const;	//��������
	//virtual float evalueMyself(const Vec2&) const;

	virtual void predictPosition(degree, queue<PR>&, float = 0.0)const;
	virtual PFF distanceWall(degree , float = 0.0) const;	//Ԥ���ƶ�����v֮�����������Ƕ�ǽ�ľ���
	virtual float distanceMyself(degree , float = 0.0) const;	//Ԥ���ƶ�����v֮��ͷ���������ڵ�ľ���
	void update();
	void update(float)override;
};