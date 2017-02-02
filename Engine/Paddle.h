#pragma once

#include "Vec2.h"
#include "RectF.h"
#include "Colors.h"
#include "Keyboard.h"
#include "Ball.h"

class Paddle
{
	static constexpr float SPEED = 200.0f;
	static constexpr float WING_WIDTH = 5.0f;

	Vec2 pos;
	float halfWidth;
	float halfHeight;

	Color color = Colors::White;
	Color wingColor = Colors::Red;

public:
	Paddle( const Vec2& pos,float halfWidth,float halfHeight );

	void Update( Keyboard& kbd,float dt );
	void Draw( Graphics& gfx ) const;

	bool DoBallCollision( Ball& ball ) const;
	void DoWallCollision( const RectF& walls );

	RectF GetBounds() const;
};