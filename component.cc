#include "component.h"
#include <ostream>
#include <iomanip>


circuit::circuit():comp_list{},connection_map{}{}

circuit::~circuit()
{
  for (auto itr = connection_map.begin();itr != connection_map.end();itr++)
    {
      delete itr->second;
    }
  
  for(std::vector<component*>::iterator itr = comp_list.begin();itr != comp_list.end();itr++)
    {
      delete *itr;
    }
}

void circuit:: simulate (std::ostream& os,int it, int rows, double time)
{
  for(unsigned int i = 0; i < comp_list.size();i++)
    {
      os<<std::setw(11)<<(comp_list.at(i))->name;
    }
   
  os<<'\n';
   
  for(unsigned int i = 0; i < comp_list.size();i++)
    {
      os<<"  volt"<<" curr";
    }
  
  os<<'\n';

  for(int i=0;i<it;i++)
    {
      
      for(std::vector<component*>::iterator itr = comp_list.begin();itr != comp_list.end();++itr)
	{
	  (*itr)->update_potential(time);
	}
      
      if(i%(it/rows) == (it/rows)-1)
	{
	  
	  for(std::vector<component*>::iterator itr = comp_list.begin();itr != comp_list.end();++itr)
	    {
	      os<< std::setprecision(2) << std::fixed;
	      os<< std::setw(6) << (*itr)->calculate_voltage() <<
		std::setw(5) << (*itr)->calculate_current();
	    }
	  
	  os << '\n';
	}
           
    }

  for(std::vector<component*>::iterator itr = comp_list.begin();itr != comp_list.end();++itr)
    {
      (*itr)->m->reset_potential();
      (*itr)->p->reset_potential();
    }
  
}
void circuit::insert (e_comp comp,std::string name,double arg_val,std::string connection_p,std::string connection_m)
{
  connection*  m_temp_connection = new connection;
  if( !(connection_map.try_emplace(connection_m , m_temp_connection).second) )
    {
      delete m_temp_connection;
    }

  connection* p_temp_connection = new connection;
 
  if( !(connection_map.try_emplace(connection_p , p_temp_connection).second) )
    {
      delete p_temp_connection;
    }
 
  auto search1 = connection_map.find(connection_p);
  auto search2 = connection_map.find(connection_m);
  
  switch(comp)
    {
    case battery:
      comp_list.push_back(new Battery(name,arg_val,(search1->second),(search2->second) ));
      break;
      
    case resistor:
      comp_list.push_back(new Resistor(name,arg_val,(search1->second),(search2->second) ));
      break;
      
    case capacitor:
      comp_list.push_back(new Capacitor (name,arg_val,(search1->second),(search2->second) ));
      break;
      
    default:
      break;
    }
}

double connection::get_potential()const
{
  return potential;
}


void connection::reset_potential()
{
  potential = 0; 
}

component::component(std::string name,connection*  pos,connection*  neg):name{name},p{pos},m(neg){}

component::~component()
{
  p = nullptr;
  m = nullptr;  
}
  


component& component::operator =(const component& rhs)
{
  name = rhs.name;
  p = rhs.p;
  m = rhs.m;
  return *this;
}

double component:: calculate_voltage()
{
  return p->get_potential() - m->get_potential();
}


component::component(const component& rhs):name{rhs.name},p{rhs.p},m{rhs.m}{}


Battery::Battery(std::string name, double voltage,connection* pos,connection* neg):
  component(name,pos,neg),voltage{voltage}{}


double Battery::calculate_current()
{
  return 0;
}


double Battery::calculate_voltage()
{
  return voltage;
}


void Battery::update_potential(double time)
{
  p->potential = voltage;
  m->potential = (time - time);
}


Resistor::Resistor(std::string name, double resistance ,connection* pos,connection* neg):
  component(name,pos,neg),resistance{resistance}{}


double Resistor::calculate_current()
{
  return ( calculate_voltage() / resistance);
}


void Resistor::update_potential(double time)
{
  double minustemp = m->potential + calculate_current() * time;
  p->potential = p->potential - calculate_current() * time;
  m->potential = minustemp;
}


Capacitor::Capacitor (std::string name, double capacitance,connection* pos,connection* neg):
  component(name,pos,neg),capacitance{capacitance},charge{0}{}


double Capacitor::calculate_current()
{
  return capacitance * (calculate_voltage() - charge);
}


void Capacitor::update_potential(double time)
{
  double temp = calculate_current() * time;
  
  p->potential = p->potential - temp;
  m->potential = m->potential + temp;
  charge += temp;
}
