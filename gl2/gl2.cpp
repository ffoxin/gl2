#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <tchar.h>
#include <vector>

#include "EngineGL.h"

void DrawTriangle()
{
	static GLfloat rtri;				// Angle For The Triangle

	glLoadIdentity();
	glTranslatef( -1.5f, 0.0f, -6.0f );
	glRotatef( rtri, 0.0f, 1.0f, 0.0f );
	glBegin( GL_TRIANGLES );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f(  0.0f, 1.0f, 0.0f );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( -1.0f, -1.0f, 1.0f );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f(  1.0f, -1.0f, 1.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f(  0.0f, 1.0f, 0.0f );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f(  1.0f, -1.0f, 1.0f );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f(  1.0f, -1.0f, -1.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f(  0.0f, 1.0f, 0.0f );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f(  1.0f, -1.0f, -1.0f );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( -1.0f, -1.0f, -1.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f(  0.0f, 1.0f, 0.0f );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( -1.0f, -1.0f, -1.0f );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f( -1.0f, -1.0f, 1.0f );
	glEnd();

	rtri += 0.2f;
}

void DrawCube()
{
	static GLfloat rquad;				// Angle For The Quad

	glLoadIdentity();
	glTranslatef( 1.5f, 0.0f, -7.0f );
	glRotatef( rquad, 1.0f, 1.0f, 1.0f );
	glBegin( GL_QUADS );
	glColor3f( 0.0f, 1.0f, 0.0f );
	glVertex3f(  1.0f, 1.0f, -1.0f );
	glVertex3f( -1.0f, 1.0f, -1.0f );
	glVertex3f( -1.0f, 1.0f, 1.0f );
	glVertex3f(  1.0f, 1.0f, 1.0f );
	glColor3f( 1.0f, 0.5f, 0.0f );
	glVertex3f(  1.0f, -1.0f, 1.0f );
	glVertex3f( -1.0f, -1.0f, 1.0f );
	glVertex3f( -1.0f, -1.0f, -1.0f );
	glVertex3f(  1.0f, -1.0f, -1.0f );
	glColor3f( 1.0f, 0.0f, 0.0f );
	glVertex3f(  1.0f, 1.0f, 1.0f );
	glVertex3f( -1.0f, 1.0f, 1.0f );
	glVertex3f( -1.0f, -1.0f, 1.0f );
	glVertex3f(  1.0f, -1.0f, 1.0f );
	glColor3f( 1.0f, 1.0f, 0.0f );
	glVertex3f(  1.0f, -1.0f, -1.0f );
	glVertex3f( -1.0f, -1.0f, -1.0f );
	glVertex3f( -1.0f, 1.0f, -1.0f );
	glVertex3f(  1.0f, 1.0f, -1.0f );
	glColor3f( 0.0f, 0.0f, 1.0f );
	glVertex3f( -1.0f, 1.0f, 1.0f );
	glVertex3f( -1.0f, 1.0f, -1.0f );
	glVertex3f( -1.0f, -1.0f, -1.0f );
	glVertex3f( -1.0f, -1.0f, 1.0f );
	glColor3f( 1.0f, 0.0f, 1.0f );
	glVertex3f(  1.0f, 1.0f, -1.0f );
	glVertex3f(  1.0f, 1.0f, 1.0f );
	glVertex3f(  1.0f, -1.0f, 1.0f );
	glVertex3f(  1.0f, -1.0f, -1.0f );
	glEnd();

	rquad -= 0.15f;
}

void DrawWheel()
{

}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow )			// Window Show State
{
	typedef std::vector<EngineGL *> EngineVector_t;
	EngineVector_t vec;
	vec.push_back( new EngineGL( TEXT( "WinGL2" ), 16, false, 800, 480 ) );

	/*EngineGL * engineWheel = new EngineGL( 
		TEXT( "WheelGL2" ), 
		16, false, 
		600, 600 );*/

	MSG msg;
	while ( true )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )	// Is There A Message Waiting?
		{
			if ( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			bool quit = false;
			for ( EngineVector_t::iterator i( vec.begin() ); i != vec.end(); ++i )
			{
				quit |= ( *i )->GetKey( VK_ESCAPE );
			}

			if ( quit )
			{
				break;
			}
			else
			{
				// update screen
				if ( vec.front()->GetKey( VK_F1 ) )
				{
					vec.front()->GetKey( VK_F1 ) = false;
					vec.push_back( new EngineGL( TEXT( "WheelGL2" ), 16, false, 600, 600 ) );
				}

				for ( EngineVector_t::iterator i( vec.begin() ); i != vec.end(); ++i )
				{
					( *i )->PreDrawScene();
					if ( i == vec.begin() )
					{
						DrawTriangle();
					}
					else
					{
						DrawCube();
					}
					( *i )->PostDrawScene();
				}
			}
		}
	}

	// Shutdown
	for ( EngineVector_t::iterator i( vec.begin() ); i != vec.end(); ++i )
	{
		delete *i;
	}

	return ( msg.wParam );
}
