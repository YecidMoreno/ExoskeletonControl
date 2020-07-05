#include "add_var.h"
#include <stdio.h>
#include <armadillo>
using namespace arma;


arma::Mat<double> foo3; 
int foo = 7;
int bar = 41;
int foo2 = 77;

int ADDCALL Add(int a, int b)
{
  return ((a + b));
}

void ADDCALL Add2()
{
  printf(">> Hola Add2 %f \t");
}

void ADDCALL __init()
{
  foo3 = 12.345;
}




