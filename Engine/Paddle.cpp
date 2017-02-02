#include "Paddle.h"

Paddle::Paddle( const Vec2& pos_in,float halfWidth_in,float halfHeight_in )
	:
	pos( pos_in ),
	halfWidth( halfWidth_in ),
	halfHeight( halfHeight_in )
{
}

void Paddle::Update( Keyboard& kbd,float dt )
{
	if( kbd.KeyIsPressed( VK_LEFT ) )
	{
		pos.x -= SPEED * dt;
	}

	if( kbd.KeyIsPressed( VK_RIGHT ) )
	{
		pos.x += SPEED * dt;
	}
}

void Paddle::Draw( Graphics& gfx ) const
{
	RectF rect = GetBounds();
	gfx.DrawRect( rect,wingColor );
	rect.left += WING_WIDTH;
	rect.right -= WING_WIDTH;
	gfx.DrawRect( rect,color );
}

bool Paddle::DoBallCollision( Ball& ball ) const
{
	// you were doing ball.GetBounds instead of ball.GetBounds()
	if( GetBounds().Intersects( ball.GetBounds() ) )
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

void Paddle::DoWallCollision( const RectF& walls )
{
	const RectF rect = GetBounds();

	if( rect.left < walls.left )
	{
		pos.x += walls.left - rect.left;
	}
	else if( rect.right > walls.right )
	{
		pos.x -= rect.right - walls.right;
	}
}

RectF Paddle::GetBounds() const
{
	return RectF::FromCentre( pos,halfWidth,halfHeight );
}
