#include <stdio.h>
#include <stdlib.h>

#include "peb.h"
#include "colors.h"

void PrintColor(const char *text, size_t color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    printf("%s", text);
    SetConsoleTextAttribute(hConsole, CMD_COLOR_RESET);
}

void PrintCheckItem(const char *text)
{
    printf("[*] %-80s", text);
}

void PrintCheckResult(const BOOL result)
{
    result ? PrintColor("[ BAD ]\n", CMD_COLOR_RED) : PrintColor("[ GOOD ]\n", CMD_COLOR_GREEN);
}

BOOL FindKnownDebuggers()
{
    return FindWindow(NULL, "OLLYDBG") ||
           FindWindow(NULL, "x64dbg") ||
           FindWindow(NULL, "x32dbg") ||
           FindWindow(NULL, "windbg");
}

// CheckHardwareBreakpoints returns the number of hardware
// breakpoints detected and on failure it returns -1.
int CheckHardwareBreakpoints()
{
    unsigned int NumBps = 0;

    // This structure is key to the function and is the
    // medium for detection and removal
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));

    // The CONTEXT structure is an in/out parameter therefore we have
    // to set the flags so Get/SetThreadContext knows what to set or get.
    ctx.ContextFlags = CONTEXT_DEBUG_REGISTERS;

    // Get a handle to our thread
    HANDLE hThread = GetCurrentThread();

    // Get the registers
    if (GetThreadContext(hThread, &ctx) == 0)
        return -1;

    // Now we can check for hardware breakpoints, its not
    // necessary to check Dr6 and Dr7, however feel free to
    if (ctx.Dr0 != 0)
    {
        ++NumBps;
    }
    if (ctx.Dr1 != 0)
    {
        ++NumBps;
    }
    if (ctx.Dr2 != 0)
    {
        ++NumBps;
    }
    if (ctx.Dr3 != 0)
    {
        ++NumBps;
    }
    if (ctx.Dr6 != 0)
    {
        ++NumBps;
    }
    if (ctx.Dr7 != 0)
    {
        ++NumBps;
    }

    return NumBps;
}

int main(void)
{
    PrintColor("-------------------------[Debugger Detection]-------------------------\n",
               CMD_COLOR_MAGENTA);

    PrintCheckItem("Checking IsDebuggerPresent API ()");
    BOOL isDebugged = IsDebuggerPresent();
    PrintCheckResult(isDebugged);

    PrintCheckItem("Checking CheckRemoteDebuggerPresentAPI ()");
    HANDLE proc = GetCurrentProcess();
    CheckRemoteDebuggerPresent(proc, &isDebugged);
    PrintCheckResult(isDebugged);

    PrintCheckItem("Checking PEB.BeingDebugged");
    PEB *peb = GetPEB();
    PrintCheckResult(peb->BeingDebugged);

    PrintCheckItem("Checking PEB.NtGlobalFlag");
    PrintCheckResult(peb->NtGlobalFlag);

    PrintCheckItem("Checking Known Debuggers (olly, x64dbg, windbg, etc.)");
    PrintCheckResult(FindKnownDebuggers());

    PrintCheckItem("Checking Hardware Breakpoints");
    PrintCheckResult(CheckHardwareBreakpoints() != 0);

    system("pause");

    return 0;
}