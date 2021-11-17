#pragma once
#include "ModuleBase.h"

namespace Module
{
	class MainModule : public ModuleBase
	{
	public:
		MainModule();
		~MainModule();

	private:

	};


	MainModule* getMainModule();
}