#ifndef ENGINEGL_H
#define ENGINEGL_H

#include <windows.h>
#include <tchar.h>
#include <gl/GL.h>

class EngineGL
{
public:
	typedef void (* DrawFunc_t)();

	EngineGL( const TCHAR * caption, DrawFunc_t drawFunction, int bits, bool fullscreen, GLsizei width, GLsizei height );
	~EngineGL();

	GLvoid SetWindowSize( GLsizei width, GLsizei height );
	
	bool IsActive();
	bool & GetKey( int keyCode );

	GLvoid PreDrawScene();
	GLvoid DrawScene();
	GLvoid PostDrawScene();

private:
	HDC			m_hDC;			// device context
	HGLRC		m_hRC;			// rendering context
	HWND		m_hWnd;			// handle window
	HINSTANCE	m_hInstance;	// application instance

	GLuint		m_width;
	GLuint		m_height;

	bool		m_keys[256];
	bool		m_active;
	bool		m_fullscreen;

	DrawFunc_t	m_drawFunction;

	static int	m_windowsCount;

	GLvoid InitEngine();
	GLvoid DestroyEngine();
	GLvoid ApplyWindowSize();

	bool RegisterWindowsClass();
	bool UnregisterWindowsClass();

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

#endif // ENGINEGL_H
