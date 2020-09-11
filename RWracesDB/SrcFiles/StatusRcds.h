// Status Records


#pragma once
#include "CSVRcdB.h"
#include "CSVRcdsT.h"


class StatusRcd : public CSVRcdB {
public:
String callSign;
String activeFlag;
String activeStatus;
String dispatchable;
String workEOC;
String eligibleForBadge;

  StatusRcd() { }
  StatusRcd(StatusRcd& r) {copy(r);}
 ~StatusRcd() { }

  virtual void clear() {callSign.clear();      activeFlag.clear();   activeStatus.clear();
                        dispatchable.clear();  workEOC.clear();      eligibleForBadge.clear();
                        }

  virtual StatusRcd& operator= (StatusRcd& r) {copy(r); return *this;}

  virtual bool operator>= (StatusRcd& r) {return callSign >= r.callSign;}
  virtual bool operator== (StatusRcd& r) {return callSign == r.callSign;}

private:

  virtual void    put(TCchar* p);
  virtual String* get();
  virtual void    copy(StatusRcd& r);
  };


typedef RcdPtrT< StatusRcd> StatusRcdP;
typedef CSVRcdsT<StatusRcd, StatusRcdP> StatusRcds;
typedef CSVIterT<StatusRcd, StatusRcdP> StsIter;

extern StatusRcds statusRcds;


