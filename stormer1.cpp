#include "stormer.h"
#include<fstream>

void printVector(vectorR4 a);
int main(){
  vectorR4 STR, A; //vetores stormer y Condiciones iniciales
  A.r1=R0;   A.r2=z0;  A.r3=R10;  A.r4=z10;
  double h=0.0001;
  //intervalo [a , b] , n = (b-a)/h
  int n=(0.3 - 0)/h;
  double  phi_n=0.0,phi_n1=0.0;

  //R,z,phi
//se implementa el método y se guardan los datos en "trajectory.dat"
  std::ofstream file;	
  file.open("trajectory.dat");
  for (int a=0;a<n;a++){
    STR=stormer(R2,z2,h,n,A);
    phi_n1=integ(h,phi1,STR,phi_n);
    file<<std::setprecision(9)<<std::fixed<< A.r1 << "  " << A.r2<<"  "<<phi_n1<<std::endl;
    phi_n=phi_n1;
    A=STR;
  }
    file.close();
  return 0;
}



