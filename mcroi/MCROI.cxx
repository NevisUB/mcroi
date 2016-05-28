//by vic
#ifndef LARLITE_MCROI_CXX
#define LARLITE_MCROI_CXX

#include "MCROI.h"

namespace larlite {

  bool MCROI::initialize() { return true; }
  
  bool MCROI::analyze(storage_manager* storage) {

    auto ev_roi  = storage->get_data<event_PiZeroROI>( "mcroi" );
    auto ev_vtx  = storage->get_data<event_vertex>   ( "mcroi" );
    auto ev_ass  = storage->get_data<event_ass>      ( "mcroi" );
    std::vector<std::vector<unsigned int> > roi_vtx_ass_v;

    // turns out it is nontrival to pass std::vector<data_base> inheritor generically
    // to algorithm without factory implementation, just send it storage_manager who gives a shit
    _ralgo->Clear();

    std::vector<double> xyz;

    if ( ! _ralgo->FindROI(storage,_producer, xyz) ) return false;
    
    PiZeroROI proi(_ralgo->wirerange,_ralgo->timerange);
    proi.SetVertex(_ralgo->vertex);
    proi.SetPiZeroROI(_ralgo->wirerange,_ralgo->timerange);

    proi.SetTrackEnd(_ralgo->vertex);
    
    ev_roi->emplace_back(proi);

    std::cout << "found vertex : [" << xyz[0] << ", " << xyz[1] << ", " << xyz[2] << "]" << std::endl;

    Double_t vtx_xyz[3];
    vtx_xyz[0] = xyz[0];
    vtx_xyz[1] = xyz[1];
    vtx_xyz[2] = xyz[2];

    std::vector<float> vtxx = {(float)xyz[0],(float)xyz[1],(float)xyz[2]};
    
    proi.SetMuonVertex(vtxx);
    proi.SetNeutrinoVertex(vtxx);
    proi.SetCCIncVertex(vtxx);  
    
    vertex vtx(vtx_xyz,0);
    
    ev_vtx->emplace_back(vtx);

    // fill assocaition
    // since only 1 element (0th) in each, this is easy
    std::vector<unsigned int> ass = {0};
    roi_vtx_ass_v.push_back( ass );
    ev_ass->set_association(ev_roi->id(), product_id(data::kVertex,"mcroi"), roi_vtx_ass_v);
    
    
    return true;
  }

  bool MCROI::finalize() { return true; }

}
#endif







