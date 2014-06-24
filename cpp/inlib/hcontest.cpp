// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifdef INLIB_MEM
#include <inlib/mem>
#endif //INLIB_MEM

#include <inlib/histo/h1d>
#include <inlib/histo/h2d>
#include <inlib/histo/sh1d>
#include <inlib/histo/sh2d>

#include <inlib/randd>
#include <inlib/sys/atime>

#include <iostream>

int main(int argc,char** argv) {
#ifdef INLIB_MEM
  inlib::mem::set_check_by_class(true);{
#endif //INLIB_MEM

  unsigned int entries = 1000000;

  ////////////////////////////////////////
  /// h1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::histo::h1d h("Gauss",100,-5,5);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),1.4);
   std::cout << "h1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// h2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
   inlib::histo::h2d h("Gauss_BW",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),rbw.shoot(),0.8);
   std::cout << "h2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// sh1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::histo::sh1d h("Gauss",100,-5,5);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),1.4);
   std::cout << "sh1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// sh2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
   inlib::histo::sh2d h("Gauss_BW",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),rbw.shoot(),0.8);
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
