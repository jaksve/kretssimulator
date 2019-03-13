#include "component.h"
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main(int argc,char* argv[])
{
  stringstream ss{};
  for (int i = 0;i < argc - 1;i++)
    {
      argv++;
      ss << *argv<<' ';     
    }
  
  int iters,rows;
  double time,voltage;
  
  ss>>iters>>rows>>time>>voltage;
  
 
  

  circuit krets1,krets2,krets3;

  krets1.insert(battery,"BAT",voltage,"p","n");
  krets1.insert(resistor,"R1",6.0,"p","q124");
  krets1.insert(resistor,"R2",4.0,"q124","q23");
  krets1.insert(resistor,"R3",8.0,"q23","n");
  krets1.insert(resistor,"R4",12.0,"q124","n");


  
  krets2.insert(battery,"BAT",voltage,"p","n");
  krets2.insert(resistor,"R1",150.0,"p","l");
  krets2.insert(resistor,"R2",50.0,"p","r");
  krets2.insert(resistor,"R3",100.0,"r","l");
  krets2.insert(resistor,"R4",300.0,"l","n");
  krets2.insert(resistor,"R5",250.0,"r","n");

  
  
  krets3.insert(battery,"BAT",voltage,"p","n");
  krets3.insert(resistor,"R1",150.0,"p","l");
  krets3.insert(resistor,"R2",50.0,"p","r");
  krets3.insert(capacitor,"C3",1.0,"r","l");
  krets3.insert(resistor,"R4", 300.0, "l","n");
  krets3.insert(capacitor,"C5",0.75,"r","n");

   cout<<"\n krets1: "<<endl;
   krets1.simulate(cout,iters,rows,time);
  
   cout<<"\n krets2: "<<endl;
   krets2.simulate(cout,iters,rows,time);
  
  cout<<"\n krets3: "<<endl;
  krets3.simulate(cout,iters,rows,time);

  

  
  return 0;

}







