#pragma once

#include "headfileSet.h"

namespace cocos2d
{
	class degree
	{
		float d;
	public:
		degree(const Vec2&);
		degree(float = 0);
		
		static float standardize(float);
		virtual operator float() const;
		virtual operator Vec2() const;	//תΪ��λ����
		virtual degree angle(const degree) const;
	};
}