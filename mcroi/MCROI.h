//by vic
#ifndef LARLITE_MCROI_H
#define LARLITE_MCROI_H

#include <string>

#include "Analysis/ana_base.h"
#include "DataFormat/PiZeroROI.h"
#include "DataFormat/wire.h"
#include "DataFormat/vertex.h"
#include "DataFormat/event_ass.h"

#include "roialgo.h"

namespace larlite {

  class MCROI : public ana_base{
  
  public:

    MCROI() : _ralgo(nullptr) { _name="MCROI"; _fout=0;}
    virtual ~MCROI(){}

    virtual bool initialize();
    virtual bool analyze(storage_manager* storage);
    virtual bool finalize();

    void SetROIAlgo        (roialgo* ralgo) { _ralgo = ralgo; }
    void SetProducer (std::string producer) { _producer = producer; }
    
  private:

    roialgo* _ralgo;
    std::string _producer;
    
  };
}
#endif
