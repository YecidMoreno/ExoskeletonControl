

/* 
    x86_64-w64-mingw32-g++ -g mainControl.cpp -o "C:\DEV\ImGUI_Control\build\mainControl" -I C:\DEV\Requeriments\SDL2\include\SDL2 -I C:\DEV\Requeriments\Imagenes -I C:\DEV\imgui-docking -I C:\DEV\imgui-docking\examples -I C:\DEV\Requeriments\include -L C:\DEV\Requeriments\SDL2\lib -L C:\DEV\Requeriments\lib_win64 -l SDL2 -l SDL2main -l opengl32 -l gdi32 -l shell32 -l shell32 -l blas_win64_MT -l lapack_win64_MT
    x86_64-w64-mingw32-g++ -c -o add_var.o add_var.cpp -D ADD_EXPORTS
    x86_64-w64-mingw32-g++ -o add_var.dll add_var.o -s -shared -Wl,--subsystem,windows
    x86_64-w64-mingw32-g++ add_vartest2.cpp -o add_vartest2.exe
    add_vartest2.exe

    x86_64-w64-mingw32-g++ -c -o add_var.o add_var.cpp -D ADD_EXPORTS -I C:\DEV\Requeriments\include -L C:\DEV\Requeriments\lib_win64 -l gdi32 -l shell32 -l shell32 -l blas_win64_MT -l lapack_win64_MT
    x86_64-w64-mingw32-g++ -o //..//add_var.dll add_var.o -s -shared -Wl,--subsystem,windows
    x86_64-w64-mingw32-g++ add_vartest2.cpp -o add_vartest2.exe -I C:\DEV\Requeriments\include -L C:\DEV\Requeriments\lib_win64 -l gdi32 -l shell32 -l shell32 -l blas_win64_MT -l lapack_win64_MT
    add_vartest2.exe
*/
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include <armadillo>
using namespace arma;

typedef int (__stdcall *f_Add)(int a,int b);
typedef void (__stdcall *f_void)();

typedef int   * v_int;
typedef float * v_float;
typedef double* v_double;
typedef arma::Mat<double>* v_armaDouble;
int main(int argc, char** argv)
{
    for (int i = 0; i < 10; i++)
    {

        HINSTANCE hGetProcIDDLL = LoadLibrary("add_var.dll"); 

        f_void __init = (f_void)GetProcAddress(hGetProcIDDLL, "__init");
        __init();

        f_Add Add = (f_Add)GetProcAddress(hGetProcIDDLL, "Add");
        f_void Add2 = (f_void)GetProcAddress(hGetProcIDDLL, "Add2");
        Add2();
        int N = *((v_int)GetProcAddress(hGetProcIDDLL, "foo2"));    
        arma::Mat<double> N2 = *((v_armaDouble)GetProcAddress(hGetProcIDDLL, "foo3"));        

        
        printf(">> %d",Add(i,10));
        printf(">> %d",N ); 
        N2.print(" N2 : ");

        FreeLibrary(hGetProcIDDLL);
        system("pause");
        
    } 

  return EXIT_SUCCESS;
}