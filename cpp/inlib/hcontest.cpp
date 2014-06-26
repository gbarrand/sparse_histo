// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifdef INLIB_MEM
#include <inlib/mem>
#endif //INLIB_MEM

#include <inlib/histo/h1d>
#include <inlib/histo/h2d>
#include <inlib/histo/sh1d>
#include <inlib/histo/sh2d>

#include <inlib/forit>
#include <inlib/randd>
#include <inlib/sys/atime>
#include <inlib/sto>

#include <fstream>
#include <iostream>

int main(int argc,char** argv) {
#ifdef INLIB_MEM
  inlib::mem::set_check_by_class(true);{
#endif //INLIB_MEM

  // ouch ! store events first in a vector in order to bench only the histo filling :
  typedef std::pair<double,double> vals_t;
  std::vector<vals_t> vs;

  unsigned int entries = 0;

 {std::ifstream f1("gauss_1_2.txt");
  std::ifstream f2("gauss_0_1.txt");
  if(f1.is_open()&&f2.is_open()&&(argc!=2)) {
    std::cout << "randoms from files." << std::endl;
    entries = 10000000;
    vs.resize(entries);
    for(unsigned int count=0;count<entries;count++) {
      vals_t& v = vs[count];
      f1 >> v.first;
      f2 >> v.second;
    }
  } else {
    std::cout << "local randoms." << std::endl;
    entries = 10000000;
    if(argc==2) {
      if(!inlib::to<unsigned int>(argv[1],entries,10000000)) entries = 10000000;
    }
    vs.resize(entries);
    inlib::rgaussd rg1(1,2);
    inlib::rgaussd rg2(0,1);
   {for(unsigned int count=0;count<entries;count++) vs[count] = vals_t(rg1.shoot(),rg2.shoot());}
  }}

  ////////////////////////////////////////
  /// h1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::h1d h("h1d",100,-5,5);
   inlib::atime start = inlib::atime::now();
   inlib_vforcit(vals_t,vs,it) h.fill((*it).first,1.4);
   std::cout << "h1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string()
             << " mean " << h.mean() << " rms " << h.rms()
             << "." << std::endl;
 }

  ////////////////////////////////////////
  /// h2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::h2d h("h2d",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   inlib_vforcit(vals_t,vs,it) h.fill((*it).first,(*it).second,0.8);
   std::cout << "h2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string()
             << " mean_x " << h.mean_x() << " rms_x " << h.rms_x()
             << " mean_y " << h.mean_y() << " rms_y " << h.rms_y()
             << "." << std::endl;
 }

  ////////////////////////////////////////
  /// sh1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::sh1d h("sh1d",100,-5,5);
   inlib::atime start = inlib::atime::now();
   inlib_vforcit(vals_t,vs,it) h.fill((*it).first,1.4);
   std::cout << "sh1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string()
             << " mean " << h.mean() << " rms " << h.rms()
             << "." << std::endl;
 }

  ////////////////////////////////////////
  /// sh2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::sh2d h("sh2d",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   inlib_vforcit(vals_t,vs,it) h.fill((*it).first,(*it).second,0.8);
   std::cout << "sh2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string()
             << " mean_x " << h.mean_x() << " rms_x " << h.rms_x()
             << " mean_y " << h.mean_y() << " rms_y " << h.rms_y()
             << "." << std::endl;
 }

  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////

#ifdef INLIB_MEM
  }inlib::mem::balance(std::cout);
#endif //INLIB_MEM

  return 0;
}
