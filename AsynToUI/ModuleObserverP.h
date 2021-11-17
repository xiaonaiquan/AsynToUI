#pragma once
#include <string>
#include "ModuleDefine.h"

namespace Module
{
	class ModuleSubject;

	//������ͻص���װ��һ������
	class ModuleObserverP
	{
	public:
		ModuleObserverP(BDelegate& hd, void* pObserObject);
	public:

		std::string				keyId;
		void*					m_pObserverObject;
		BDelegate				callback;
	};

	//���¼���װ��һ������
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

		ModuleSubject*					m_pMko;        //Ϊ�˵���ModuleSubject�Ľӿڣ������һ��ӳ��ָ��
	};
}