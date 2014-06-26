// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifdef INLIB_MEM
#include <inlib/mem>
#endif //INLIB_MEM

#include <inlib/histo/h1d>
#include <inlib/histo/h2d>
#include <inlib/histo/sh1d>
#include <inlib/histo/sh2d>

#include <inlib/sys/atime>

#include <iostream>
#include <fstream>
#include <vector>

int main(int argc,char** argv) {
#ifdef INLIB_MEM
  inlib::mem::set_check_by_class(true);{
#endif //INLIB_MEM

  unsigned int entries = 10000000;

  std::vector<double> gauss(entries);
  std::vector<double> bw(entries);

  // fill data vectors
  {
   std::ifstream f1("data/gauss.txt");
   std::ifstream f2("data/bw.txt");
   for(unsigned int count=0;count<entries;count++) {
     f1 >> gauss[count];
     f2 >> bw[count];
   }
  }

  ////////////////////////////////////////
  /// h1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::h1d h("h1d",100,-5,5);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) {
     h.fill(gauss[count],1.4);
   }
   std::cout << "h1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// h2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::h2d h("h2d",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   double v;
   for(unsigned int count=0;count<entries;count++) {
     h.fill(gauss[count], bw[count],0.8);
   }
   std::cout << "h2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// sh1d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::sh1d h("sh1d",100,-5,5);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) {
     h.fill(gauss[count],1.4);
   }
   std::cout << "sh1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
 }

  ////////////////////////////////////////
  /// sh2d ///////////////////////////////
  ////////////////////////////////////////
 {
   inlib::histo::sh2d h("sh2d",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) {
     h.fill(gauss[count], bw[count],0.8);
   }
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
