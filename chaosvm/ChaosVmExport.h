#ifdef CHAOSVM_EXPORTS
#define __CHAOSVM_API__ __declspec(dllexport)
#else
#define __CHAOSVM_API__ //__declspec(dllimport)
#endif


#define __CHAOSVM_EXP__ extern "C" __CHAOSVM_API__ 
