#ifdef ADD_EXPORTS
  #define ADDAPI __declspec(dllexport)
#else
  #define ADDAPI __declspec(dllimport)
#endif

/* Define calling convention in one place, for convenience. */
#define ADDCALL __cdecl

#include <armadillo>
using namespace arma;

/* Make sure functions are exported with C linkage under C++ compilers. */
#ifdef __cplusplus
extern "C"
{
#endif

ADDAPI int ADDCALL Add(int a, int b);
ADDAPI void ADDCALL Add2();
ADDAPI void ADDCALL __init();

/* Exported variables. */
extern ADDAPI int foo;
extern ADDAPI int foo2;
extern ADDAPI int bar;
extern ADDAPI arma::Mat<double> foo3 ;

#ifdef __cplusplus
} // __cplusplus defined.
#endif