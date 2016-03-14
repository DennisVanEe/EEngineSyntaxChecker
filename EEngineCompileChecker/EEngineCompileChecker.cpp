// nullptr program is designed to compile code and print out any warnings that might come from doing so

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <angelscript.h>
#include <scriptarray\scriptarray.h>
#include <scriptstdstring\scriptstdstring.h>
#include <scriptmath\scriptmath.h>
#include <scriptbuilder\scriptbuilder.h>

#include "ee_Module.hpp"

#define VERSION "0.1-alpha"

asIScriptEngine *engine;
eeGames::Module *currentModule;
CScriptBuilder builder; // the builder that is used

std::vector<eeGames::Module*> moduleList;

// used in place to call what is required

void dummyFunc() {}

class dummyClass
{
public:
	void dummy() {}
};

dummyClass dummy;
dummyClass* ptrDummy = &dummy;

void errorMessageCaller(const asSMessageInfo *msg, void *param)
{
	std::string type("ERROR");
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN ";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO ";
	std::cout << "(" << msg->row << ", " << msg->col << ") : " << type << " : " << msg->message << "\n";
}

void registerEngine()
{
	// set up the error handler:
	engine = asCreateScriptEngine();
	// set up the error handler:
	engine->SetMessageCallback(asFUNCTION(errorMessageCaller), 0, asCALL_CDECL);
	int error;

	// register the addons
	RegisterStdString(engine);
	RegisterScriptArray(engine, true);
	RegisterScriptMath(engine);

	error = engine->SetDefaultNamespace("ee"); // the namespace all the following will fall under

												  // register the standard functins
	error = engine->RegisterGlobalFunction("void consolePrintln(const string &in)", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("void consolePrint(const string &in)", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);

	// writing data to a data container;
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int8)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int16)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int32)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int64)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint8)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint16)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint32)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint64)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, double)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);

	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int8 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int16 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int32 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int64 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint8 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint16 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint32 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint64 &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, float &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, double &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, string &out)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);

	error = engine->RegisterGlobalFunction("bool terminateModule(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool startModule(const string &in, const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool sleepModule(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool wakeModule(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);

	error = engine->RegisterGlobalFunction("bool createDataConainter(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool deleteDataContainer(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool saveDataContainer(const string &in, const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool loadDataContainer(const string &in, const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);

	error = engine->RegisterGlobalFunction("bool loadEntityContainer(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool deleteEntityContainer(const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);

	// register enums for keyboard and mouse presses:
	error = engine->RegisterEnum("Mouse"); assert(error >= 0);
	error = engine->RegisterEnumValue("Mouse", "Left", 0); assert(error >= 0);
	error = engine->RegisterEnumValue("Mouse", "Right", 1); assert(error >= 0);
	error = engine->RegisterEnumValue("Mouse", "Middle", 2); assert(error >= 0);
	error = engine->RegisterEnumValue("Mouse", "XButton1", 3); assert(error >= 0);
	error = engine->RegisterEnumValue("Mouse", "XButton2", 4); assert(error >= 0);

	error = engine->RegisterEnum("Key"); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "A", 0); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "B", 1); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "C", 2); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "D", 3); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "E", 4); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F", 5); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "G", 6); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "H", 7); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "I", 8); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "J", 9); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "K", 10); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "L", 11); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "M", 12); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "N", 13); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "O", 14); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "P", 15); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Q", 16); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "R", 17); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "S", 18); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "T", 19); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "U", 20); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "V", 21); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "W", 22); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "X", 23); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Y", 24); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Z", 25); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num0", 26); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num2", 27); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num3", 28); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num4", 29); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num5", 30); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num6", 31); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num7", 32); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num8", 33); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num9", 34); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Escape", 35); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LControl", 36); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LShift", 37); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LAlt", 38); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LSystem", 39); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RControl", 40); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RShift", 41); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RAlt", 42); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RSystem", 43); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Menu", 44); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LBracket", 45); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RBracket", 46); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "SemiColon", 47); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Comma", 48); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Period", 49); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Quote", 50); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Slash", 51); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "BackSlash", 52); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Tilde", 53); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Equal", 54); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Dash", 55); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Space", 56); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Return", 57); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "BackSpace", 58); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Tab", 59); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "PageUp", 60); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "PageDown", 61); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "End", 62); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Home", 63); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Insert", 64); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Delete", 65); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Add", 66); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Subtract", 67); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Multiply", 68); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Divide", 69); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Left", 70); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Right", 71); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Up", 72); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Down", 73); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad0", 74); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad1", 75); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad2", 76); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad3", 77); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad4", 78); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad5", 79); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad6", 80); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad7", 81); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad8", 82); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad9", 83); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F1", 84); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F2", 85); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F3", 86); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F4", 87); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F5", 88); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F6", 89); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F7", 90); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F8", 91); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F9", 92); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F10", 93); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F11", 94); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F12", 95); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F13", 96); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F14", 97); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F15", 98); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Pause", 99); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "KeyCount", 100); assert(error >= 0);

	// register keyboard functions
	error = engine->RegisterGlobalFunction("bool iskeyPressed(Key)", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool isButtonPressed(Mouse)", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("int getXPosMouse()", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("int getYPosMouse()", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);

	// register AnimatedEntity creation and functions
	error = engine->RegisterObjectType("AnimatedEntity", sizeof(dummyClass), asOBJ_VALUE); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("AnimatedEntity", asBEHAVE_CONSTRUCT, "void f(const string &in, const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_OBJLAST, ptrDummy); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("AnimatedEntity", asBEHAVE_CONSTRUCT, "void f()", asMETHOD(dummyClass, dummy), asCALL_THISCALL_OBJLAST, ptrDummy); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("AnimatedEntity", asBEHAVE_DESTRUCT, "void f()", asMETHOD(dummyClass, dummy), asCALL_THISCALL_OBJLAST, ptrDummy); assert(error >= 0);

	error = engine->RegisterObjectMethod("AnimatedEntity", "void playFrame(uint16)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void setFrame(uint16)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// scale and position
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getPositionX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getPositionY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getScaleX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getScaleY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getOriginX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getOriginY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "float getRotation()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("AnimatedEntity", "void setPosition(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void setScale(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void setOrigin(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void setRotation(float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("AnimatedEntity", "void move(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void scale(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void rotate(float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// rendering
	error = engine->RegisterObjectMethod("AnimatedEntity", "void setRenderLevel(int)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "int getRenderLevel(int)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "void setVisible(bool)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("AnimatedEntity", "bool isVisible()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// register StaticEntity creation and functions
	error = engine->RegisterObjectType("StaticEntity", sizeof(dummyClass), asOBJ_VALUE); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("StaticEntity", asBEHAVE_CONSTRUCT, "void f(const string &in, const string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_OBJLAST, ptrDummy); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("StaticEntity", asBEHAVE_CONSTRUCT, "void f()", asMETHOD(dummyClass, dummy), asCALL_THISCALL_OBJLAST, ptrDummy); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("StaticEntity", asBEHAVE_DESTRUCT, "void f()", asMETHOD(dummyClass, dummy), asCALL_THISCALL_OBJLAST, ptrDummy); assert(error >= 0);

	// scale and position
	error = engine->RegisterObjectMethod("StaticEntity", "float getPositionX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "float getPositionY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "float getScaleX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "float getScaleY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "float getOriginX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "float getOriginY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "float getRotation()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("StaticEntity", "void setScale(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "void setOrigin(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "void setPosition(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "void setRotation(float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("StaticEntity", "void move(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "void scale(float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "void rotate(float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// rendering
	error = engine->RegisterObjectMethod("StaticEntity", "void setRenderLevel(int)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "int getRenderLevel(int)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "void setVisible(bool)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("StaticEntity", "bool isVisible()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// register SoundEffect functions
	error = engine->RegisterObjectType("SoundEffect", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "void play()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "void play(uint32)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "void setLoop(bool)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "void pause()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "void stop()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("SoundEffect", "void setPosition(float, float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "float getPositionX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "float getPositionY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "float getPositionZ()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("SoundEffect", "bool getLoopStatus()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("SoundEffect", "void setVolume(uint8)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// register Music functions
	error = engine->RegisterObjectType("Music", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "void play()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "void play(uint32)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "void setLoop(bool)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "void pause()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "void stop()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("Music", "void setPosition(float, float, float)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "float getPositionX()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "float getPositionY()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "float getPositionZ()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Music", "bool getLoopStatus()", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("Music", "void setVolume(uint8)", asMETHOD(dummyClass, dummy), asCALL_THISCALL); assert(error >= 0);

	// set up music management software
	error = engine->RegisterGlobalFunction("SoundEffect @getSoundEffect(string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("SoundEffect @createSoundEffectCopy(string &in, string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);
	error = engine->RegisterGlobalFunction("Music @getMusic(string &in)", asMETHOD(dummyClass, dummy), asCALL_THISCALL_ASGLOBAL, ptrDummy); assert(error >= 0);

	// register Microphone functions (only one mucrophone, so only one function for controlling it)
	error = engine->RegisterGlobalFunction("void setMicrophonePosition(float, float, float)", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("float getMicrophonePositionX()", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("float getMicrophonePositionY()", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("float getMicrophonePositionZ()", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);

	error = engine->RegisterGlobalFunction("float getMicrophoneVolume()", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("void setMicrophoneVolume(float)", asFUNCTION(dummyFunc), asCALL_CDECL); assert(error >= 0);
}

void helpPrint()
{
	std::cout << "EEngine version: pre-alpha, AngelScript version: " << ANGELSCRIPT_VERSION_STRING << "\n";
	std::cout << "\nanything in a bracket is a value input for the command (type without bracket)\n";
	std::cout << "build [dir]      - loads and adds the module at [dir] to build\n";
	std::cout << "show all         - shows all current modules loaded and their directories\n";
	std::cout << "remove [name]    - removes a module from being compiled by module name (file name)\n";
	std::cout << "bind func        - binds imported functions for all built modules\n";
	std::cout << "clear all        - clears all current modules in the list\n";
	std::cout << "exit             - exit the application\n";
}

void add(const std::string &command)
{
	std::string dir(command.substr(6, command.length() - 6));
	std::string name;
	int i;
	for (i = dir.size() - 1; i >= 0 && dir[i] != '/' && dir[i] != '\\'; i--)
		name += dir[i];
	std::reverse(name.begin(), name.end());

	int error = builder.StartNewModule(engine, name.c_str());
	if (error < 0)
	{
		std::cout << "could not start module " << name;
		return;
	}

	error = builder.AddSectionFromFile(dir.c_str());
	if (error == 0)
	{
		std::cout << "module " << name << " has already been loaded\n";
		return;
	}
	else if (error < 0)
	{
		std::cout << "Could not find or open module file\n";
		return;
	}

	error = builder.BuildModule();
	if (error < 0)
		return;
	eeGames::Module *temp = new eeGames::Module(builder.GetModule());

	if (temp->prepareContext() == false)
	{
		delete temp;
		return;
	}

	moduleList.push_back(temp);
	std::cout << "module " << name << " successfully built\n";
}

void showAll()
{
	if (moduleList.size() == 0)
	{
		std::cout << "no modules to show\n";
		return;
	}

	for (int i = 0; i < moduleList.size(); i++)
		std::cout << moduleList[i]->getModuleName() << "\n";
	std::cout << "\n";
}

void remove(const std::string &command)
{
	std::string name(command.substr(7, command.length() - 7));

	int i = 0;
	for (; i < moduleList.size(); i++)
	{
		if (moduleList[i]->getModuleName() == name)
		{
			moduleList.erase(moduleList.begin() + i);
			break;
		}
	}

	if (i == moduleList.size())
		std::cout << "could not find the module " << name << "\n";
	else
		std::cout << "module " << name << " removed\n";
}

void bindFunc()
{
	if (moduleList.size() == 0)
	{
		std::cout << "no modules to bind functions for\n";
		return;
	}

	for (int i = 0; i < moduleList.size(); i++)
	{
		if (moduleList[i]->bindImports())
			std::cout << "module " << moduleList[i]->getModuleName() << " had functions binded\n";
	}
}

void clear()
{
	for (eeGames::Module *tmp : moduleList)
		delete tmp;
	moduleList.clear();
	std::cout << "all modules cleared\n";
}

int main()
{
	std::vector<eeGames::Module> moduleList;
	std::string currentCommand;

	registerEngine();

	std::cout << "Welcome to the EEngine AngelScript Compiler (v" << VERSION << ")\n";
	std::cout << "Type 'help' to display the help index\n";

	while (true)
	{
		std::cout << "\n> ";
		std::getline(std::cin, currentCommand);

		if (currentCommand == "help")
			helpPrint();
		else if (currentCommand.find("build ") == 0)
			add(currentCommand);
		else if (currentCommand == "show all")
			showAll();
		else if (currentCommand.find("remove ") == 0)
			remove(currentCommand);
		else if (currentCommand == "bind func")
			bindFunc();
		else if (currentCommand == "clear all")
			clear();
		else if (currentCommand == "exit")
		{
			clear();
			return 0;
		}
		else
			std::cout << "this command does not exist\n";
	}
}

