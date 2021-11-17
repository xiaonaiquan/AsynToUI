#pragma once
#include "ModuleBase.h"
#include "ModuleDefine.h"

namespace Module
{
	class ModuleSubject;

	class ModuleBase
	{
	public:
		ModuleBase();
		~ModuleBase();

	public:
		void addObserver(void* pObserObject,BDelegate handle);
		void removeObserver(void* pObserObject);
		void asynNotifyObserver(const std::string& keyId, std::string& data);
	private:
		ModuleSubject* m_pModuleSubject;
	};
}

