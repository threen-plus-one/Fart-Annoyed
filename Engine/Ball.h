#pragma once

#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"

class Ball
{
	static constexpr float RADIUS = 7.0f;
	static constexpr float SPEED = 400.0f;

	Vec2 pos;
	Vec2 vel;

public:
	Ball( const Vec2& pos,const Vec2& vel );
	
	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	bool DoWallCollision( const RectF& walls );
	void ReboundX();
	void ReboundY();
	void ReboundYPad( const Vec2& padCentre );

	RectF GetBounds() const;
	const Vec2& GetPosition() const;
	const Vec2& GetVelocity() const;
};
