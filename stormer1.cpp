#include "stormer.h"

#include<math.h>
#define _USE_MATH_DEFINES


int main(){
  vectorR4 str, A, B; //vetores stormer y Condiciones iniciales
  
  A.r1=R0;   A.r2=z0;  A.r3=R10;  A.r4=z10;
  std::cout<< "condiciones inciales" <<std::endl;
 
  double h=0.0001;
  //intervalo [a , b] , n = (b-a)/h
  int n=(0.3 - 0)/h;
  //  std::cout<< "R" << "\t" << "z" << std::endl;

  for (int a=0;a<n;a++){
  str=stormer(R2,z2,h,n,A);
  printVector(A);  
  A=str;
  }
  return 0;
}

