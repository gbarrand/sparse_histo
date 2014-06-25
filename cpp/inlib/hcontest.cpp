// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifdef INLIB_MEM
#include <inlib/mem>
#endif //INLIB_MEM

#include <inlib/histo/h1d>
#include <inlib/histo/h2d>
#include <inlib/histo/sh1d>
#include <inlib/histo/sh2d>

#include <inlib/vdata>
#include <inlib/sys/atime>

#ifdef INLIB_USE_RANDOM
#include <inlib/randd>
#endif

#include <iostream>

int main(int argc,char** argv) {
#ifdef INLIB_MEM
  inlib::mem::set_check_by_class(true);{
#endif //INLIB_MEM

  unsigned int entries = 10000000;

  ////////////////////////////////////////
  /// h1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::h1d h("h1d",100,-5,5);
   inlib::atime start = inlib::atime::now();
#ifdef INLIB_USE_RANDOM
   inlib::rgaussd rg(1,2);
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),1.4);
#else
   for(unsigned int count=0;count<entries;count++) h.fill(double(count%10)-5.0,1.4);
#endif
   std::cout << "h1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// h2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::h2d h("h2d",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
#ifdef INLIB_USE_RANDOM
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),rbw.shoot(),0.8);
#else
   double v;
   for(unsigned int count=0;count<entries;count++) {
     v = double(count%10);
     h.fill(v-5,(v-5)*0.5,0.8);
   }
#endif
   std::cout << "h2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// sh1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::sh1d h("sh1d",100,-5,5);
   inlib::atime start = inlib::atime::now();
#ifdef INLIB_USE_RANDOM
   inlib::rgaussd rg(1,2);
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),1.4);
#else
   for(unsigned int count=0;count<entries;count++) h.fill(double(count%10)-5.0,1.4);
#endif
   std::cout << "sh1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// sh2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::sh2d h("sh2d",100,-5,5,100,-2,2);
#ifdef INLIB_USE_RANDOM
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
//{for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),rbw.shoot(),0.8);}
   // store values first in order to bench only the histo filling :
   typedef std::pair<double,double> vals_t;
   std::vector<vals_t> vs(entries); //ouch !
  {for(unsigned int count=0;count<entries;count++) vs[count] = vals_t(rg.shoot(),rbw.shoot());}
   inlib::atime start = inlib::atime::now();
  {vals_t* p = inlib::vec_data(vs);
   for(unsigned int count=0;count<entries;count++,p++) h.fill(p->first,p->second,0.8);}
#else
   inlib::atime start = inlib::atime::now();
  {double v;
   for(unsigned int count=0;count<entries;count++) {
     v = double(count%10);
     h.fill(v-5,(v-5)*0.5,0.8);
   }}
#endif
   std::cout << "sh2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////

#ifdef INLIB_MEM
  }inlib::mem::balance(std::cout);
#endif //INLIB_MEM

  return 0;
}
