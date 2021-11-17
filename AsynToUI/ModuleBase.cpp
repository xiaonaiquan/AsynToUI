#include "stdafx.h"
#include "ModuleBase.h"
#include "ModuleSubject.h"

namespace Module
{
	ModuleBase::ModuleBase() :m_pModuleSubject(nullptr)
	{
		m_pModuleSubject = new ModuleSubject;
	}
	ModuleBase::~ModuleBase()
	{

	}

	void ModuleBase::addObserver(void* pObserObject, BDelegate handle)
	{
		m_pModuleSubject->addObserver(pObserObject, handle);
	}

	void ModuleBase::removeObserver(void* pObserObject)
	{
		m_pModuleSubject->removeObserver(pObserObject);
	}

	void ModuleBase::asynNotifyObserver(const std::string& keyId, std::string& data)
	{
		m_pModuleSubject->asynNotifyObserver(keyId, data);
	}
}