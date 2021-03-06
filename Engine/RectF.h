#pragma once

#include "Vec2.h"

class RectF
{
public:
	float top;
	float bottom;
	float left;
	float right;

	RectF() = default;
	RectF( float top,float bottom,float left,float right );
	RectF( const Vec2& topLeft,const Vec2& bottomRight );
	RectF( const Vec2& topleft,float width,float height );

	bool Intersects( const RectF& other ) const;
	RectF GetExpanded( float magnitude ) const;
	RectF& Expand( float magnitude );
	Vec2 GetCentre() const;

	static RectF FromCentre( const Vec2& centre,float halfWidth,float halfHeight );
};