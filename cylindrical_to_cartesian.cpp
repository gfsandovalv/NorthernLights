#include<cmath>
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;

int main()
{

/*se lee el archivo "trajectory.dat" romando las columnas como R,z,phi
y devuelve un archivo "cartesian.dat" con las cordenadas cartesianas*/


  double x=0, y=0, R=0, z=0, phi=0;
  ifstream filein("trajectory.dat");
  ofstream fileout("cartesian.dat");
  while (filein >>R >>z >>phi){
    x=R*cos(phi);
    y=R*sin(phi);
fileout<<setprecision(9)<<std::fixed<<x<<"  "<<y<<"  "<<z<<endl;  
  } 
  fileout.close();


}
