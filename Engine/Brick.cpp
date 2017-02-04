#include "Brick.h"
#include <cassert>

Brick::Brick( const RectF& rect_in,Color color_in )
	:
	rect( rect_in ),
	color( color_in )
{
}

bool Brick::CheckBallCollision( const Ball& ball ) const
{
	return !destroyed && rect.Intersects( ball.GetBounds() );
}

void Brick::ExcecuteBallCollision( Ball& ball )
{
	assert( CheckBallCollision( ball ) );

	const Vec2 ballPos = ball.GetPosition();
	if( ballPos.x >= rect.left && ballPos.x <= rect.right )
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	
	destroyed = true;
}

void Brick::Draw( Graphics& gfx ) const
{
	if( !destroyed )
	{
		gfx.DrawRect( rect.GetExpanded( -GRID_PADDING ),color );
	}
}

const RectF& Brick::GetBounds() const
{
	return rect;
}
