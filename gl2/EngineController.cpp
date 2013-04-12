#include "EngineController.h"

EngineController * EngineController::m_engineController = 0;
EngineController::EngineMap_t EngineController::m_engineMap;

EngineController * EngineController::GetEC()
{
	if ( m_engineController == 0 )
	{
		m_engineController = new EngineController();
	}

	return m_engineController;
}

void EngineController::AddEngine( HWND hWnd, EngineGL * engine )
{
	GetEC()->m_engineMap[hWnd] = engine;
}

void EngineController::RemoveEngine( HWND hWnd )
{
	GetEC()->m_engineMap.erase( hWnd );
}

EngineGL * EngineController::GetEngine( HWND hWnd )
{
	EngineController * ec = GetEC();

	EngineMap_t::iterator it = ec->m_engineMap.find( hWnd );

	if ( it == ec->m_engineMap.end() )
	{
		return 0;
	}

	return it->second;

}

EngineController::EngineController()
{

}

EngineController::~EngineController()
{

}
