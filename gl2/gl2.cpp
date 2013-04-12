#include <windows.h>		// Header File For Windows
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <tchar.h>
#include <vector>

#include "EngineController.h"
#include "EngineGL.h"

void DrawTriangle()
{
	static GLfloat rtri = 0.0;				// Angle For The Triangle

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
	static GLfloat rquad = 0.0;				// Angle For The Quad

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
	vec.push_back( new EngineGL( TEXT( "WinGL2 Triangle" ), DrawTriangle, 16, false, 800, 480 ) );

	MSG msg;
	while ( true )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
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
			if ( vec.size() == 1 && vec.front()->GetKey( VK_ESCAPE ) )
			{
				break;
			}
			else
			{
				size_t nAddEngines = 0;
				// update screen
				for ( EngineVector_t::iterator i( vec.begin() ); i != vec.end(); ++i )
				{
					EngineGL * engine = *i;
					if ( engine->GetKey( VK_F1 ) )
					{
						engine->GetKey( VK_F1 ) = false;
						nAddEngines++;
					}
				}

				for ( size_t i = 0; i < nAddEngines; ++i )
				{
					vec.push_back( new EngineGL( TEXT( "WinGL2 Cube" ), DrawCube, 16, false, 600, 600 ) );
				}

				for ( EngineVector_t::iterator i( vec.begin() ); i != vec.end(); ++i )
				{
					EngineGL * engine = *i;
					engine->PreDrawScene();
					engine->DrawScene();
					engine->PostDrawScene();
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
