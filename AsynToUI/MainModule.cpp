#include "stdafx.h"
#include "MainModule.h"

namespace Module
{
	Module::MainModule* getMainModule()
	{
		static MainModule module;
		return &module;
	}

	MainModule::MainModule()
	{

	}

	MainModule::~MainModule()
	{

	}
}