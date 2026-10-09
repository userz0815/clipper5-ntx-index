
typedef unsigned int         POINTER_32;
typedef POINTER_32           ImageBaseOffset32;

typedef unsigned char        bool;
typedef unsigned char        byte;
typedef unsigned int         dword;
typedef unsigned long long   GUID;

typedef unsigned char        uchar;
typedef unsigned int         uint;
typedef unsigned long        ulong;

typedef unsigned char        undefined;
typedef unsigned char        undefined1;
typedef unsigned short       undefined2;
typedef unsigned int         undefined4;
typedef unsigned long long   undefined5;

typedef unsigned short       ushort;
typedef unsigned short       wchar16;
typedef short                wchar_t;
typedef unsigned short       word;

//typedef unsigned int UNDEFINED4;

#define unkbyte9   unsigned long long
#define unkbyte10   unsigned long long
#define unkbyte11   unsigned long long
#define unkbyte12   unsigned long long
#define unkbyte13   unsigned long long
#define unkbyte14   unsigned long long
#define unkbyte15   unsigned long long
#define unkbyte16   unsigned long long

#define unkuint9   unsigned long long
#define unkuint10   unsigned long long
#define unkuint11   unsigned long long
#define unkuint12   unsigned long long
#define unkuint13   unsigned long long
#define unkuint14   unsigned long long
#define unkuint15   unsigned long long
#define unkuint16   unsigned long long

#define unkint9   long long
#define unkint10   long long
#define unkint11   long long
#define unkint12   long long
#define unkint13   long long
#define unkint14   long long
#define unkint15   long long
#define unkint16   long long

#define unkfloat1   float
#define unkfloat2   float
#define unkfloat3   float
#define unkfloat5   double
#define unkfloat6   double
#define unkfloat7   double
#define unkfloat9   long double
#define unkfloat11   long double
#define unkfloat12   long double
#define unkfloat13   long double
#define unkfloat14   long double
#define unkfloat15   long double
#define unkfloat16   long double

#define BADSPACEBASE   void
#define code   void

typedef struct CLIENT_ID CLIENT_ID, *PCLIENT_ID;

struct CLIENT_ID {
    void *UniqueProcess;
    void *UniqueThread;
};

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion;

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct {
    dword OffsetToDirectory:31;
    dword DataIsDirectory:1;
};

union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion {
    dword OffsetToData;
    struct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryStruct;
};

typedef struct _cpinfo _cpinfo, *P_cpinfo;

typedef unsigned int UINT;

typedef uchar BYTE;

struct _cpinfo {
    UINT MaxCharSize;
    BYTE DefaultChar[2];
    BYTE LeadByte[12];
};

typedef struct _cpinfo *LPCPINFO;

typedef ulong DWORD;

typedef DWORD LCTYPE;

typedef struct _STARTUPINFOA _STARTUPINFOA, *P_STARTUPINFOA;

typedef char CHAR;

typedef CHAR *LPSTR;

typedef ushort WORD;

typedef BYTE *LPBYTE;

typedef void *HANDLE;

struct _STARTUPINFOA {
    DWORD cb;
    LPSTR lpReserved;
    LPSTR lpDesktop;
    LPSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
};

typedef struct _STARTUPINFOA *LPSTARTUPINFOA;

typedef struct _OVERLAPPED _OVERLAPPED, *P_OVERLAPPED;

typedef ulong ULONG_PTR;

typedef union _union_518 _union_518, *P_union_518;

typedef struct _struct_519 _struct_519, *P_struct_519;

typedef void *PVOID;

struct _struct_519 {
    DWORD Offset;
    DWORD OffsetHigh;
};

union _union_518 {
    struct _struct_519 s;
    PVOID Pointer;
};

struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union _union_518 u;
    HANDLE hEvent;
};

typedef struct _SYSTEMTIME _SYSTEMTIME, *P_SYSTEMTIME;

struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
};

typedef struct _RTL_CRITICAL_SECTION _RTL_CRITICAL_SECTION, *P_RTL_CRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION *PRTL_CRITICAL_SECTION;

typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION_DEBUG _RTL_CRITICAL_SECTION_DEBUG, *P_RTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION_DEBUG *PRTL_CRITICAL_SECTION_DEBUG;

typedef long LONG;

typedef struct _LIST_ENTRY _LIST_ENTRY, *P_LIST_ENTRY;

typedef struct _LIST_ENTRY LIST_ENTRY;

struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
};

struct _LIST_ENTRY {
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
};

struct _RTL_CRITICAL_SECTION_DEBUG {
    WORD Type;
    WORD CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION *CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD SpareWORD;
};

typedef struct _OVERLAPPED *LPOVERLAPPED;

typedef struct _EXCEPTION_POINTERS _EXCEPTION_POINTERS, *P_EXCEPTION_POINTERS;

typedef LONG (*PTOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS *);

typedef struct _EXCEPTION_RECORD _EXCEPTION_RECORD, *P_EXCEPTION_RECORD;

typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD;

typedef EXCEPTION_RECORD *PEXCEPTION_RECORD;

typedef struct _CONTEXT _CONTEXT, *P_CONTEXT;

typedef struct _CONTEXT CONTEXT;

typedef CONTEXT *PCONTEXT;

typedef struct _FLOATING_SAVE_AREA _FLOATING_SAVE_AREA, *P_FLOATING_SAVE_AREA;

typedef struct _FLOATING_SAVE_AREA FLOATING_SAVE_AREA;

struct _FLOATING_SAVE_AREA {
    DWORD ControlWord;
    DWORD StatusWord;
    DWORD TagWord;
    DWORD ErrorOffset;
    DWORD ErrorSelector;
    DWORD DataOffset;
    DWORD DataSelector;
    BYTE RegisterArea[80];
    DWORD Cr0NpxState;
};

struct _CONTEXT {
    DWORD ContextFlags;
    DWORD Dr0;
    DWORD Dr1;
    DWORD Dr2;
    DWORD Dr3;
    DWORD Dr6;
    DWORD Dr7;
    FLOATING_SAVE_AREA FloatSave;
    DWORD SegGs;
    DWORD SegFs;
    DWORD SegEs;
    DWORD SegDs;
    DWORD Edi;
    DWORD Esi;
    DWORD Ebx;
    DWORD Edx;
    DWORD Ecx;
    DWORD Eax;
    DWORD Ebp;
    DWORD Eip;
    DWORD SegCs;
    DWORD EFlags;
    DWORD Esp;
    DWORD SegSs;
    BYTE ExtendedRegisters[512];
};

struct _EXCEPTION_RECORD {
    DWORD ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD *ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[15];
};

struct _EXCEPTION_POINTERS {
    PEXCEPTION_RECORD ExceptionRecord;
    PCONTEXT ContextRecord;
};

typedef struct _SYSTEMTIME *LPSYSTEMTIME;

typedef PTOP_LEVEL_EXCEPTION_FILTER LPTOP_LEVEL_EXCEPTION_FILTER;

typedef wchar_t WCHAR;

typedef CHAR *LPCSTR;

typedef CHAR *LPCH;

typedef union _LARGE_INTEGER _LARGE_INTEGER, *P_LARGE_INTEGER;

typedef struct _struct_19 _struct_19, *P_struct_19;

typedef struct _struct_20 _struct_20, *P_struct_20;

typedef double LONGLONG;

struct _struct_20 {
    DWORD LowPart;
    LONG HighPart;
};

struct _struct_19 {
    DWORD LowPart;
    LONG HighPart;
};

union _LARGE_INTEGER {
    struct _struct_19 s;
    struct _struct_20 u;
    LONGLONG QuadPart;
};

typedef union _LARGE_INTEGER LARGE_INTEGER;

typedef struct _IMAGE_SECTION_HEADER _IMAGE_SECTION_HEADER, *P_IMAGE_SECTION_HEADER;

typedef union _union_226 _union_226, *P_union_226;

union _union_226 {
    DWORD PhysicalAddress;
    DWORD VirtualSize;
};

struct _IMAGE_SECTION_HEADER {
    BYTE Name[8];
    union _union_226 Misc;
    DWORD VirtualAddress;
    DWORD SizeOfRawData;
    DWORD PointerToRawData;
    DWORD PointerToRelocations;
    DWORD PointerToLinenumbers;
    WORD NumberOfRelocations;
    WORD NumberOfLinenumbers;
    DWORD Characteristics;
};

typedef WCHAR *LPWSTR;

typedef struct _IMAGE_SECTION_HEADER *PIMAGE_SECTION_HEADER;

typedef WCHAR *LPWCH;

typedef WCHAR *LPCWSTR;

typedef DWORD LCID;

typedef struct IMAGE_DOS_HEADER IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

struct IMAGE_DOS_HEADER {
    char e_magic[2]; // Magic number
    word e_cblp; // Bytes of last page
    word e_cp; // Pages in file
    word e_crlc; // Relocations
    word e_cparhdr; // Size of header in paragraphs
    word e_minalloc; // Minimum extra paragraphs needed
    word e_maxalloc; // Maximum extra paragraphs needed
    word e_ss; // Initial (relative) SS value
    word e_sp; // Initial SP value
    word e_csum; // Checksum
    word e_ip; // Initial IP value
    word e_cs; // Initial (relative) CS value
    word e_lfarlc; // File address of relocation table
    word e_ovno; // Overlay number
    word e_res[4][4]; // Reserved words
    word e_oemid; // OEM identifier (for e_oeminfo)
    word e_oeminfo; // OEM information; e_oemid specific
    word e_res2[10][10]; // Reserved words
    dword e_lfanew; // File address of new exe header
    byte e_program[64]; // Actual DOS program
};

typedef ULONG_PTR DWORD_PTR;

typedef ULONG_PTR SIZE_T;

typedef void (*_PHNDLR)(int);

typedef struct _FILETIME _FILETIME, *P_FILETIME;

typedef struct _FILETIME *LPFILETIME;

struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};

typedef int (*FARPROC)(void);

typedef WORD *LPWORD;

typedef DWORD *LPDWORD;

typedef struct HINSTANCE__ HINSTANCE__, *PHINSTANCE__;

struct HINSTANCE__ {
    int unused;
};

typedef int BOOL;

typedef BOOL *LPBOOL;

typedef BYTE *PBYTE;

typedef struct HINSTANCE__ *HINSTANCE;

typedef void *LPCVOID;

typedef void *LPVOID;

typedef HINSTANCE HMODULE;

typedef struct IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct IMAGE_DATA_DIRECTORY IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

struct IMAGE_DATA_DIRECTORY {
    ImageBaseOffset32 VirtualAddress;
    dword Size;
};

struct IMAGE_OPTIONAL_HEADER32 {
    word Magic;
    byte MajorLinkerVersion;
    byte MinorLinkerVersion;
    dword SizeOfCode;
    dword SizeOfInitializedData;
    dword SizeOfUninitializedData;
    ImageBaseOffset32 AddressOfEntryPoint;
    ImageBaseOffset32 BaseOfCode;
    ImageBaseOffset32 BaseOfData;
    UINT *ImageBase;
    dword SectionAlignment;
    dword FileAlignment;
    word MajorOperatingSystemVersion;
    word MinorOperatingSystemVersion;
    word MajorImageVersion;
    word MinorImageVersion;
    word MajorSubsystemVersion;
    word MinorSubsystemVersion;
    dword Win32VersionValue;
    dword SizeOfImage;
    dword SizeOfHeaders;
    dword CheckSum;
    word Subsystem;
    word DllCharacteristics;
    dword SizeOfStackReserve;
    dword SizeOfStackCommit;
    dword SizeOfHeapReserve;
    dword SizeOfHeapCommit;
    dword LoaderFlags;
    dword NumberOfRvaAndSizes;
    struct IMAGE_DATA_DIRECTORY DataDirectory[16];
};

typedef struct Var Var, *PVar;

struct Var {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;

struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct {
    dword NameOffset:31;
    dword NameIsString:1;
};

typedef struct IMAGE_FILE_HEADER IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

struct IMAGE_FILE_HEADER {
    word Machine; // 332
    word NumberOfSections;
    dword TimeDateStamp;
    dword PointerToSymbolTable;
    dword NumberOfSymbols;
    word SizeOfOptionalHeader;
    word Characteristics;
};

typedef struct IMAGE_NT_HEADERS32 IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

struct IMAGE_NT_HEADERS32 {
    char Signature[4];
    struct IMAGE_FILE_HEADER FileHeader;
    struct IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

typedef struct StringFileInfo StringFileInfo, *PStringFileInfo;

struct StringFileInfo {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY_ENTRY IMAGE_RESOURCE_DIRECTORY_ENTRY, *PIMAGE_RESOURCE_DIRECTORY_ENTRY;

typedef union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion, *PIMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion;

union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion {
    struct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct IMAGE_RESOURCE_DIRECTORY_ENTRY_NameStruct;
    dword Name;
    word Id;
};

struct IMAGE_RESOURCE_DIRECTORY_ENTRY {
    union IMAGE_RESOURCE_DIRECTORY_ENTRY_NameUnion NameUnion;
    union IMAGE_RESOURCE_DIRECTORY_ENTRY_DirectoryUnion DirectoryUnion;
};

typedef struct StringTable StringTable, *PStringTable;

struct StringTable {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_SECTION_HEADER IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef union Misc Misc, *PMisc;

typedef enum SectionFlags {
    IMAGE_SCN_TYPE_NO_PAD=8,
    IMAGE_SCN_RESERVED_0001=16,
    IMAGE_SCN_CNT_CODE=32,
    IMAGE_SCN_CNT_INITIALIZED_DATA=64,
    IMAGE_SCN_CNT_UNINITIALIZED_DATA=128,
    IMAGE_SCN_LNK_OTHER=256,
    IMAGE_SCN_LNK_INFO=512,
    IMAGE_SCN_RESERVED_0040=1024,
    IMAGE_SCN_LNK_REMOVE=2048,
    IMAGE_SCN_LNK_COMDAT=4096,
    IMAGE_SCN_GPREL=32768,
    IMAGE_SCN_MEM_16BIT=131072,
    IMAGE_SCN_MEM_PURGEABLE=131072,
    IMAGE_SCN_MEM_LOCKED=262144,
    IMAGE_SCN_MEM_PRELOAD=524288,
    IMAGE_SCN_ALIGN_1BYTES=1048576,
    IMAGE_SCN_ALIGN_2BYTES=2097152,
    IMAGE_SCN_ALIGN_4BYTES=3145728,
    IMAGE_SCN_ALIGN_8BYTES=4194304,
    IMAGE_SCN_ALIGN_16BYTES=5242880,
    IMAGE_SCN_ALIGN_32BYTES=6291456,
    IMAGE_SCN_ALIGN_64BYTES=7340032,
    IMAGE_SCN_ALIGN_128BYTES=8388608,
    IMAGE_SCN_ALIGN_256BYTES=9437184,
    IMAGE_SCN_ALIGN_512BYTES=10485760,
    IMAGE_SCN_ALIGN_1024BYTES=11534336,
    IMAGE_SCN_ALIGN_2048BYTES=12582912,
    IMAGE_SCN_ALIGN_4096BYTES=13631488,
    IMAGE_SCN_ALIGN_8192BYTES=14680064,
    IMAGE_SCN_LNK_NRELOC_OVFL=16777216,
    IMAGE_SCN_MEM_DISCARDABLE=33554432,
    IMAGE_SCN_MEM_NOT_CACHED=67108864,
    IMAGE_SCN_MEM_NOT_PAGED=134217728,
    IMAGE_SCN_MEM_SHARED=268435456,
    IMAGE_SCN_MEM_EXECUTE=536870912,
    IMAGE_SCN_MEM_READ=1073741824,
    IMAGE_SCN_MEM_WRITE=2147483648
} SectionFlags;

union Misc {
    dword PhysicalAddress;
    dword VirtualSize;
};

struct IMAGE_SECTION_HEADER {
    char Name[8];
    union Misc Misc;
    ImageBaseOffset32 VirtualAddress;
    dword SizeOfRawData;
    dword PointerToRawData;
    dword PointerToRelocations;
    dword PointerToLinenumbers;
    word NumberOfRelocations;
    word NumberOfLinenumbers;
    enum SectionFlags Characteristics;
};

typedef struct VS_VERSION_INFO VS_VERSION_INFO, *PVS_VERSION_INFO;

struct VS_VERSION_INFO {
    word StructLength;
    word ValueLength;
    word StructType;
    wchar16 Info[16];
    byte Padding[2];
    dword Signature;
    word StructVersion[2];
    word FileVersion[4];
    word ProductVersion[4];
    dword FileFlagsMask[2];
    dword FileFlags;
    dword FileOS;
    dword FileType;
    dword FileSubtype;
    dword FileTimestamp;
};

typedef struct IMAGE_BASE_RELOCATION IMAGE_BASE_RELOCATION, *PIMAGE_BASE_RELOCATION;

struct IMAGE_BASE_RELOCATION {
    dword VirtualAddress;
    dword SizeOfBlock;
};

typedef struct IMAGE_RESOURCE_DATA_ENTRY IMAGE_RESOURCE_DATA_ENTRY, *PIMAGE_RESOURCE_DATA_ENTRY;

struct IMAGE_RESOURCE_DATA_ENTRY {
    dword OffsetToData;
    dword Size;
    dword CodePage;
    dword Reserved;
};

typedef struct VarFileInfo VarFileInfo, *PVarFileInfo;

struct VarFileInfo {
    word wLength;
    word wValueLength;
    word wType;
};

typedef struct IMAGE_RESOURCE_DIRECTORY IMAGE_RESOURCE_DIRECTORY, *PIMAGE_RESOURCE_DIRECTORY;

struct IMAGE_RESOURCE_DIRECTORY {
    dword Characteristics;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    word NumberOfNamedEntries;
    word NumberOfIdEntries;
};

typedef struct IMAGE_DIRECTORY_ENTRY_EXPORT IMAGE_DIRECTORY_ENTRY_EXPORT, *PIMAGE_DIRECTORY_ENTRY_EXPORT;

struct IMAGE_DIRECTORY_ENTRY_EXPORT {
    dword Characteristics;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    ImageBaseOffset32 Name;
    dword Base;
    dword NumberOfFunctions;
    dword NumberOfNames;
    ImageBaseOffset32 AddressOfFunctions;
    ImageBaseOffset32 AddressOfNames;
    ImageBaseOffset32 AddressOfNameOrdinals;
};

typedef struct StringInfo StringInfo, *PStringInfo;

struct StringInfo {
    word wLength;
    word wValueLength;
    word wType;
};

typedef unsigned int uintptr_t;

typedef struct _tiddata _tiddata, *P_tiddata;

typedef struct _tiddata *_ptiddata;

typedef struct threadmbcinfostruct threadmbcinfostruct, *Pthreadmbcinfostruct;

typedef struct threadmbcinfostruct *pthreadmbcinfo;

typedef struct threadlocaleinfostruct threadlocaleinfostruct, *Pthreadlocaleinfostruct;

typedef struct threadlocaleinfostruct *pthreadlocinfo;

typedef struct setloc_struct setloc_struct, *Psetloc_struct;

typedef struct setloc_struct _setloc_struct;

typedef struct localerefcount localerefcount, *Plocalerefcount;

typedef struct localerefcount locrefcount;

typedef struct lconv lconv, *Plconv;

typedef struct __lc_time_data __lc_time_data, *P__lc_time_data;

typedef struct _is_ctype_compatible _is_ctype_compatible, *P_is_ctype_compatible;

struct lconv {
    char *decimal_point;
    char *thousands_sep;
    char *grouping;
    char *int_curr_symbol;
    char *currency_symbol;
    char *mon_decimal_point;
    char *mon_thousands_sep;
    char *mon_grouping;
    char *positive_sign;
    char *negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    wchar_t *_W_decimal_point;
    wchar_t *_W_thousands_sep;
    wchar_t *_W_int_curr_symbol;
    wchar_t *_W_currency_symbol;
    wchar_t *_W_mon_decimal_point;
    wchar_t *_W_mon_thousands_sep;
    wchar_t *_W_positive_sign;
    wchar_t *_W_negative_sign;
};

struct _is_ctype_compatible {
    ulong id;
    int is_clike;
};

struct setloc_struct {
    wchar_t *pchLanguage;
    wchar_t *pchCountry;
    int iLocState;
    int iPrimaryLen;
    BOOL bAbbrevLanguage;
    BOOL bAbbrevCountry;
    UINT _cachecp;
    wchar_t _cachein[131];
    wchar_t _cacheout[131];
    struct _is_ctype_compatible _Loc_c[5];
    wchar_t _cacheLocaleName[85];
};

struct threadmbcinfostruct {
    int refcount;
    int mbcodepage;
    int ismbcodepage;
    ushort mbulinfo[6];
    uchar mbctype[257];
    uchar mbcasemap[256];
    wchar_t *mblocalename;
};

struct localerefcount {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
};

struct threadlocaleinfostruct {
    int refcount;
    UINT lc_codepage;
    UINT lc_collate_cp;
    UINT lc_time_cp;
    locrefcount lc_category[6];
    int lc_clike;
    int mb_cur_max;
    int *lconv_intl_refcount;
    int *lconv_num_refcount;
    int *lconv_mon_refcount;
    struct lconv *lconv;
    int *ctype1_refcount;
    ushort *ctype1;
    ushort *pctype;
    uchar *pclmap;
    uchar *pcumap;
    struct __lc_time_data *lc_time_curr;
    wchar_t *locale_name[6];
};

struct _tiddata {
    ulong _tid;
    uintptr_t _thandle;
    int _terrno;
    ulong _tdoserrno;
    UINT _fpds;
    ulong _holdrand;
    char *_token;
    wchar_t *_wtoken;
    uchar *_mtoken;
    char *_errmsg;
    wchar_t *_werrmsg;
    char *_namebuf0;
    wchar_t *_wnamebuf0;
    char *_namebuf1;
    wchar_t *_wnamebuf1;
    char *_asctimebuf;
    wchar_t *_wasctimebuf;
    void *_gmtimebuf;
    char *_cvtbuf;
    uchar _con_ch_buf[5];
    ushort _ch_buf_used;
    void *_initaddr;
    void *_initarg;
    void *_pxcptacttab;
    void *_tpxcptinfoptrs;
    int _tfpecode;
    pthreadmbcinfo ptmbcinfo;
    pthreadlocinfo ptlocinfo;
    int _ownlocale;
    ulong _NLG_dwCode;
    void *_terminate;
    void *_unexpected;
    void *_translator;
    void *_purecall;
    void *_curexception;
    void *_curcontext;
    int _ProcessingThrow;
    void *_curexcspec;
    void *_pFrameInfoChain;
    _setloc_struct _setloc_data;
    void *_reserved1;
    void *_reserved2;
    void *_reserved3;
    void *_reserved4;
    void *_reserved5;
    int _cxxReThrow;
    ulong __initDomain;
    int _initapartment;
};

struct __lc_time_data {
    char *wday_abbr[7];
    char *wday[7];
    char *month_abbr[12];
    char *month[12];
    char *ampm[2];
    char *ww_sdatefmt;
    char *ww_ldatefmt;
    char *ww_timefmt;
    int ww_caltype;
    int refcount;
    wchar_t *_W_wday_abbr[7];
    wchar_t *_W_wday[7];
    wchar_t *_W_month_abbr[12];
    wchar_t *_W_month[12];
    wchar_t *_W_ampm[2];
    wchar_t *_W_ww_sdatefmt;
    wchar_t *_W_ww_ldatefmt;
    wchar_t *_W_ww_timefmt;
    wchar_t *_W_ww_locale_name;
};

typedef struct _LocaleUpdate _LocaleUpdate, *P_LocaleUpdate;

//struct _LocaleUpdate { // PlaceHolder Structure
//};

typedef int (*_onexit_t)(void);

typedef UINT size_t;

typedef size_t rsize_t;

typedef int errno_t;

typedef struct localeinfo_struct localeinfo_struct, *Plocaleinfo_struct;

struct localeinfo_struct {
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
};

typedef struct localeinfo_struct *_locale_t;


undefined4 FUN_10001000(undefined4 *param_1);
undefined4 FUN_100011b0(undefined4 *param_1);
undefined4 FUN_10001270(undefined4 *param_1);
int FUN_100012c0(undefined4 *param_1);
undefined4 FUN_10001370(undefined4 *param_1);
undefined4 FUN_100013d0(undefined4 *param_1);
undefined4 FUN_10001400(int param_1);
UINT FUN_10001430(int param_1,int param_2);
int FUN_10001480(undefined4 *param_1);
int FUN_100014e0(void);
void _LOCK@12(undefined4 param_1,undefined4 param_2,undefined4 param_3);
void _UNLOCK@12(undefined4 param_1,undefined4 param_2,undefined4 param_3);
undefined4 FUN_10001560(undefined4 param_1,undefined4 param_2);
undefined4 FUN_100015d0(void);
bool FUN_10001600(undefined4 param_1);
undefined4 FUN_10001650(void);
void FUN_10001690(void);
undefined4 FUN_100016b0(int param_1);
bool FUN_10001800(int param_1);
undefined4 RDDINIT(uint param_1,undefined4 *param_2,int *param_3,int param_4,undefined4 *param_5);
undefined4 __thiscall FUN_10001980(void *this,int *param_1,undefined4 param_2);
undefined4 FUN_100019b0(undefined4 *param_1);
int FUN_10001a30(int *param_1);
int FUN_10001aa0(int *param_1,int *param_2);
void FUN_10001af0(int *param_1,undefined4 param_2);
undefined4 FUN_10001b20(undefined4 param_1,undefined4 *param_2);
void FUN_10001b50(int *param_1);
undefined4 FUN_10001bb0(int *param_1);
undefined4 FUN_10001c10(int *param_1,int param_2,undefined4 *param_3);
int __thiscall FUN_10001ca0(void *this,int *param_1);
int __thiscall FUN_10001cf0(void *this,int *param_1);
void FUN_10001d40(int *param_1);
int FUN_10001db0(int *param_1,undefined4 param_2);
int FUN_10001e20(int *param_1);
int FUN_10001ee0(int *param_1,int param_2);
int FUN_10002170(int *param_1,int *param_2);
undefined4 FUN_100023e0(int *param_1,undefined4 *param_2,int *param_3,int param_4);
int FUN_10002b60(int *param_1);
undefined4 FUN_10002bf0(int *param_1);
undefined4 FUN_10002db0(int *param_1,undefined4 param_2);
int FUN_10002e20(int *param_1);
undefined4 FUN_10002fb0(int *param_1,undefined4 param_2);
int FUN_10003030(int *param_1);
int FUN_100030c0(int *param_1);
int FUN_100031f0(int *param_1,int param_2,int param_3);
void * FUN_10003cb0(int *param_1,int *param_2,undefined4 param_3);
int FUN_10004660(int *param_1,int param_2);
int FUN_10005530(int *param_1);
int FUN_100055e0(int *param_1);
int FUN_10005750(int *param_1,int param_2);
int FUN_10005950(int *param_1,undefined4 param_2,int param_3,int *param_4);
undefined4 FUN_10005a00(int *param_1);
void FUN_10005b20(int param_1,undefined4 param_2);
undefined4 FUN_10005b70(int *param_1,int param_2,undefined4 param_3,uint *param_4);
undefined4 FUN_10005bf0(undefined4 param_1,int *param_2);
int FUN_10005c70(int param_1,undefined4 *param_2,int param_3,int param_4,int param_5);
void FUN_10006150(int param_1,uint param_2,int param_3);
undefined4 FUN_10006290(undefined4 param_1,undefined4 *param_2,uint param_3,int param_4,char *param_5,undefined4 param_6,int param_7);
int FUN_100064c0(undefined4 param_1,undefined4 *param_2,undefined4 param_3,uint param_4,int param_5);
void FUN_10006510(undefined4 param_1,undefined4 *param_2,undefined4 param_3,uint param_4,int param_5);
undefined4 FUN_10006580(undefined4 param_1,undefined4 *param_2,int param_3);
void FUN_10006930(undefined4 param_1,undefined4 *param_2,int param_3);
void FUN_10006bd0(int param_1,int param_2,int param_3,int param_4);
void FUN_10006ca0(int param_1,int param_2);
undefined4 FUN_10006db0(int param_1,int *param_2,int param_3);
uint FUN_10007050(undefined4 param_1,int param_2,int param_3,int param_4);
void FUN_100070f0(undefined4 param_1,uint param_2,int param_3);
undefined4 FUN_10007130(int param_1,void *param_2);
undefined4 __thiscall FUN_100071b0(void *this,undefined4 param_1,undefined4 *param_2);
undefined4 FUN_10007220(undefined4 param_1,int param_2,ushort *param_3,int param_4);
bool FUN_10007580(undefined4 param_1,undefined4 *param_2);
undefined4 FUN_100075f0(undefined4 param_1,undefined4 *param_2);
int FUN_100076b0(undefined4 param_1,undefined4 *param_2,int param_3,int param_4);
undefined4 FUN_10007a50(undefined4 param_1,undefined4 *param_2,int *param_3,int param_4);
int FUN_10007c20(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,int param_5,undefined4 param_6);
void FUN_10008140(undefined4 param_1,undefined4 *param_2,int param_3);
void FUN_100089a0(undefined4 param_1,int param_2,ushort *param_3,uint param_4,int param_5);
void FUN_10008a90(int param_1,undefined2 *param_2);
undefined4 FUN_10008b10(void *param_1,undefined4 *param_2,void *param_3,int param_4);
void __thiscall FUN_10008be0(void *this,void *param_1,int param_2,int param_3,int param_4);
int FUN_10008ca0(undefined4 param_1,undefined4 *param_2,int param_3);
undefined4 __thiscall FUN_10008d30(void *this,undefined4 param_1,undefined4 *param_2);
void __thiscall FUN_10008df0(void *this,undefined4 param_1,undefined4 *param_2);
int FUN_10008e60(int param_1,undefined4 *param_2);
undefined4 FUN_10008fa0(int *param_1,void *param_2,void *param_3);
int FUN_100097e0(int *param_1,undefined4 *param_2,int *param_3,int param_4);
void FUN_100098b0(undefined4 param_1,undefined4 *param_2);
int FUN_10009910(int param_1,undefined4 *param_2);
undefined4 FUN_10009a20(int param_1,int param_2);
int FUN_10009b10(int param_1,undefined4 *param_2);
undefined4 FUN_10009c20(int param_1,int param_2);
void FUN_10009d10(int param_1,undefined4 param_2,int param_3);
int FUN_10009de0(int *param_1,undefined4 *param_2,int param_3,int param_4);
void FUN_1000a170(void *param_1,int *param_2);
undefined4 FUN_1000a1d0(int *param_1,int param_2,int param_3,undefined4 *param_4);
int FUN_1000a250(int *param_1,int param_2);
undefined4 FUN_1000a2c0(int *param_1,int param_2,int param_3);
int FUN_1000a3e0(int *param_1,int param_2,undefined4 param_3);
int FUN_1000a490(int *param_1,int param_2,int *param_3,int param_4);
int FUN_1000a750(int *param_1,int param_2,int *param_3,int param_4);
void __thiscall FUN_1000a9e0(void *this,int param_1,undefined4 param_2,undefined4 param_3);
void FUN_1000aa50(undefined4 param_1,undefined4 param_2,undefined4 param_3,char *param_4);
int FUN_1000ad20(int *param_1,undefined4 param_2);
int FUN_1000ada0(int *param_1,undefined4 *param_2,int param_3);
int FUN_1000ae90(int param_1,int param_2,int param_3);
undefined4 FUN_1000af80(int *param_1,undefined4 *param_2,int param_3,int param_4);
int FUN_1000b100(int *param_1,int param_2,undefined4 param_3);
int FUN_1000b150(int *param_1,undefined4 *param_2,int param_3);
void FUN_1000b380(int *param_1,uint param_2,int param_3,int param_4,int param_5);
void Ordinal_274(void);
void Ordinal_454(void);
void Ordinal_455(void);
void Ordinal_166(void);
void Ordinal_1108(void);
void Ordinal_1200(void);
void Ordinal_1109(void);
void Ordinal_857(void);
void Ordinal_1556(void);
void _GetThreadSlot@4(void);
void Ordinal_854(void);
void Ordinal_1113(void);
void Ordinal_444(void);
void Ordinal_877(void);
void Ordinal_1115(void);
void Ordinal_75(void);
void _IndexExclLock@4(void);
void Ordinal_873(void);
void Ordinal_1124(void);
void Ordinal_426(void);
void Ordinal_1131(void);
void Ordinal_1120(void);
void Ordinal_415(void);
void Ordinal_422(void);
void Ordinal_410(void);
void Ordinal_253(void);
void Ordinal_203(void);
void Ordinal_272(void);
void Ordinal_1106(void);
void Ordinal_222(void);
void _GetLockTries@4(void);
void Ordinal_1116(void);
void Ordinal_71(void);
void Ordinal_874(void);
void Ordinal_271(void);
void Ordinal_223(void);
void Ordinal_1132(void);
void Ordinal_1259(void);
void Ordinal_411(void);
void Ordinal_876(void);
void Ordinal_1121(void);
void Ordinal_1565(void);
void Ordinal_295(void);
void Ordinal_81(void);
void Ordinal_276(void);
void Ordinal_1112(void);
void Ordinal_707(void);
void Ordinal_1130(void);
void Ordinal_1102(void);
void Ordinal_257(void);
void Ordinal_1127(void);
void _IndexExclUnlock@4(void);
void Ordinal_1114(void);
void Ordinal_1128(void);
void __Str(void);
void Ordinal_1123(void);
void Ordinal_1129(void);
void Ordinal_456(void);
void * __cdecl FID_conflict:_memcpy(void *_Dst,void *_Src,size_t _Size);
char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count);
undefined4 __CRT_INIT@12(undefined4 param_1,int param_2,int param_3);
int __fastcall ___DllMainCRTStartup(int param_1,int param_2,undefined4 param_3);
void entry(undefined4 param_1,int param_2,int param_3);
void __cdecl FUN_1000be12(undefined4 *param_1,undefined4 *param_2,uint param_3);
undefined4 * __cdecl __VEC_memcpy(undefined4 *param_1,undefined4 *param_2,uint param_3);
undefined4 FUN_1000bf7c(void);
undefined4 __get_sse2_info(void);
int __cdecl __encode_pointer(int param_1);
void __encoded_null(void);
int __cdecl __decode_pointer(int param_1);
LPVOID ___set_flsgetvalue(void);
void __cdecl __mtterm(void);
void __cdecl __initptd(_ptiddata _Ptd,pthreadlocinfo _Locale);
void FUN_1000c277(void);
void FUN_1000c280(void);
_ptiddata __cdecl __getptd_noexit(void);
_ptiddata __cdecl __getptd(void);
void __freefls@4(void *param_1);
void FUN_1000c436(void);
void FUN_1000c442(void);
void __cdecl __freeptd(_ptiddata _Ptd);
int __cdecl __mtinit(void);
void __cdecl _free(void *_Memory);
void FUN_1000c69c(void);
void * __cdecl __malloc_crt(size_t _Size);
void * __cdecl __calloc_crt(size_t _Count,size_t _Size);
void * __cdecl __realloc_crt(void *_Ptr,size_t _NewSize);
void __cdecl __crt_waiting_on_module_handle(LPCWSTR param_1);
void __cdecl __amsg_exit(int param_1);
void __cdecl ___crtCorExitProcess(int param_1);
void __cdecl ___crtExitProcess(int param_1);
void FUN_1000c84f(void);
void FUN_1000c858(void);
void __cdecl __initterm(undefined4 *param_1);
void __cdecl __initterm_e(undefined4 *param_1,undefined4 *param_2);
int __cdecl __cinit(int param_1);
void __cdecl doexit(int param_1,int param_2,int param_3);
void FUN_1000ca3e(void);
void __cdecl __exit(int _Code);
void __cdecl __cexit(void);
void __cdecl __init_pointers(void);
int __cdecl __ioinit(void);
void __cdecl __ioterm(void);
int __cdecl __setenvp(void);
void __cdecl parse_cmdline(undefined4 *param_1,byte *param_2,int *param_3);
int __cdecl __setargv(void);
LPVOID __cdecl ___crtGetEnvironmentStringsA(void);
void __RTC_Initialize(void);
int __cdecl __heap_init(void);
void __cdecl __heap_term(void);
void FUN_1000d2c2(void);
int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr);
int __cdecl ___CppXcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr);
void __cdecl __SEH_prolog4(undefined4 param_1,int param_2);
void __SEH_epilog4(void);
undefined4 __cdecl __except_handler4(int *param_1,PVOID param_2,undefined4 param_3);
void __cdecl ___security_init_cookie(void);
int __cdecl __mtinitlocks(void);
void __cdecl __mtdeletelocks(void);
void __cdecl FUN_1000d764(int param_1);
int __cdecl __mtinitlocknum(int _LockNum);
void FUN_1000d835(void);
void __cdecl __lock(int _File);
void __cdecl ___freetlocinfo(void *param_1);
void __cdecl ___addlocaleref(LONG *param_1);
LONG * __cdecl ___removelocaleref(LONG *param_1);
LONG * __updatetlocinfoEx_nolock(void);
pthreadlocinfo __cdecl ___updatetlocinfo(void);
void FUN_1000db8a(void);
int __cdecl CPtoLCID(int param_1);
void __cdecl setSBCS(threadmbcinfostruct *param_1);
void __cdecl setSBUpLow(threadmbcinfostruct *param_1);
pthreadmbcinfo __cdecl ___updatetmbcinfo(void);
void FUN_1000de57(void);
_LocaleUpdate * __thiscall _LocaleUpdate::_LocaleUpdate(_LocaleUpdate *this,localeinfo_struct *param_1);
int __cdecl getSystemCP(int param_1);
void __cdecl __setmbcp_nolock(undefined4 param_1,int param_2);
int __cdecl __setmbcp(int _CodePage);
void FUN_1000e2a9(void);
undefined4 ___initmbctable(void);
int __cdecl __get_errno_from_oserr(ulong param_1);
int * __cdecl __errno(void);
uint __cdecl ___sbh_find_block(int param_1);
void __cdecl ___sbh_free_block(uint *param_1,int param_2);
undefined4 * ___sbh_alloc_new_region(void);
int __cdecl ___sbh_alloc_new_group(int param_1);
undefined4 __cdecl ___sbh_resize_block(uint *param_1,int param_2,int param_3);
int * __cdecl ___sbh_alloc_block(uint *param_1);
int * __cdecl _V6_HeapAlloc(uint *param_1);
void FUN_1000ee5f(void);
void * __cdecl _malloc(size_t _Size);
int * __cdecl __calloc_impl(UINT param_1,UINT param_2,undefined4 *param_3);
void FUN_1000f02e(void);
void * __cdecl _realloc(void *_Memory,size_t _NewSize);
void FUN_1000f194(void);
void __cdecl __NMSG_WRITE(int param_1);
void __cdecl __FF_MSGBANNER(void);
void __cdecl FUN_1000f44f(undefined4 param_1);
void __cdecl __invoke_watson(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,UINT param_4,uintptr_t param_5);
void __cdecl __invalid_parameter(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,UINT param_4,uintptr_t param_5);
int __cdecl __onexit_nolock(int param_1);
_onexit_t __cdecl __onexit(_onexit_t _Func);
void FUN_1000f6cd(void);
int __cdecl _atexit(_func_4879 *param_1);
void __initp_misc_cfltcvt_tab(void);
BOOL __cdecl __ValidateImageBase(PBYTE pImageBase);
PIMAGE_SECTION_HEADER __cdecl __FindPESection(PBYTE pImageBase,DWORD_PTR rva);
BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE pTarget);
void __initp_eh_hooks(void);
void __cdecl __initp_misc_winsig(undefined4 param_1);
uint __cdecl siglookup(uint param_1);
_PHNDLR __cdecl ___get_sigabrt(void);
int __cdecl _raise(int _SigNum);
void FUN_1000fa7d(void);
void __cdecl FUN_1000fab9(undefined4 param_1);
void __cdecl FUN_1000fac8(undefined4 param_1);
void __cdecl FUN_1000fad7(undefined4 param_1);
BOOL __cdecl ___crtInitCritSecAndSpinCount(LPCRITICAL_SECTION param_1,DWORD param_2);
void __cdecl FUN_1000fb46(undefined4 param_1);
int __cdecl __callnewh(size_t _Size);
errno_t __cdecl _strcpy_s(char *_Dst,rsize_t _SizeInBytes,char *_Src);
size_t __cdecl _strlen(char *_Str);
int __cdecl x_ismbbtype_l(localeinfo_struct *param_1,uint param_2,int param_3,int param_4);
int __cdecl __ismbblead(uint _C);
void * __cdecl _memcpy(void *_Dst,void *_Src,size_t _Size);
void __fastcall __security_check_cookie(int param_1);
void __cdecl __local_unwind4(uint *param_1,int param_2,uint param_3);
void FUN_1001013a(int param_1);
void __fastcall _EH4_CallFilterFunc(undefined *param_1);
void __fastcall _EH4_TransferToHandler(undefined *UNRECOVERED_JUMPTABLE);
void __fastcall _EH4_GlobalUnwind(PVOID param_1);
void __fastcall _EH4_LocalUnwind(int param_1,uint param_2,undefined4 param_3,uint *param_4);
void __cdecl ___free_lc_time(undefined4 *param_1);
void __cdecl ___free_lconv_num(undefined4 *param_1);
void __cdecl ___free_lconv_mon(int param_1);
void __cdecl __freea(void *_Memory);
errno_t __cdecl _strcat_s(char *_Dst,rsize_t _SizeInBytes,char *_Src);
size_t __cdecl _strcspn(char *_Str,char *_Control);
errno_t __cdecl _strncpy_s(char *_Dst,rsize_t _SizeInBytes,char *_Src,rsize_t _MaxCount);
void * __cdecl _memset(void *_Dst,int _Val,size_t _Size);
int __cdecl __crtGetStringTypeA_stat(localeinfo_struct *param_1,ulong param_2,char *param_3,int param_4,ushort *param_5,int param_6,int param_7,int param_8);
BOOL __cdecl ___crtGetStringTypeA(_locale_t _Plocinfo,DWORD _DWInfoType,LPCSTR _LpSrcStr,int _CchSrc,LPWORD _LpCharType,int _Code_page,BOOL _BError);
char * __cdecl _strpbrk(char *_Str,char *_Control);
int __cdecl __crtLCMapStringA_stat(localeinfo_struct *param_1,ulong param_2,ulong param_3,char *param_4,int param_5,char *param_6,int param_7,int param_8,int param_9);
int __cdecl ___crtLCMapStringA(_locale_t _Plocinfo,LPCWSTR _LocaleName,DWORD _DwMapFlag,LPCSTR _LpSrcStr,int _CchSrc,LPSTR _LpDestStr,int _CchDest,int _Code_page,BOOL _BError);
size_t __cdecl __msize(void *_Memory);
void FUN_10010d94(void);
int __cdecl ___crtMessageBoxA(LPCSTR _LpText,LPCSTR _LpCaption,UINT _UType);
int __cdecl __set_error_mode(int _Mode);
void FUN_10010f51(void);
void __cdecl _abort(void);
void __cdecl ___report_gsfailure(void);
void __cdecl __global_unwind2(PVOID param_1);
void __cdecl __local_unwind2(int param_1,uint param_2);
void __NLG_Notify(ulong param_1);
void FUN_100112b4(void);
int __cdecl __isleadbyte_l(int _C,_locale_t _Locale);
uint __alloca_probe_16(void);
uint __alloca_probe_8(void);
void __cdecl fastzero_I(undefined1 (*param_1) [16],uint param_2);
undefined1 (*) [16] __cdecl __VEC_memzero(undefined1 (*param_1) [16],undefined4 param_2,uint param_3);
long __cdecl _atol(char *_Str);
void __cdecl ___ansicp(LCID param_1);
void __cdecl ___convertcp(UINT param_1,UINT param_2,char *param_3,uint *param_4,LPSTR param_5,int param_6);
int __cdecl __isctype_l(int _C,int _Type,_locale_t _Locale);
void __alloca_probe(void);
ulong __cdecl strtoxl(localeinfo_struct *param_1,char *param_2,char **param_3,int param_4,int param_5);
long __cdecl _strtol(char *_Str,char **_EndPtr,int _Radix);
int __cdecl ___ascii_strnicmp(char *_Str1,char *_Str2,size_t _MaxCount);
void RtlUnwind(PVOID TargetFrame,PVOID TargetIp,PEXCEPTION_RECORD ExceptionRecord,PVOID ReturnValue);

