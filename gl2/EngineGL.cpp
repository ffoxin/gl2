#include "EngineGL.h"

#include <exception>
#include <gl/GLU.h>

#include "EngineController.h"
#include "ExceptionWindow.h"
#include "StringConstants.h"

const TCHAR * const windowClassName = TEXT( "OpenGLWindowClass" );
int EngineGL::m_windowsCount = 0;

void MessageBoxError( const char * message, const char * title );

EngineGL::EngineGL(const TCHAR * caption, int bits, bool fullscreen, GLsizei width, GLsizei height) :
	m_width( width ), 
	m_height( height ), 
	m_fullscreen( fullscreen )
{
	memset( m_keys, 0, sizeof( m_keys ) / sizeof( *m_keys ) );

	m_hInstance = GetModuleHandle( NULL );	// Grab An Instance For Our Window

	if ( !RegisterWindowsClass() )
	{
		return;
	}

	if ( m_fullscreen )													// fullscreen mode
	{
		DEVMODE dmScreenSettings;										// Device Mode
		memset( &dmScreenSettings, 0, sizeof( dmScreenSettings ) );		// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize			= sizeof( dmScreenSettings );	// Size Of The Dev mode Structure
		dmScreenSettings.dmPelsWidth	= m_width;						// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= m_height;						// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;							// Selected Bits Per Pixel
		dmScreenSettings.dmFields 		= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if ( ChangeDisplaySettings( &dmScreenSettings, CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
		{
			m_fullscreen = false;
		}
	}

	DWORD	windowStyle;		// window style
	DWORD	windowStyleEx;		// window extended style

	if ( m_fullscreen )
	{
		windowStyle		= WS_POPUP;
		windowStyleEx	= WS_EX_APPWINDOW;
		ShowCursor( FALSE );	// hide mouse pointer
	}
	else
	{
		windowStyle		= WS_OVERLAPPEDWINDOW;
		windowStyleEx	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	}

	RECT windowRect;
	windowRect.left		= static_cast<long>( 0 );			// Set Left Value To 0
	windowRect.right	= static_cast<long>( m_width );		// Set Right Value To Requested Width
	windowRect.top		= static_cast<long>( 0 );			// Set Top Value To 0
	windowRect.bottom	= static_cast<long>( m_height );	// Set Bottom Value To Requested Height

	AdjustWindowRectEx( &windowRect, windowStyle, FALSE, windowStyleEx );		// Adjust Window To True Requested Size

	m_hWnd = CreateWindowEx( 
		windowStyleEx,										// Extended Style For The Window
		windowClassName,									// Class Name
		caption,											// Window Title
		windowStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,	// Required Window Style
		0, 0,												// Window Position
		windowRect.right - windowRect.left,					// Calculate Window Width
		windowRect.bottom - windowRect.top,					// Calculate Window Height
		NULL,												// No Parent Window
		NULL,												// No Menu
		m_hInstance,										// Instance
		NULL );

	EngineController::AddEngine( m_hWnd, this );

	try
	{
		// Create The Window
		if ( !m_hWnd )
		{
			throw ExceptionCreateWindow();
		}

		static PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
		{
			sizeof( PIXELFORMATDESCRIPTOR ),			// Size Of This Pixel Format Descriptor
			1,											// Version Number
			PFD_DRAW_TO_WINDOW |						// Format Must Support Window
			PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
			PFD_DOUBLEBUFFER,							// Must Support Double Buffering
			PFD_TYPE_RGBA,								// Request An RGBA Format
			bits,										// Select Our Color Depth
			0, 0, 0, 0, 0, 0,							// Color Bits Ignored
			0,											// No Alpha Buffer
			0,											// Shift Bit Ignored
			0,											// No Accumulation Buffer
			0, 0, 0, 0,									// Accumulation Bits Ignored
			16,											// 16bit Z-Buffer (Depth Buffer)  
			0,											// No Stencil Buffer
			0,											// No Auxiliary Buffer
			PFD_MAIN_PLANE,								// Main Drawing Layer
			0,											// Reserved
			0, 0, 0										// Layer Masks Ignored
		};

		m_hDC = GetDC( m_hWnd );
		if ( !m_hDC )							// Did We Get A Device Context?
		{
			throw ExceptionCreateDeviceContext();
		}

		GLuint pixelFormat = ChoosePixelFormat( m_hDC, &pfd );
		if ( !pixelFormat )	// Did Windows Find A Matching Pixel Format?
		{
			throw ExceptionChoosePixelFormat();
		}

		if( !SetPixelFormat( m_hDC, pixelFormat, &pfd ) )		// Are We Able To Set The Pixel Format?
		{
			throw ExceptionSetPixelFormat();
		}

		m_hRC = wglCreateContext( m_hDC );
		if ( !m_hRC )				// Are We Able To Get A Rendering Context?
		{
			throw ExceptionCreateRenderingContext();
		}

		if( !wglMakeCurrent( m_hDC, m_hRC ) )					// Try To Activate The Rendering Context
		{
			throw ExceptionActivateRenderingContext();
		}

		ShowWindow( m_hWnd, SW_SHOW );						// Show The Window
		SetForegroundWindow( m_hWnd );						// Slightly Higher Priority
		SetFocus( m_hWnd );									// Sets Keyboard Focus To The Window
		SetWindowSize( m_width, m_height );					// Set Up Our Perspective GL Screen

		InitEngine();
	}
	catch ( std::exception & e )
	{
		DestroyEngine(); // reset display
		MessageBoxError( e.what(), sError );
	}
}

EngineGL::~EngineGL()
{
	EngineController::RemoveEngine( m_hWnd );
	DestroyEngine();
}

GLvoid EngineGL::SetWindowSize( GLsizei width, GLsizei height )
{
	if ( height == 0 )
	{
		height = 1; // prevent divide by zero
	}

	m_width = width;
	m_height = height;

	ApplyWindowSize();
}

GLvoid EngineGL::ApplyWindowSize()
{
	glViewport( 0, 0, m_width, m_height ); // reset current viewport

	glMatrixMode( GL_PROJECTION );	// select projection matrix
	glLoadIdentity();				// reset projection matrix

	// calculate aspect ratio
	gluPerspective( 45.0f, static_cast<GLdouble>( m_width ) / static_cast<GLdouble>( m_height ), 0.1, 100.0 );

	glMatrixMode( GL_MODELVIEW );	// select modelview matrix
	glLoadIdentity();				// reset modelview matrix
}

GLvoid EngineGL::InitEngine()
{
	glShadeModel( GL_SMOOTH );								// enable smooth shading
	glClearColor( 0.0f, 0.0f, 0.0f, 0.5f );					// set black background
	glClearDepth( 1.0 );									// setup depth buffer
	glEnable( GL_DEPTH_TEST );								// enable depth testing
	glDepthFunc( GL_LEQUAL );								// set depth testing type
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// enable nice perspective calculations
}

GLvoid EngineGL::PreDrawScene()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );	// clear screen and depth buffer
}

LRESULT CALLBACK EngineGL::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	EngineGL * engine = EngineController::GetEngine( hWnd );
	if ( engine != 0 )
	{
		// handle windows message
		switch ( uMsg )
		{
		case WM_ACTIVATE:	// window activate message
			{
				// LOWORD: WA_ACTIVE, WA_CLICKACTIVE, WA_INACTIVE
				// HIWORD: minimized state
				if ( ( LOWORD( wParam ) != WA_INACTIVE ) && ( HIWORD( wParam ) != 0 ) )
				{
					engine->m_active = true;
				}
				else
				{
					engine->m_active = false;
				}

				return 0;
			}

		case WM_SYSCOMMAND:	// system commands
			{
				switch ( wParam )
				{
				case SC_SCREENSAVE:		// screen saver trying to start
				case SC_MONITORPOWER:	// monitor trying to enter powersave
					return 0;
				}
				break;
			}

		case WM_CLOSE:
			{
				PostQuitMessage( 0 );
				return 0;
			}

		case WM_KEYDOWN:
			{
				engine->m_keys[wParam] = true;
				return 0;
			}

		case WM_KEYUP:
			{
				engine->m_keys[wParam] = false;
				return 0;
			}

		case WM_SIZE:	// resize window
			{
				// LOWORD: width
				// HIWORD: height
				engine->SetWindowSize( LOWORD( lParam ), HIWORD( lParam ) );
				return 0;
			}
		}
	}

	// pass unhandled messages to default handler
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}

GLvoid EngineGL::DestroyEngine()
{
	if ( m_fullscreen )
	{
		ChangeDisplaySettings( NULL, 0 ); // switch back to desktop
		ShowCursor( TRUE );
	}

	if ( m_hRC )
	{
		// check if device and rendering context might be released
		if ( !wglMakeCurrent( NULL, NULL ) )
		{
			MessageBoxError( sReleaseContextsError, sShutdownError );
		}

		// try to delete rendering context
		if ( !wglDeleteContext( m_hRC ) )
		{
			MessageBoxError( sReleaseRenderingContextError, sShutdownError );
		}
		m_hRC = NULL;
	}

	// try to release device context
	if ( m_hDC && !ReleaseDC( m_hWnd, m_hDC ) )
	{
		MessageBoxError( sReleaseDeviceContextError, sShutdownError );
		m_hDC = NULL;
	}

	// try to destroy window
	if ( m_hWnd && !DestroyWindow( m_hWnd ) )
	{
		MessageBoxError( sReleaseWindowError, sShutdownError );
		m_hWnd = NULL;
	}

	// try to unregister class
	UnregisterWindowsClass();
}

GLvoid EngineGL::PostDrawScene()
{
	SwapBuffers( m_hDC );
}

GLvoid EngineGL::DrawScene()
{
	static GLfloat rtri;				// Angle For The Triangle
	static GLfloat rquad;				// Angle For The Quad

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

	rtri += 0.2f;
	rquad -= 0.15f;
}

bool EngineGL::IsActive()
{
	return m_active;
}

bool & EngineGL::GetKey( int keyCode )
{
	return m_keys[keyCode];
}

bool EngineGL::RegisterWindowsClass()
{
	if ( m_windowsCount++ != 0 )
	{
		return true;
	}

	WNDCLASS windowClass;												// Windows Class Structure
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	windowClass.lpfnWndProc		= (WNDPROC) WindowProc;							// WndProc Handles Messages
	windowClass.cbClsExtra		= 0;									// No Extra Window Data
	windowClass.cbWndExtra		= 0;									// No Extra Window Data
	windowClass.hInstance		= m_hInstance;							// Set The Instance
	windowClass.hIcon			= LoadIcon( NULL, IDI_WINLOGO );		// Load The Default Icon
	windowClass.hCursor			= LoadCursor( NULL, IDC_ARROW );		// Load The Arrow Pointer
	windowClass.hbrBackground	= NULL;									// No Background Required For GL
	windowClass.lpszMenuName	= NULL;									// We Don't Want A Menu
	windowClass.lpszClassName	= windowClassName;						// Set The Class Name

	if ( !RegisterClass( &windowClass ) )
	{
		if ( GetLastError() != ERROR_CLASS_ALREADY_EXISTS )
		{
			MessageBoxA( NULL, sRegisterWindowClassError, sError, MB_OK | MB_ICONEXCLAMATION );
			m_windowsCount--;
			return false;
		}
	}

	return true;
}

bool EngineGL::UnregisterWindowsClass()
{
	if ( --m_windowsCount != 0 )
	{
		return true;
	}

	if ( !UnregisterClass( windowClassName, m_hInstance ) )
	{
		MessageBoxError( sUnregisterWindowClassError, sShutdownError );
		m_windowsCount++;
		m_hInstance = NULL;
	}
}

void MessageBoxError( const char * message, const char * title )
{
	MessageBoxA( NULL, message, title, MB_OK | MB_ICONINFORMATION );
}
