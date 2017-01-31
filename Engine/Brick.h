#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"

class Brick
{
	RectF rect;
	Color color;

	bool destroyed;

public:
	Brick( const RectF& rect,Color color );
	void Draw( Graphics& gfx ) const;
};