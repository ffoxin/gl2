// minimal windows application

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T( "win32app" );

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T( "Win32 Guided Tour Application" );

HINSTANCE hInst;
bool keys[256];

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );

int WINAPI WinMain( HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow )
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof( WNDCLASSEX );
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon( hInstance, MAKEINTRESOURCE( IDI_APPLICATION ) );
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)( COLOR_WINDOW+1 );
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_APPLICATION ) );

	if ( !RegisterClassEx( &wcex ) )
	{
		MessageBox( NULL,
			_T( "Call to RegisterClassEx failed!" ),
			_T( "Win32 Guided Tour" ),
			NULL );

		return 1;
	}

	hInst = hInstance; // Store instance handle in our global variable

	// The parameters to CreateWindow explained:
	// szWindowClass: the name of the application
	// szTitle: the text that appears in the title bar
	// WS_OVERLAPPEDWINDOW: the type of window to create
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position ( x, y )
	// 500, 100: initial size ( width, length )
	// NULL: the parent of this window
	// NULL: this application does not have a menu bar
	// hInstance: the first parameter from WinMain
	// NULL: not used in this application
	HWND hWnd = CreateWindow( 
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		500, 100,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if ( !hWnd )
	{
		MessageBox( NULL,
			_T( "Call to CreateWindow failed!" ),
			_T( "Win32 Guided Tour" ),
			NULL );

		return 1;
	}

	// The parameters to ShowWindow explained:
	// hWnd: the value returned from CreateWindow
	// nCmdShow: the fourth parameter from WinMain
	ShowWindow( hWnd,
		nCmdShow );
	UpdateWindow( hWnd );

	// Main message loop:
	MSG msg;
	while ( true )
	{
		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			if ( keys[VK_F1] == true )
			{
				keys[VK_F1] = false;

			}
		}
	}

	return ( int ) msg.wParam;
}

//
//  FUNCTION: WndProc( HWND, UINT, WPARAM, LPARAM )
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR greeting[] = _T( "Hello, World!" );

	switch ( message )
	{
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );

		TextOut( hdc, 5, 5, greeting, _tcslen( greeting ) );

		EndPaint( hWnd, &ps );
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	case WM_KEYDOWN:
		keys[wParam] = true;
		break;

	case WM_KEYUP:
		keys[wParam] = false;
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
		break;
	}

	return 0;
}
