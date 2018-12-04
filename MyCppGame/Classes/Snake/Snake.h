#pragma once

#include "headfileSet.h"
#include "BodyNode.h"

using namespace cocos2d;

class Snake : public Node
{
protected:

	Vector<BodyNode*> body;
	void bodyConnect();	//�����ν�����ڵ�
	Color4F color;
	int cnt;	//ʳ��
public:
	Snake();	//���ڳ�ʼ��
	static Snake* create();
	void update(float) override;
	void update();
	void setPosition(const Vec2&) override;
	const Vec2& getPosition()const override;
	Action* runAction(Action*) override;
	void setRotation(float) override;
	float getRotation() const override;
	void setScale(float) override;
	float getScale() const override;

	void removeBody(int = 1);
	void addBody(int= 1);
	void reset();
	void setBodySize(int);
	BodyNode* getHead()const;

	int bodyNumber()const;
	virtual const Vec2 getCenterPosition()const;
	virtual float getLength()const;
	virtual float getRadius()const;
	virtual bool collide(const Snake*)const;	//�ж��Լ��Ƿ�ײ���Է�
	virtual bool collide()const;	//�ж��Լ��Ƿ�ײ���Լ�
	virtual bool eatFood(BodyNode*);
	virtual bool outofRange(const Size&)const;	//�ж��Ƿ����
	virtual void disappear();

};