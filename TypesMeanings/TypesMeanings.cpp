#include <inttypes.h>
#include <Windows.h>

int main()
{
	/*
	* 32 bit systems:
	*
	* LP32 or 2/4/4 (int is 16-bit, long and pointer are 32-bit)
	* Win16 API
	* ILP32 or 4/4/4 (int, long, and pointer are 32-bit);
	* Win32 API
	* Unix and Unix-like systems (Linux, Mac OS X)
	*
	* 64 bit systems:
	*
	* LLP64 or 4/4/8 (int and long are 32-bit, pointer is 64-bit)
	* Win64 API
	* LP64 or 4/8/8 (int is 32-bit, long and pointer are 64-bit)
	* Unix and Unix-like systems (Linux, Mac OS X)
	*/

	int;			// depending on compiler ( built-in type )
	long;			// depending on ?
	int* p;			// depending on the platform ( x64, x86 )

	int32_t;		// no dependency ( always 32 bit int )
	int64_t;		// no dependency ( always 64 bit int )
	size_t;			// depending on the platform ( x64, x86 )

					// Windows API 
	DWORD v = 0;	// no dependency usigned long
	LONG_PTR;		// depending on the platform ( x64, x86 )
	INT_PTR;		// "
	DWORD_PTR;		// "

}