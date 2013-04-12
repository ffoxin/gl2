#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include <map>

#include "Window.h"

class WindowController
{
public:
	static WindowController * GetInstance();
	static void ReleaseInstance();

	void AddWindow( HWND hWnd, Window * window );
	void RemoveWindow( HWND hWnd );
	Window * GetWindowByHwnd( HWND hWnd );

private:
	typedef std::map<HWND, Window *> WindowMap_t;

	static WindowController * m_windowController;
	WindowMap_t m_windowMap;

	WindowController();
	WindowController( const WindowController & ); // not implemented
	WindowController & operator=( const WindowController & ); // not implemented
	~WindowController();
};

#endif // WINDOWCONTROLLER_H
