// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file exlib.license for terms.

//exlib_build_use boost inlib

#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <inlib/forit>
#include <inlib/randd>
#include <inlib/sys/atime>
#include <inlib/sto>

int main(int argc,char** argv) {
  unsigned int entries = 10000000;
  if(argc==2) {
    if(!inlib::to<unsigned int>(argv[1],entries,10000000)) entries = 10000000;
  }

  // ouch ! store events first in a vector in order to bench only the histo filling :
  typedef std::pair<int,int> vals_t;
  std::vector<vals_t> vs(entries); //ouch !
 {inlib::rgaussd rg1(50,10);
   inlib::rgaussd rg2(50,25);
  for(unsigned int count=0;count<entries;count++) vs[count] = vals_t(rg1.shoot(),rg2.shoot());}

 {boost::numeric::ublas::mapped_matrix<double> h(100,100,0);
  inlib::atime start = inlib::atime::now();
  int x,y;
  inlib_vforcit(vals_t,vs,it) {
    x = (*it).first;
    y = (*it).second;
    if((x<0)||(x>=100)) continue;
    if((y<0)||(y>=100)) continue;
    h(x,y) += 0.8;
  }
  std::cout << "sh2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;}

  return 0;
}
