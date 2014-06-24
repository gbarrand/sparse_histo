// Copyright (C) 2010, Guy Barrand. All rights reserved.
// See the file inlib.license for terms.

#ifdef INLIB_MEM
#include <inlib/mem>
#endif //INLIB_MEM

#include <inlib/histo/h1d>
#include <inlib/histo/h2d>
#include <inlib/histo/p1d>
#include <inlib/histo/sliced>
#include <inlib/sys/atime>

#include <inlib/randd>

#include <iostream>

int main(int argc,char** argv) {
#ifdef INLIB_MEM
  inlib::mem::set_check_by_class(true);{
#endif //INLIB_MEM

  bool print = true;
  if(argc==2) {
    std::string s = argv[1];
    if(s=="-noprint") print = false;
  }

  unsigned int entries = 1000000;

  ////////////////////////////////////////
  /// h1d ////////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::histo::h1d h("Gauss",100,-5,5);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),1.4);
   std::cout << "h1d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
   if(print) h.hprint(std::cout);
   //std::cout << " mean " << h.mean() << ", rms " << h.rms() << std::endl;

   /*
  {unsigned int nbin = h.axis().bins();
   double mn = h.axis().lower_edge();
   double mx = h.axis().upper_edge();}
   */

 }

 {
   inlib::rbwd rbw(0,1);
   inlib::histo::h1d h("BW",100,-5,5);
   for(unsigned int count=0;count<entries;count++) h.fill(rbw.shoot(),2.3);
   if(print) h.hprint(std::cout);
 }

  ////////////////////////////////////////
  /// p1d ////////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
   inlib::histo::p1d h("Profile",100,-5,5,-2,2);
   for(unsigned int count=0;count<entries;count++) {
     h.fill(rg.shoot(),rbw.shoot(),1);
   }
   if(print) h.hprint(std::cout);
 }

  ////////////////////////////////////////
  /// h2d ////////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
   inlib::histo::h2d h("Gauss_BW",100,-5,5,100,-2,2);
   inlib::atime start = inlib::atime::now();
   for(unsigned int count=0;count<entries;count++) h.fill(rg.shoot(),rbw.shoot(),0.8);
   std::cout << "h2d.fill(" << entries << ") " << inlib::atime::elapsed(start).time_string() << std::endl;
   if(print) h.hprint(std::cout);

   /*
  {unsigned int nbin = h.axis_x().bins();
   double mn = h.axis_x().lower_edge();
   double mx = h.axis_x().upper_edge();}

  {unsigned int nbin = h.axis_y().bins();
   double mn = h.axis_y().lower_edge();
   double mx = h.axis_y().upper_edge();}
   */

  {
    inlib::histo::h1d* projection = inlib::histo::projection_x(h,"ProjX");
    if(!projection) return -1;
    projection->set_title("Gauss_BW_projectionX");
    if(print) projection->hprint(std::cout);
    delete projection;
  }
   
  {
    inlib::histo::h1d* projection = inlib::histo::projection_y(h,"ProjY");
    if(!projection) return -1;
    projection->set_title("Gauss_BW_projectionY");
    if(print) projection->hprint(std::cout);
    delete projection;
  }

  {
    inlib::histo::h1d* slice = inlib::histo::slice_x(h,40,60,"SliceX");
    if(!slice) return -1;
    slice->set_title("Gauss_BW_sliceX");
    if(print) slice->hprint(std::cout);
    delete slice;
  }

  typedef inlib::histo::axis<double,unsigned int> axis_t;
  {
    inlib::histo::h1d* slice = inlib::histo::slice_x(h,axis_t::UNDERFLOW_BIN,axis_t::UNDERFLOW_BIN,"SliceX");
    if(!slice) return -1;
    slice->set_title("Gauss_BW_sliceX_UNDER");
    if(print) slice->hprint(std::cout);
    delete slice;
  }

  {
    inlib::histo::h1d* slice = inlib::histo::slice_x(h,axis_t::OVERFLOW_BIN,axis_t::OVERFLOW_BIN,"SliceX");
    if(!slice) return -1;
    slice->set_title("Gauss_BW_sliceX_OVER");
    if(print) slice->hprint(std::cout);
    delete slice;
  }

  {
    inlib::histo::h1d* slice = inlib::histo::slice_y(h,30,50,"SliceY");
    if(!slice) return -1;
    slice->set_title("Gauss_BW_sliceY");
    if(print) slice->hprint(std::cout);
    delete slice;
  }

  {
    using namespace inlib::histo; //playing with namespaces.
    h1d* slice = slice_y(h,axis_t::UNDERFLOW_BIN,axis_t::UNDERFLOW_BIN,"SliceY");
    if(!slice) return -1;
    slice->set_title("Gauss_BW_sliceY_UNDER");
    if(print) slice->hprint(std::cout);
    delete slice;
  }

  {
    namespace tools = inlib::histo; //playing with namespaces.
    tools::h1d* slice = slice_y(h,inlib::histo::axis_OVERFLOW_BIN,inlib::histo::axis_OVERFLOW_BIN,"SliceY");
    if(!slice) return -1;
    slice->set_title("Gauss_BW_sliceY_OVER");
    if(print) slice->hprint(std::cout);
    delete slice;
  }

 }

  ////////////////////////////////////////
  /// h3d ////////////////////////////////
  ////////////////////////////////////////
 {
   inlib::rgaussd rg(1,2);
   inlib::rbwd rbw(0,1);
   inlib::rtausmed rflat;
   inlib::histo::h3d h("Gauss_BW_flat",100,-10,10,100,-2,2,100,-2,2);
   for(unsigned int count=0;count<entries;count++) {
     h.fill(rg.shoot(),rbw.shoot(),rflat.shoot());
   }
   if(print) h.hprint(std::cout);

   if(print){
     std::cout << "x mean " << h.mean_x()
               << " rms " << h.rms_x() << std::endl;
     std::cout << "y mean " << h.mean_y()
               << " rms " << h.rms_y() << std::endl;
     std::cout << "z mean " << h.mean_z()
               << " rms " << h.rms_z() << std::endl;
   }

  {
    inlib::histo::h2d* projection = inlib::histo::projection_xy(h,"ProjXY");
    if(!projection) return -1;
    projection->set_title("Gauss_BW_flat_projectionXY");
    if(print) projection->hprint(std::cout);
    
   {inlib::histo::h1d* _projection =
      inlib::histo::projection_x(*projection,"ProjX");
    if(!_projection) return -1;
    _projection->set_title("Gauss_BW_flat_projectionX");
    if(print) _projection->hprint(std::cout);
    delete _projection;}

   {inlib::histo::h1d* _projection =
      inlib::histo::projection_y(*projection,"ProjY");
    if(!_projection) return -1;
    _projection->set_title("Gauss_BW_flat_projectionY");
    if(print) _projection->hprint(std::cout);
    delete _projection;}

    delete projection;
  }
   
  {
    inlib::histo::h2d* projection = inlib::histo::projection_yz(h,"ProjYZ");
    if(!projection) return -1;
    projection->set_title("Gauss_BW_flat_projectionYZ");
    if(print) projection->hprint(std::cout);
    
   {inlib::histo::h1d* _projection =
      inlib::histo::projection_y(*projection,"ProjZ");
    if(!_projection) return -1;
    _projection->set_title("Gauss_BW_flat_projectionZ");
    if(print) _projection->hprint(std::cout);
    delete _projection;}

    delete projection;
  }
   
 }

  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////

#ifdef INLIB_MEM
  }inlib::mem::balance(std::cout);
#endif //INLIB_MEM

  return 0;
}
