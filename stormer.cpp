#include<iostream>
#include<cmath>
#include<math.h>
#define _USE_MATH_DEFINES
//Condiciones de frontera
double const gamma0=-0.5;
double const u=5*M_PI/4;
double const R0=0.257453;
double const z0=0.3146870;
double const r0=std::hypot(R0,z0);
double const q0=1-std::pow((2*gamma0/R0+R0/std::pow(r0,3)),2);
double const z10=std::sqrt(q0)*std::sin(u);//z'_0 (velocidad inicial en z)
double const R10=std::sqrt(q0)*std::cos(u); //R'_0 (velocidad inicial en R)
//funciones dadas
double R=1;
double z=1;
double r=std::hypot(R,z);
double R2(double R, double r);
double R2(double R, double r){
return (2*gamma0/R+R/std::pow(r,3))*(2*gamma0/(R*R)+3*R*R/(std::pow(r,5))-1/(std::pow(r,3))); //R''(segunda derivada de R)
}
double z2(double R, double r);
double z2(double R, double r){
  return (2*gamma0/R+R/(std::pow(r,3)))*(3*R*z/std::pow(r,5));
}

double phi1(double R, double r); //primera derivada de phi
double phi1(double R, double r){
  return (2*gamma0/(R*R))+(1/(std::pow(r,3)));
}
//estructuras de datos (vectores de R2 y R4)
struct vectorR2{
  double R=0;
  double z=0;
};
struct vectorR4{
  double r1=0;
  double r2=0;
  double r3=0;
  double r4=0;
};
//método de stormer-verlet
vectorR4 stormer(double (*R2)(double, double), double (*z2)(double, double), double h, int n, vectorR4 boudary);
//las funciones R2 y z2 como parametros, h = el tamaño del paso de tiempo, n = número de iteraciones, vector que contiene las condiciones iniciales
vectorR4 stormer(double (*R2)(double, double), double (*z2)(double, double), double h, int n, vectorR4 boudary){
  vectorR2 Q1, Q; //Q'' , Q' , Q // velocidad y posición de las componentes R y z
  vectorR4 H;
  double Rn=boudary.r1;
  double zn=boudary.r2;
  
  double V_Rn=boudary.r3;
  double V_zn=boudary.r4;
  
  //Posiciones en R y z
  Q.R= Rn + h*V_Rn + (h*h/2)*(R2(Rn,zn));
  Q.z= zn + h*V_zn + (h*h/2)*(z2(Rn,zn));
  
  //Velocidades en R y z
  Q1.R=V_Rn + (h/2)*(R2(Rn,zn)+ R2(Q.R,Q.z)); 
  Q1.z=V_zn + (h/2)*(R2(Rn,zn)+ R2(Q.R,Q.z));    

  H.r1=Q.R;   H.r2=Q.z;  H.r3=Q1.R;  H.r4=Q1.z;
  return H;
  
}

//phi 
double integ(double h, double (*f)(double, double), vectorR4 H, double phi_n);
// h= paso del tiempo, f(R,r)=la funcion a integrar, H=(R,z) (r=(R²+z²)^(1/2)), y phi_n= valor inicial de phi
double integ(double h, double (*f)(double, double), vectorR4 H, double phi_n){
  double R=H.r1, z=H.r2, r=std::hypot(R,z);
  double k1=0,k2=0,k3=0,k4=0;
  k1=f(R,r);
  k2=f(R+(h/2),r+(h/2));
  k3=f(R+(h/2),r+(h/2));
  k4=f(R,r);
  
  double phi_n1=phi_n+(h/6)*(k1+2*k2+2*k3+k4);
  return phi_n1;
}

//funcion para imprimir
void printVector(vectorR4 a);
void printVector(vectorR4 a){

  std::cout<< a.r1 << "  " << a.r2;
}

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

