#pragma once

#include <cinttypes>

class FEmuBase;
class FLuaConsole;

typedef struct lua_State lua_State;

namespace LuaSys
{
    class FLuaScopeCheck
    {
    public:
        FLuaScopeCheck(lua_State* pState);
        ~FLuaScopeCheck();
    private:
        lua_State* LuaState = nullptr;
        int InitialStackItems = 0;
    };

	bool Init(FEmuBase* pEmulator);
	void Shutdown(void);

	void RegisterExecutionHandler(uint16_t address, const char* functionName);
	void RemoveExecutionHandler(uint16_t address);
	bool OnInstructionExecuted(uint16_t pc);

    lua_State*  GetGlobalState();

    bool LoadFile(const char* pFileName, bool bAddEditor);
    void ExecuteString(const char *pString);
    void OutputDebugString(const char* fmt, ...);

	bool OnEmulatorScreenDrawn(float x, float y, float scale);

    //FLuaConsole* GetLuaConsole();
    FEmuBase* GetEmulator();
    void DrawUI();

    void DumpStack(lua_State *L);

	bool ExportGlobalLabels();
}
