#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
	static constexpr float GRID_PADDING = 1.0f;

	RectF rect;
	Color color;

	bool destroyed = false;

public:
	Brick() = default;
	Brick( const RectF& rect,Color color );

	bool DoBallCollision( Ball& ball );

	void Draw( Graphics& gfx ) const;
};