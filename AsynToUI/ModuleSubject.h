#pragma once
#include "ModuleDefine.h"
#include <mutex>
#include <vector>

namespace Module
{
	class ModuleObserverP;

	class BEvent_Impl;

	class ModuleSubject final
	{
	public:
		ModuleSubject();
		~ModuleSubject();

	public:
		void addObserver(void* pObserObject, BDelegate handle);

		void removeObserver(void* pObserObject);

		BOOL isObserverExist(const void* pObserObject);

		void asynNotifyObserver(const std::string& keyId, std::string& data);

		void getIObserverHandlersByModuleId(std::vector<BDelegate>& callbacks);

	private:
		void _asynNotifyObserver(const std::string& keyId, BEvent_Impl* pEvent);
	private:
		std::mutex m_Mtx;

		std::vector<ModuleObserverP*>	m_vecObservers;
	};
}
