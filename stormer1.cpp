#include "stormer.h"
int main(){
  vectorR4 STR, A; //vetores stormer y Condiciones iniciales
  A.r1=R0;   A.r2=z0;  A.r3=R10;  A.r4=z10;
  double h=0.001;
  //intervalo [a , b] , n = (b-a)/h
  int n=(0.3 - 0)/h;
  double  phi_n=0.0,phi_n1=0.0;
  
  //  std::cout<< "R" << "\t" << "z" << std::endl;
    
  for (int a=0;a<n;a++){
    STR=stormer(R2,z2,h,n,A);
    phi_n1=integ(h,phi1,STR,phi_n);
    printVector(A);
    std::cout<<"  "<<phi_n1<<std::endl;
    phi_n=phi_n1;
    A=STR;
  }

  return 0;
}


