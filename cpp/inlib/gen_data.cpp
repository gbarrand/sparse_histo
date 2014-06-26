// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifdef INLIB_MEM
#include <inlib/mem>
#endif //INLIB_MEM

#include <inlib/randd>

#include <fstream>
#include <iostream>
#include <iomanip>

int main(int argc,char** argv) {
#ifdef INLIB_MEM
  inlib::mem::set_check_by_class(true);{
#endif //INLIB_MEM

  unsigned int entries = 10000000;

  inlib::rgaussd rg1(1,2);
  inlib::rgaussd rg2(0,1);
  std::ofstream f1("gauss_1_2.txt", std::ios::out | std::ios::binary | std::ios::trunc);
  std::ofstream f2("gauss_0_1.txt", std::ios::out | std::ios::binary | std::ios::trunc);
  f1 << std::fixed << std::setprecision(15);
  f2 << std::fixed << std::setprecision(15);
  for(unsigned int count=0;count<entries;count++) {
    double v1 = rg1.shoot();
    double v2 = rg2.shoot();
    f1 << v1 << "\n";
    f2 << v2 << "\n";
  }
  f1.flush();
  f2.flush();
  f1.close();
  f2.close();

#ifdef INLIB_MEM
  }inlib::mem::balance(std::cout);
#endif //INLIB_MEM

  return 0;
}
