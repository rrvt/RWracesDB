// Display One Record


#include "stdafx.h"
#include "RWracesDBDoc.h"
#include "MessageBox.h"
#include "NotePad.h"


void RWracesDBDoc::dspOneRecord(MemberRecord& rcd, DspType dspType) {
bool                comparison        = dspType == CmpDspType;
int                 mbrID             = rcd.MbrEntityID;
int                 emplID            = rcd.EmplEntityID;
int                 iceID             = rcd.ICE_EntityID;
int                 assgnPrefID       = rcd.AssgnPrefID;
int                 locPrefID         = rcd.LocationPrefID;
int                 statusID          = rcd.StatusID;

EntityRecord*       mbrRcd            = entityTable.find(mbrID);
EntityRecord*       emplRcd           = entityTable.find(emplID);
EntityRecord*       iceRcd            = entityTable.find(iceID);
AssgnPrefRecord*    assgnPrefRcd      = assgnPrefTable.find(assgnPrefID);
LocationPrefRecord* locationPrefRcd   = locationPrefTable.find(locPrefID);
StatusRecord*       statusRcd         = statusTable.find(statusID);

  this->dspType = dspType;  commaOut();

  notePad << rcd.BadgeNumber << _T(",");

  if (rcd.TextMsgPh1.isEmpty() && mbrRcd && !mbrRcd->Phone2.isEmpty()) {
    rcd.TextMsgPh1 = mbrRcd->Phone2;
    String s = mbrRcd->FirstName + _T(" ") + mbrRcd->LastName + _T("Text Message Dev blank");
    messageBox(s);
    }

  if (!dspEntity(mbrRcd, &rcd)) notePad << _T(",,,,,,,,,,,,,,,");

  quoteStrOut(rcd.TextMsgPh1);
  quoteStrOut(rcd.TextMsgPh2);

  if (comparison) notePad << nCrlf;

  quoteStrOut(rcd.CallSign);

  dateOut(rcd.FCCExpiration);
  dateOut(rcd.StartDate);
  dateOut(rcd.DSWDate);
  dateOut(rcd.BadgeExpDate);
  dateOut(rcd.Responder);

  if (comparison) notePad << nCrlf;

  if (!dspEntity(emplRcd)) notePad << _T(",,,,,,,,,,,,,,");

  if (comparison) notePad << nCrlf;

  if (!dspEntity(iceRcd)) notePad << _T(",,,,,,,,,,,,,,");

  if (comparison) notePad << nCrlf;

  quoteStrOut(rcd.HandHeld);
  quoteStrOut(rcd.PortMobile);
  quoteStrOut(rcd.PortPacket);
  quoteStrOut(rcd.OtherEquip);
  quoteStrOut(rcd.Multilingual);
  quoteStrOut(rcd.OtherCapabilities);

  if (comparison) notePad << nCrlf;

  quoteStrOut(rcd.Limitations);

  if (comparison) notePad << nCrlf;

  if (assgnPrefRcd) {
    quoteStrOut(assgnPrefRcd->APKey);
    quoteStrOut(assgnPrefRcd->Txt);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  if (locationPrefRcd) {
    quoteStrOut(locationPrefRcd->Key);
    quoteStrOut(locationPrefRcd->Txt);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  quoteStrOut(rcd.Comments);

  if (comparison) notePad << nCrlf;

  quoteStrOut(rcd.ShirtSize);
  notePad << rcd.IsOfficer << _T(",");

  if (statusRcd) {
    quoteStrOut(statusRcd->Abbreviation);
    quoteStrOut(statusRcd->Description);
    }
  else notePad << _T(",,");

  if (comparison) notePad << nCrlf;

  quoteStrOut(rcd.SkillCertifications);
  quoteStrOut(rcd.EOC_Certifications);
  quoteStrOut(rcd.UpdateDate);

  notePad << rcd.BadgeOK;

  if (comparison) notePad << nCrlf << _T("-------------<EndRcd>-------------") << nCrlf;

  notePad << nCrlf;
  }


bool RWracesDBDoc::dspEntity(EntityRecord* ent, MemberRecord* rcd) {
AddressRecord*   addrRcd;
CityStateRecord* cityRcd;

  if (!ent) return false;

  quoteStrOut(ent->FirstName);
  quoteStrOut(ent->MiddleInitial);
  quoteStrOut(ent->LastName);
  quoteStrOut(ent->Suffix);

  addrRcd = addressTable.find(ent->AddrID);

  if (addrRcd) {
    quoteStrOut(addrRcd->Address1);
    quoteStrOut(addrRcd->Address2);
    }
  else notePad << _T(",,");

  cityRcd = cityStateTable.find(ent->CityStID);

  if (cityRcd) {
    quoteStrOut(cityRcd->City);
    quoteStrOut(cityRcd->State);
    quoteStrOut(cityRcd->Zip);
    }
  else notePad << _T(",,,");

  notePad << ent->AddrIsPO << _T(",");
  quoteStrOut(ent->LocationZip);
  quoteStrOut(ent->eMail);
  if (rcd) quoteStrOut(rcd->SecondaryEmail);

  quoteStrOut(ent->Phone1);
  quoteStrOut(ent->Phone2);
  return true;
  }



void RWracesDBDoc::dspRecordHeader(bool comparison) {

  notePad.clear();

  notePad << _T("BadgeNumber,");
  notePad << _T("mbrFirstName,");
  notePad << _T("mbrMiddleInitial,");
  notePad << _T("mbrLastName,");
  notePad << _T("mbrSuffix,");
  notePad << _T("mbrStreet,");
  notePad << _T("mbrAptSuite,");
  notePad << _T("mbrCity,");
  notePad << _T("mbrState,");
  notePad << _T("mbrZip,");
  notePad << _T("mbrAddrIsPO,");
  notePad << _T("mbrLocationZip,");
  notePad << _T("mbrPrimaryEmail,");
  notePad << _T("mbrSecondaryEmail,");

  notePad << _T("mbrPhone,");
  notePad << _T("mbrCell,");
  notePad << _T("txtDevPrim,");
  notePad << _T("txtDevSec,");

  if (comparison) notePad << nCrlf;

  notePad << _T("CallSign,");
  notePad << _T("FCCExpiration,");
  notePad << _T("StartDate,");
  notePad << _T("DSWDate,");
  notePad << _T("BadgeExpDate,");
  notePad << _T("Responder,");

  if (comparison) notePad << nCrlf;

  notePad << _T("emplFirstName,");
  notePad << _T("emplMiddleInitial,");
  notePad << _T("emplLastName,");
  notePad << _T("emplSuffix,");
  notePad << _T("emplStreet,");
  notePad << _T("emplAptSuite,");
  notePad << _T("emplCity,");
  notePad << _T("emplState,");
  notePad << _T("emplZip,");
  notePad << _T("emplAddrIsPO,");
  notePad << _T("emplLocationZip,");
  notePad << _T("emplEmail,");
  notePad << _T("emplPhone,");
  notePad << _T("emplCell,");

  if (comparison) notePad << nCrlf;

  notePad << _T("iceFirstName,");
  notePad << _T("iceMiddleInitial,");
  notePad << _T("iceLastName,");
  notePad << _T("iceSuffix,");
  notePad << _T("iceStreet,");
  notePad << _T("iceAptSuite,");
  notePad << _T("iceCity,");
  notePad << _T("iceState,");
  notePad << _T("iceZip,");
  notePad << _T("iceAddrIsPO,");
  notePad << _T("iceLocationZip,");
  notePad << _T("iceEmail,");
  notePad << _T("icePhone,");
  notePad << _T("iceCell,");

  if (comparison) notePad << nCrlf;

  notePad << _T("Handheld,");
  notePad << _T("PortMobile,");
  notePad << _T("PortPacket,");
  notePad << _T("OtherEquip,");
  notePad << _T("Multilingual,");
  notePad << _T("OtherCapabilities,");

  if (comparison) notePad << nCrlf;

  notePad << _T("Limitations,");

  if (comparison) notePad << nCrlf;

  notePad << _T("AssgnPrefKey,");
  notePad << _T("AssgnPrefDsc,");

  if (comparison) notePad << nCrlf;

  notePad << _T("LocationPrefKey,");
  notePad << _T("LocationPref,");

  if (comparison) notePad << nCrlf;

  notePad << _T("Comments,");

  if (comparison) notePad << nCrlf;

  notePad << _T("ShirtSize,");
  notePad << _T("IsOfficer,");
  notePad << _T("StatusAbr,");
  notePad << _T("StatusDsc,");

  if (comparison) notePad << nCrlf;

  notePad << _T("SkillCertifications,");
  notePad << _T("EOC_Certifications,");
  notePad << _T("UpdateDate,");
  notePad << _T("BadgeOK");

  if (comparison) notePad << nCrlf << _T("-------------<EndRcd>-------------") << nCrlf;

  notePad << nCrlf;
  }

