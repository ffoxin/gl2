#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>

class Window
{
public:
	Window( int width, int height );
	~Window();

	bool & GetKey( int keyCode );

private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;

	int			m_width;
	int			m_height;

	bool		m_keys[256];

	int RegisterWindowClass();
	int UnregisterWindowClass();

	static LRESULT CALLBACK WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

#endif // WINDOW_H
