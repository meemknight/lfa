#ifndef TOOLS_H_INCLUDE
#define TOOLS_H_INCLUDE

#define INTERNAL_BUILD 1	//when internal build is true and an assertion is hit, you have the option to debug or ignore
							//when internal build if false and an asertion is hit, the error is reported and the program 
							//closes


#include <signal.h>
#include <string.h>
#include <stdio.h>


#ifdef PLATFORM_WIN32

	#include <Windows.h>
	
	inline void assertFuncProduction(
		const char *expression,
		const char *file_name,
		unsigned const line_number,
		const char *comment = "---")
	{
	
		char c[1024] = {};
	
		sprintf(c,
			"Assertion failed\n\n"
			"File:\n"
			"%s\n\n"
			"Line:\n"
			"%u\n\n"
			"Expresion:\n"
			"%s\n\n"
			"Comment:\n"
			"%s"
			"\n\nPlease report this error to the developer.",
			file_name,
			line_number,
			expression,
			comment
		);
	
		int const action = MessageBox(0, c, "Platform Layer", MB_TASKMODAL
			| MB_ICONHAND | MB_OK | MB_SETFOREGROUND);
	
		switch (action)
		{
			case IDOK: // Abort the program:
			{
				raise(SIGABRT);
	
				_exit(3);
			}
			default:
			{
				_exit(3);
			}
		}
	
	}
	
	inline void assertFuncInternal(
		const char *expression,
		const char *file_name,
		unsigned const line_number,
		const char *comment = "---")
	{
	
		char c[1024] = {};
	
		sprintf(c,
			"Assertion failed\n\n"
			"File:\n"
			"%s\n\n"
			"Line:\n"
			"%u\n\n"
			"Expresion:\n"
			"%s\n\n"
			"Comment:\n"
			"%s"
			"\n\nPress retry to debug.",
			file_name,
			line_number,
			expression,
			comment
		);
	
		int const action = MessageBox(0, c, "Platform Layer", MB_TASKMODAL
			| MB_ICONHAND | MB_ABORTRETRYIGNORE | MB_SETFOREGROUND);
	
		switch (action)
		{
			case IDABORT: // Abort the program:
			{
				raise(SIGABRT);
	
				_exit(3);
			}
			case IDRETRY: // Break into the debugger then return control to caller
			{
				__debugbreak();
				return;
			}
			case IDIGNORE: // Return control to caller
			{
				return;
			}
			default: // This should not happen; treat as fatal error:
			{
				abort();
			}
		}
	
	}
	
	#if INTERNAL_BUILD == 1
	
		#define permaAssert(expression) (void)(											\
					(!!(expression)) ||												\
					(assertFuncInternal(#expression, __FILE__, (unsigned)(__LINE__)), 0)	\
				)
		
		#define permaAssertComment(expression, comment) (void)(								\
					(!!(expression)) ||														\
					(assertFuncInternal(#expression, __FILE__, (unsigned)(__LINE__), comment), 1)	\
				)
		
	#else
	
		#define permaAssert(expression) (void)(											\
					(!!(expression)) ||												\
					(assertFuncProduction(#expression, __FILE__, (unsigned)(__LINE__)), 0)	\
				)
		
		#define permaAssertComment(expression, comment) (void)(								\
					(!!(expression)) ||														\
					(assertFuncProduction(#expression, __FILE__, (unsigned)(__LINE__), comment), 1)	\

				)
		
	#endif
	
	

#else //linux or others
	
	inline void assertFuncProduction(
		const char *expression,
		const char *file_name,
		unsigned const line_number,
		const char *comment = "---")
	{

		raise(SIGABRT);
	
	}


	#define permaAssert(expression) (void)(											\
					(!!(expression)) ||												\
					(assertFuncProduction(#expression, __FILE__, (unsigned)(__LINE__)), 0)	\
				)

	#define permaAssertComment(expression, comment) (void)(								\
					(!!(expression)) ||														\
					(assertFuncProduction(#expression, __FILE__, (unsigned)(__LINE__)), 0, comment)	\
				)


#endif

#endif