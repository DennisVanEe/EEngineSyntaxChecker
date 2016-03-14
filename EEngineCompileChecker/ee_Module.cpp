#include "ee_Module.hpp"

eeGames::Module::Module(asIScriptModule *module) : _m_module(module)
{
	_m_engine = _m_module->GetEngine();
	_m_context = _m_engine->CreateContext();
}

eeGames::Module::~Module()
{
	_m_context->Release();
	_m_module->Discard();
}

bool eeGames::Module::bindImports()
{
	int error = _m_module->BindAllImportedFunctions();
	switch (error)
	{
	case asERROR:
	case asCANT_BIND_ALL_FUNCTIONS:
		return false;
	}
	return true;
}

bool eeGames::Module::prepareContext()
{
	bool exit = true;
	if (_m_context->Prepare(_m_module->GetFunctionByDecl(_m_stepDecl.c_str())) != asSUCCESS)
	{
		std::cout << "Could not find the function " << _m_stepDecl << " in module " << _m_module->GetName() << "\n";
		exit = false;
	}
	if (_m_context->Prepare(_m_module->GetFunctionByDecl(_m_initDecl.c_str())) != asSUCCESS)
	{
		std::cout << "Could not find the function " << _m_initDecl << " in module "   << _m_module->GetName() << "\n";
		exit = false;
	}
	return exit;
}