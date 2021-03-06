/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "FrameTimer.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel( float dt );
	/********************************/
	/*  User Functions              */
	void DoBrickCollision();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	static constexpr float TIMESTEP = 0.0025f;

	static constexpr int BRICKS_ACROSS = 18;
	static constexpr int BRICKS_DOWN = 4;
	static constexpr int NUM_BRICKS = BRICKS_ACROSS * BRICKS_DOWN;

	static constexpr float BRICK_WIDTH = 40.0f;
	static constexpr float BRICK_HEIGHT = 24.0f;

	Color borderColor = Colors::MakeRGB( 0u,0u,127u );

	bool gameOver = false;

	FrameTimer ft;
	
	RectF walls;
	Ball ball;
	Brick bricks[ NUM_BRICKS ];
	Paddle pad;

	Sound soundPad;
	Sound soundBrick;
	/********************************/
};