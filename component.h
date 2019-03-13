#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include <vector>
#include <map>
#include <ostream>


class connection
{
 private:
  double potential;
  void reset_potential();
 connection():potential{0}{};
  
 public:
  double get_potential()const;
  friend class Capacitor;
  friend class Resistor;
  friend class Battery;
  friend class circuit;
  
};




class component{
 private:
  
 protected:
  
  std::string name;
  component(std::string name,connection*  pos,connection*  neg);
  component(const component&);
  component& operator =(const component & rhs);
  virtual double calculate_current() = 0;
  virtual double calculate_voltage();
  virtual void update_potential(double time)=0;
  connection *p,*m;
  virtual ~component();
  
 public:
  
  friend class circuit;
 
};


class Battery :public component
{
 private:
  
  double voltage;
  Battery(std::string name, double voltage,connection* pos,connection* neg);

  double calculate_current();
  double calculate_voltage();
  void update_potential(double time);
 public:

  
  
  friend class circuit;
};


class Resistor: public component
{
 public:
  
  friend class circuit;
 private:
  double calculate_current();
  void update_potential(double time);
  Resistor(std::string name, double resistance ,connection* pos,connection* neg);
  double resistance;
};

class Capacitor: public component
{
 public:
  friend class circuit;
  
 private:
  double calculate_current();
  void update_potential(double time);
  Capacitor (std::string name, double capacitance,connection* pos,connection* neg);
  double capacitance;
  double charge;
};


enum e_comp {battery,resistor,capacitor};
class circuit
{
 private:
  std::vector<component*> comp_list;
  std::map<std::string , connection*> connection_map;
  
 public:
  
  circuit();
  ~circuit();
  void simulate (std::ostream& os,int it, int rows, double time);
  void insert (e_comp comp,std::string name,double arg_val,std::string connection_p,std::string connection_m);
 
};



#endif
