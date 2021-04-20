// Status Records


#pragma once
#include "CSVRcdB.h"
#include "CSVRcdsT.h"


class CSVstsRcd : public CSVRcdB {
public:
String callSign;
String activeFlag;
String activeStatus;
String dispatchable;
String workEOC;
String eligibleForBadge;

  CSVstsRcd() { }
  CSVstsRcd(CSVstsRcd& r) {copy(r);}
 ~CSVstsRcd() { }

  virtual void clear() {callSign.clear();      activeFlag.clear();   activeStatus.clear();
                        dispatchable.clear();  workEOC.clear();      eligibleForBadge.clear();
                        }

  virtual CSVstsRcd& operator= (CSVstsRcd& r) {copy(r); return *this;}

  virtual bool operator>= (CSVstsRcd& r) {return callSign >= r.callSign;}
  virtual bool operator== (CSVstsRcd& r) {return callSign == r.callSign;}

private:

  virtual void    put(TCchar* p);
  virtual String* get();
  virtual void    copy(CSVstsRcd& r);
  };


typedef RcdPtrT< CSVstsRcd> CSVstsRcdP;
typedef CSVRcdsT<CSVstsRcd, CSVstsRcdP> StatusRcds;
typedef CSVIterT<CSVstsRcd, CSVstsRcdP> SRcdIter;

extern StatusRcds statusRcds;


