// Status Records


#pragma once
#include "CSVRcdB.h"
#include "CSVRcdsT.h"


class CSVstsRcd : public CSVRcdB {
public:
String callSign;
String lastName;
String firstName;
String activityCnt;

  CSVstsRcd() { }
  CSVstsRcd(CSVstsRcd& r) {copy(r);}
 ~CSVstsRcd() { }

  virtual void clear() {callSign.clear(); lastName.clear(); firstName.clear(); activityCnt.clear();}

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


