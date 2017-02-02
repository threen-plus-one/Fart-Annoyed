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

RectF RectF::GetExpanded( float magnitude ) const
{
	return RectF( top - magnitude / 2,bottom + magnitude,left - magnitude / 2, right + magnitude );
}

RectF& RectF::Expand( float magnitude )
{
	return *this = GetExpanded( magnitude );
}

RectF RectF::FromCentre( const Vec2& centre,float halfWidth,float halfHeight )
{
	const Vec2 half( halfWidth,halfHeight );
	return RectF( centre - half,centre + half );
}
