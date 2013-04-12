#ifndef ENGINECONTROLLER_H
#define ENGINECONTROLLER_H

#include <map>

#include "EngineGL.h"

class EngineController
{
public:
	static EngineController * GetEC();

	void AddEngine( HWND hWnd, EngineGL * engine );
	void RemoveEngine( HWND hWnd );
	EngineGL * GetEngine( HWND hWnd );

private:
	typedef std::map<HWND, EngineGL *> EngineMap_t;

	static EngineController * m_engineController;
	static EngineMap_t m_engineMap;

	EngineController();
	~EngineController();

	EngineController( const EngineController & engineControlller );
	EngineController & operator=(const EngineController & EngineController );
};

#endif // ENGINECONTROLLER_H
