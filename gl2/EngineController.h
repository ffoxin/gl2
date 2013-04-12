#ifndef ENGINECONTROLLER_H
#define ENGINECONTROLLER_H

#include <map>

#include "EngineGL.h"

class EngineController
{
public:
	static void AddEngine( HWND hWnd, EngineGL * engine );
	static void RemoveEngine( HWND hWnd );
	static EngineGL * GetEngine( HWND hWnd );

private:
	typedef std::map<HWND, EngineGL *> EngineMap_t;

	static EngineController * m_engineController;
	static EngineMap_t m_engineMap;

	EngineController();
	~EngineController();

	static EngineController * GetEC();

	EngineController( const EngineController & engineControlller );
	EngineController & operator=(const EngineController & EngineController );
};

#endif // ENGINECONTROLLER_H
