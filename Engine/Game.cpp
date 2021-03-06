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
	walls( Vec2( 40.0f,40.0f ),Vec2( 759.0f,559.0f ) ),
	ball( Vec2( 300.0f,400.0f ),Vec2( 1.0f,1.0f ) ),
	pad( Vec2( 400.0f,500.0f ),50.0f,7.0f ),
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
	float elapsedTime = ft.Mark();
	while( elapsedTime > 0.0f )
	{
		const float dt = (TIMESTEP <= elapsedTime)? TIMESTEP : elapsedTime;
		UpdateModel( dt );
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{
	if( !gameOver )
	{
		ball.Update( dt );
		pad.Update( wnd.kbd,dt );

		if( ball.DoWallCollision( walls ) )
		{
			gameOver = true;
		}

		pad.DoWallCollision( walls );
		if( pad.DoBallCollision( ball ) )
		{
			soundPad.Play();
		}

		DoBrickCollision();
	}
}

void Game::DoBrickCollision()
{
	bool collided = false;
	float leastDistSq;
	int indexClosest;
	const Vec2 ballPos = ball.GetPosition();
	for( int i = 0; i < NUM_BRICKS; ++i )
	{
		if( bricks[ i ].CheckBallCollision( ball ) )
		{
			const Vec2 brickCentre = bricks[ i ].GetBounds().GetCentre();
			const float distSq = (ballPos - brickCentre).GetLengthSq();

			if( !collided )
			{
				indexClosest = i;
				leastDistSq = distSq;
				collided = true;
			}
			else
			{
				if( distSq < leastDistSq )
				{
					indexClosest = i;
					leastDistSq = distSq;
				}
			}
		}
	}

	if( collided )
	{
		bricks[ indexClosest ].ExcecuteBallCollision( ball );
		soundBrick.Play();
		pad.ResetCooldown();
	}
}

void Game::ComposeFrame()
{
#ifndef _DEBUG
	gfx.FillRect( 0,0,int( Graphics::ScreenWidth - 1 ),int( Graphics::ScreenHeight - 1 ),borderColor );
	gfx.FillRect( walls,Colors::Black );
#else
	gfx.DrawRect( walls,borderColor );
#endif // !_DEBUG

	ball.Draw( gfx );
	
	for( const Brick& b : bricks )
	{
		b.Draw( gfx );
	}

	pad.Draw( gfx );
}
