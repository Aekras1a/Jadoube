#pragma once
#include "ISysInternals.h"
#include <string>

typedef HANDLE(*OpenProcessFunc)(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId);

struct process_explorer_proc_obj;
extern "C" DWORD64 getProcObj();
extern "C" int setProcObj(process_explorer_proc_obj* obj);

//RE-ed the applicable compents from procexp obj
//the rest is unknown and uncared
extern "C" {
	struct process_explorer_proc_obj {
		DWORD flink_offset; //@ 0x00
		BYTE unkwn1[0x30]; //pad the unknown
		void *unknown; //pad with unknown QWORD/DWORD to keep multi-platform
		void *proc_name; //@ 0x40
		BYTE unkown2[0x10]; //pad the unknown
		DWORD proc_id; // @ 0x50 
					   //???
	};
}


class Procexp : public ISysInternals
{
private:
	std::wstring myProcess = L"explorer.exe";
   static HANDLE HideProcessHook(DWORD dwDesiredAccess, BOOL bInheritHandle, DWORD dwProcessId, process_explorer_proc_obj* procObj);
public:
	Procexp();
	void DoActions();
	void Patch(void * hook, void * jmpAddr);
	~Procexp();
};

