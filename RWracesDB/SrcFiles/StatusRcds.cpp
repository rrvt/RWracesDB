// Status Records


#include "stdafx.h"
#include "StatusRcds.h"


StatusRcds statusRcds;


void    StatusRcd::put(TCchar* p) {
  switch (putI) {
    case 0: callSign         = p; break;
    case 1: activeFlag       = p; break;
    case 2: activeStatus     = p; break;
    case 3: dispatchable     = p; break;
    case 4: workEOC          = p; break;
    case 5: eligibleForBadge = p; break;
    }
  }


String* StatusRcd::get() {
  switch (getI) {
    case 0: return &callSign;
    case 1: return &activeFlag;
    case 2: return &activeStatus;
    case 3: return &dispatchable;
    case 4: return &workEOC;
    case 5: return &eligibleForBadge;
    }
  return 0;
  }


void StatusRcd::copy(StatusRcd& r) {
  callSign         = r.callSign;
  activeFlag       = r.activeFlag;
  activeStatus     = r.activeStatus;
  dispatchable     = r.dispatchable;
  workEOC          = r.workEOC;
  eligibleForBadge = r.eligibleForBadge;
  CSVRcdB::copy(r);
  }


