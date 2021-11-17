#include "stdafx.h"
#include "ModuleSubject.h"
#include "ModuleObserverP.h"
#include <algorithm>
#include "UIEventManager.h"

namespace Module
{
	ModuleSubject::ModuleSubject()
	{

	}

	ModuleSubject::~ModuleSubject()
	{

	}

	void ModuleSubject::addObserver(void* pObserObject, BDelegate handle)
	{
		if (isObserverExist(pObserObject))
			return;
		ModuleObserverP* BObserverP = new ModuleObserverP(handle, pObserObject);
		{
			std::lock_guard<std::mutex> lock(m_Mtx);
			m_vecObservers.push_back(BObserverP);
		}
	}

	void ModuleSubject::removeObserver(void* pObserObject)
	{
		std::lock_guard<std::mutex> lock(m_Mtx);
		auto iter = std::remove_if(m_vecObservers.begin(), m_vecObservers.end(),
			[=](ModuleObserverP* pItem)
		{
			bool b = (pObserObject == pItem->m_pObserverObject);
			if (b)
			{
				delete pItem;
				pItem = nullptr;
			}
			return b;
		});
		if (iter != m_vecObservers.end())
		{
			m_vecObservers.erase(iter, m_vecObservers.end());
		}
	}

	BOOL ModuleSubject::isObserverExist(const void* pObserObject)
	{
		std::lock_guard<std::mutex> lock(m_Mtx);
		auto iterObserver = std::find_if(m_vecObservers.begin(), m_vecObservers.end(),
			[=](ModuleObserverP* pBObserverP)
		{
			return(pObserObject == pBObserverP->m_pObserverObject);
		});
		return (iterObserver != m_vecObservers.end());
	}

	void ModuleSubject::asynNotifyObserver(const std::string& keyId, std::string& data)
	{
		BEvent_Impl* pEvent = new BEvent_Impl(this);
		pEvent->m_mkoString = data;
		_asynNotifyObserver(keyId, pEvent);
	}

	void ModuleSubject::_asynNotifyObserver(const std::string& keyId, BEvent_Impl* pEvent)
	{
		pEvent->m_keyId = keyId;
		//֪ͨ
		Module::getEventManager()->asynFireUIEvent(pEvent);
	}

	void ModuleSubject::getIObserverHandlersByModuleId(std::vector<BDelegate>& callbacks)
	{
		std::lock_guard<std::mutex> lock(m_Mtx);
		for (ModuleObserverP* pContext : m_vecObservers)
		{
			callbacks.push_back(pContext->callback);
		}
	}
}