#pragma once

#include <angelscript.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <assert.h>
#include <iostream>
#include <assert.h>

// Module holds scripts that can communicate directly with each other
// can create or destroy these scripts

// TODO: make sure sprites are managed in render engine: render engine controls sprite life, script controls position

namespace eeGames
{
	class Module
	{
	private:
		asIScriptModule *_m_module;
		asIScriptContext *_m_context;
		asIScriptEngine *_m_engine;

		std::string _m_scriptString;

		// TODO: load these from engine properties xml
		std::string _m_stepDecl = "void step(uint)";
		std::string _m_initDecl = "void initialize()";
	public:
		Module(asIScriptModule *module);
		~Module();

		// module modification and loading
		bool bindImports();

		std::string getModuleName() const
		{
			return std::move(std::string(_m_module->GetName()));
		}

		bool prepareContext();
	};
}
