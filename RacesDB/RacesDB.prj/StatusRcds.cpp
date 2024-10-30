// Status Records


#include "pch.h"
#include "StatusRcds.h"


StatusRcds statusRcds;


void    CSVstsRcd::put(TCchar* p) {
  switch (putI) {
    case 0: callSign    = p; break;
    case 1: lastName    = p; break;
    case 2: firstName   = p; break;
    case 3: activityCnt = p; break;
    }
  }


String* CSVstsRcd::get() {
  switch (getI) {
    case 0: return &callSign;
    case 1: return &lastName;
    case 2: return &firstName;
    case 3: return &activityCnt;
    }
  return 0;
  }


void CSVstsRcd::copy(CSVstsRcd& r) {
  callSign    = r.callSign;
  lastName    = r.lastName;
  firstName   = r.firstName;
  activityCnt = r.activityCnt;
  CSVRcdB::copy(r);
  }


