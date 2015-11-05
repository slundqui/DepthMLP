/**
 * BaseLayer.hpp
 *
 * The base abstract layer
 * Each layer must define 3 methods: parameterSetting, initialization, and update
 * 
 * Each layer must also define a buffer.
 * AData: The unit activation buffer to be passed onto the next layer via convolution
 *
 * Author: Sheng Lundquist
 **/
#ifndef BASELAYER_HPP_ 
#define BASELAYER_HPP_ 

#include "includes.hpp"
#include "../BaseData.hpp"
#include "../connections/BaseConnection.hpp"


class Column;

class BaseLayer: public BaseData {
public:
   BaseLayer();
   virtual ~BaseLayer();
   virtual int initialize();
   virtual int setParams(
         Column* c,
         std::string layerName,
         int stride,
         int num_features);
   void setPrev(BaseConnection* inConn){prevConn = inConn;}
   void setNext(BaseConnection* inConn){nextConn = inConn;}
   BaseConnection* getPrev(){return prevConn;};
   BaseConnection* getNext(){return nextConn;};

   //TODO make virtual, but need to change test
   virtual int forwardUpdate(int timestep){};
   virtual int backwardsUpdate(int timestep){};

   //Note: this function is inefficient, only use for debugging
   //Caller's responsible for freeing memory
   float * getDeviceAct();
protected:
   float * d_AData; //Device memory
   //float * h_AData; //Host memory
   int bSize, ySize, xSize, fSize;
   int stride;

private:
   BaseConnection* prevConn;
   BaseConnection* nextConn;

};
#endif 
