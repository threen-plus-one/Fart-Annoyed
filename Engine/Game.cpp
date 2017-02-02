/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	walls( Vec2( 0.0f,0.0f ),Vec2( 799.0f,599.0f ) ),
	ball( Vec2( 400.0f,400.0f ),Vec2( 400.0f,400.0f ) ),
	soundPad( L"Sounds\\arkpad.wav" ),
	soundBrick( L"Sounds\\arkbrick.wav" )
{
	const Vec2 topLeft( 40.0f,40.0f );
	const Color colors[ BRICKS_DOWN ] = {
		Colors::Red,
		Colors::Green,
		Colors::Blue,
		Colors::Cyan
	};

	int i = 0;
	for( int y = 0; y < BRICKS_DOWN; ++y )
	{
		for( int x = 0; x < BRICKS_ACROSS; ++x )
		{
			const Vec2 brickTopLeft = topLeft + Vec2( float( x ) * BRICK_WIDTH,float( y ) * BRICK_HEIGHT );
			bricks[ i ] = Brick( RectF( brickTopLeft,BRICK_WIDTH,BRICK_HEIGHT ),colors[ y ] );
			++i;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	ball.Update( dt );
	if( ball.DoWallCollision( walls ) )
	{
		soundPad.Play();
	}

	for( Brick& b : bricks )
	{
		if( b.DoBallCollision( ball ) )
		{
			soundBrick.Play();
			return;
		}
	}
}

void Game::ComposeFrame()
{
	ball.Draw( gfx );
	for( const Brick& b : bricks )
	{
		b.Draw( gfx );
	}
}
