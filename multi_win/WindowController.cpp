#include "WindowController.h"

WindowController * WindowController::m_windowController = 0;

WindowController * WindowController::GetInstance()
{
	if ( m_windowController == 0 )
	{
		m_windowController = new WindowController();
	}

	return m_windowController;
}

void WindowController::ReleaseInstance()
{
	delete m_windowController;
	m_windowController = 0;
}

void WindowController::AddWindow( HWND hWnd, Window * window )
{
	m_windowMap[hWnd] = window;
}

void WindowController::RemoveWindow( HWND hWnd )
{
	m_windowMap.erase( hWnd );
}

Window * WindowController::GetWindowByHwnd( HWND hWnd )
{
	WindowMap_t::iterator found = m_windowMap.find( hWnd );

	if ( found == m_windowMap.end() )
	{
		return 0;
	}

	return found->second;
}

WindowController::WindowController()
{

}

WindowController::~WindowController()
{

}
