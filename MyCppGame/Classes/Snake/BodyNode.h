#pragma once

#include "headfileSet.h"
using namespace cocos2d;

class BodyNode : public Node
{
	const Size& getContentSize() const override;
	void setContentSize(const Size&) override;
public:
	Vec2 front, back;	//����ڵ�Ķ�����β��
	float radius;	//����ڵ�İ뾶

	static BodyNode* create(Color4F);

	void setPosition(const Vec2&) override;
	void setRotation(float) override;
	float getRotation() const override ;
	void setScale(float) override;
	float getScale()const override;
	void update(float) override;
	
	virtual float getDistance(BodyNode*)const;
	virtual void update();
	virtual void attachTo(BodyNode*);
	virtual bool collide(const BodyNode*)const;
};
