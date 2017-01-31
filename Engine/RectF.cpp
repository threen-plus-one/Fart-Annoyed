#include "RectF.h"

RectF::RectF( float top_in,float bottom_in,float left_in,float right_in )
	:
	top( top_in ),
	bottom( bottom_in ),
	left( left_in ),
	right( right_in )
{
}

RectF::RectF( const Vec2& topLeft,const Vec2& bottomRight )
	:
	RectF( topLeft.y,bottomRight.y,topLeft.x,bottomRight.x )
{
}

RectF::RectF( const Vec2& topleft,float width,float height )
	:
	RectF( topleft,topleft + Vec2( width,height ) )
{
}

bool RectF::Intersects( const RectF& other ) const
{
	return
		right > other.left &&
		left < other.right &&
		bottom > other.top &&
		top < other.bottom;
}
