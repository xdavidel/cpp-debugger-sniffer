#include <Windows.h>

typedef struct _PEB
{
    /* 0x000 */ BYTE InheritedAddressSpace;
    /* 0x001 */ BYTE ReadImageFileExecOptions;
    /* 0x002 */ BYTE BeingDebugged;
    /* 0x003 */ BYTE SpareBool;
    /* 0x004 */ void *Mutant;
    /* 0x008 */ void *ImageBaseAddress;
    /* 0x00c */ void *Ldr;
    /* 0x010 */ void *ProcessParameters;
    /* 0x014 */ void *SubSystemData;
    /* 0x018 */ void *ProcessHeap;
    /* 0x01c */ void *FastPebLock;
    /* 0x020 */ void *FastPebLockRoutine;
    /* 0x024 */ void *FastPebUnlockRoutine;
    /* 0x028 */ DWORD EnvironmentUpdateCount;
    /* 0x02c */ void *KernelCallbackTable;
    /* 0x030 */ DWORD SystemReserved[1];
    /* 0x034 */ DWORD ExecuteOptions : 2; // bit offset: 34, len=2
    /* 0x034 */ DWORD SpareBits : 30;     // bit offset: 34, len=30
    /* 0x038 */ void *FreeList;
    /* 0x03c */ DWORD TlsExpansionCounter;
    /* 0x040 */ void *TlsBitmap;
    /* 0x044 */ DWORD TlsBitmapBits[2];
    /* 0x04c */ void *ReadOnlySharedMemoryBase;
    /* 0x050 */ void *ReadOnlySharedMemoryHeap;
    /* 0x054 */ void **ReadOnlyStaticServerData;
    /* 0x058 */ void *AnsiCodePageData;
    /* 0x05c */ void *OemCodePageData;
    /* 0x060 */ void *UnicodeCaseTableData;
    /* 0x064 */ DWORD NumberOfProcessors;
    /* 0x068 */ DWORD NtGlobalFlag;
    /* 0x070 */ DWORD CriticalSectionTimeout;
    /* 0x078 */ DWORD HeapSegmentReserve;
    /* 0x07c */ DWORD HeapSegmentCommit;
    /* 0x080 */ DWORD HeapDeCommitTotalFreeThreshold;
    /* 0x084 */ DWORD HeapDeCommitFreeBlockThreshold;
    /* 0x088 */ DWORD NumberOfHeaps;
    /* 0x08c */ DWORD MaximumNumberOfHeaps;
    /* 0x090 */ void **ProcessHeaps;
    /* 0x094 */ void *GdiSharedHandleTable;
    /* 0x098 */ void *ProcessStarterHelper;
    /* 0x09c */ DWORD GdiDCAttributeList;
    /* 0x0a0 */ void *LoaderLock;
    /* 0x0a4 */ DWORD OSMajorVersion;
    /* 0x0a8 */ DWORD OSMinorVersion;
    /* 0x0ac */ WORD OSBuildNumber;
    /* 0x0ae */ WORD OSCSDVersion;
    /* 0x0b0 */ DWORD OSPlatformId;
    /* 0x0b4 */ DWORD ImageSubsystem;
    /* 0x0b8 */ DWORD ImageSubsystemMajorVersion;
    /* 0x0bc */ DWORD ImageSubsystemMinorVersion;
    /* 0x0c0 */ DWORD ImageProcessAffinityMask;
    /* 0x0c4 */ DWORD GdiHandleBuffer[34];
    /* 0x14c */ void (*PostProcessInitRoutine)();
    /* 0x150 */ void *TlsExpansionBitmap;
    /* 0x154 */ DWORD TlsExpansionBitmapBits[32];
    /* 0x1d4 */ DWORD SessionId;
    /* 0x1d8 */ DWORD AppCompatFlags;
    /* 0x1e0 */ DWORD AppCompatFlagsUser;
    /* 0x1e8 */ void *pShimData;
    /* 0x1ec */ void *AppCompatInfo;
    /* 0x1f0 */ DWORD CSDVersion;
    /* 0x1f8 */ void *ActivationContextData;
    /* 0x1fc */ void *ProcessAssemblyStorageMap;
    /* 0x200 */ void *SystemDefaultActivationContextData;
    /* 0x204 */ void *SystemAssemblyStorageMap;
    /* 0x208 */ DWORD MinimumStackCommit;
} PEB;

// Current PEB for 64bit and 32bit processes accordingly
PVOID GetPEB()
{
#ifdef _WIN64
    return (PVOID)__readgsqword(0x0C * sizeof(PVOID));
#else
    return (PVOID)__readfsdword(0x0C * sizeof(PVOID));
#endif
}