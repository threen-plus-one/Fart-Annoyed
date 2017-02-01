#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
	RectF rect;
	Color color;

	bool destroyed = false;

public:
	Brick( const RectF& rect,Color color );
	void Draw( Graphics& gfx ) const;

	bool DoBallCollision( Ball& ball );
};