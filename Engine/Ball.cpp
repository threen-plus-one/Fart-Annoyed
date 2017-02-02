#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball( const Vec2& pos_in,const Vec2& vel_in )
	:
	pos( pos_in ),
	vel( vel_in )
{
}

void Ball::Update( float dt )
{
	pos += vel * dt;
}

void Ball::Draw( Graphics& gfx ) const
{
	SpriteCodex::DrawBall( pos,gfx );
}

bool Ball::DoWallCollision( const RectF& walls )
{
	bool collided = false;

	const RectF bounds = GetBounds();
	
	if( bounds.top < walls.top )
	{
		pos.y += walls.top - bounds.top;
		ReboundY();
		collided = true;
	}
	else if( bounds.bottom > walls.bottom )
	{
		pos.y -= bounds.bottom - walls.bottom;
		ReboundY();
		collided = true;
	}

	if( bounds.left < walls.left )
	{
		pos.x += walls.left - bounds.left;
		ReboundX();
		collided = true;
	}
	else if( bounds.right > walls.right )
	{
		pos.x -= bounds.right - walls.right;
		ReboundX();
		collided = true;
	}

	return collided;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetBounds() const
{
	return RectF::FromCentre( pos,RADIUS,RADIUS );
}