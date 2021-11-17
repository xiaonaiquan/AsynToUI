#pragma once
#include <string>
#include "ModuleDefine.h"

namespace Module
{
	class ModuleSubject;

	//将对象和回调包装成一个对象
	class ModuleObserverP
	{
	public:
		ModuleObserverP(BDelegate& hd, void* pObserObject);
	public:

		std::string				keyId;
		void*					m_pObserverObject;
		BDelegate				callback;
	};

	//将事件包装成一个对象
	class BEvent_Impl final
	{
	public:
		BEvent_Impl(ModuleSubject* p);
		~BEvent_Impl();
	public:
		void process();
		void release();

	public:
		std::string						m_keyId;

		//callback  params
		int							    m_mkoInt;
		void*							m_pmkoVoid;
		std::string						m_mkoString;
		std::shared_ptr<void>			m_pmkoShardVoid;

		ModuleSubject*					m_pMko;        //为了调用ModuleSubject的接口，这里放一个映射指针
	};
}