#include "stdafx.h"
#include "ModuleObserverP.h"
#include "ModuleSubject.h"

namespace Module
{
	ModuleObserverP::ModuleObserverP(BDelegate& hd, void* pObserObject) :callback(hd), m_pObserverObject(pObserObject)
	{

	}

	BEvent_Impl::BEvent_Impl(ModuleSubject* p) : m_pMko(p), m_mkoInt(0), m_pmkoVoid(nullptr)
	{

	}

	BEvent_Impl::~BEvent_Impl()
	{

	}

	void BEvent_Impl::process()
	{
		if (nullptr == m_pMko)
		{
			return;
		}
		std::vector<BDelegate> Callbacks;
		m_pMko->getIObserverHandlersByModuleId(Callbacks); 
		if (Callbacks.empty())
			return;

		for (auto callback : Callbacks)
		{
			try
			{
				callback(m_keyId, std::make_tuple(m_mkoString, m_mkoInt, m_pmkoShardVoid, m_pmkoVoid));
			}
			catch (const std::bad_function_call&)
			{
				
			}
			catch (...)
			{
				
			}

		}
	}

	void BEvent_Impl::release()
	{
		delete this;
	}
}