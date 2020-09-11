// Create Everbridge csv file

#include "stdafx.h"
#include "RWracesDBDoc.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Utilities.h"

/*
//First Name,Middle Initial,Last Name,Suffix,External ID,                                         // 5
//Country,Business Name,Record Type,Groups,SSO User ID,Group Remove,                              // 6
//Location 1,Street Address 1,Apt/Suite/Unit 1,City 1,State/Province 1,Postal Code 1,             // 6
//Country 1,Latitude 1,Longitude 1,Location Id 1,                                                 // 4
//Location 2,Street Address 2,Apt/Suite/Unit 2,City 2,State/Province 2,Postal Code 2,             // 6
//Country 2,Latitude 2,Longitude 2,Location Id 2,                                                 // 4
//Location 3,Street Address 3,Apt/Suite/Unit 3,City 3,State/Province 3,Postal Code 3,             // 6
//Country 3,Latitude 3,Longitude 3,Location Id 3,                                                 // 4
//Location 4,Street Address 4,Apt/Suite/Unit 4,City 4,State/Province 4,Postal Code 4,             // 6
//Country 4,Latitude 4,Longitude 4,Location Id 4,                                                 // 4
//Location 5,Street Address 5,Apt/Suite/Unit 5,City 5,State/Province 5,Postal Code 5,             // 6
//Country 5,Latitude 5,Longitude 5,Location Id 5,                                                 // 4
//Extension Phone 1,Extension 1,Extension Phone Country 1,                                        // 3
//Extension Phone 2,Extension 2,Extension Phone Country 2,                                        // 3
//Extension Phone 3,Extension 3,Extension Phone Country 3,                                        // 3
//Extension Phone 4,Extension 4,Extension Phone Country 4,                                        // 3
//Extension Phone 5,Extension 5,Extension Phone Country 5,                                        // 3
//Phone 1,Phone Country 1,Phone 2,Phone Country 2,Phone 3,Phone Country 3,                        // 6
//Phone 4,Phone Country 4,Phone 5,Phone Country 5,Phone 6,Phone Country 6,                        // 6
//Email Address 1,Email Address 2,Email Address 3,Email Address 4,Email Address 5,                // 5
//Plain Text Email - 1 way,Plain Text - 1 way Pager Service,                                      // 2
//Plain Text Email - 2 way,                                                                       // 1
//SMS 1,SMS 1 Country,SMS 2,SMS 2 Country,SMS 3,SMS 3 Country,                                    // 6
//SMS 4,SMS 4 Country,SMS 5,SMS 5 Country,                                                        // 4
//FAX 1,FAX Country 1,FAX 2,FAX Country 2,FAX 3,FAX Country 3,                                    // 6
//TTY 1,TTY Country 1,TTY 2,TTY Country 2,TTY 3,TTY Country 3,                                    // 6
//Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,                    // 4
//TAP Pager,TAP Pager Country,TAP Pager Pin,                                                      // 3
//One Way SMS,One Way SMS Country,                                                                // 2
//Custom Field 1,Custom Value 1,Custom Field 2,Custom Value 2,Custom Field 3,Custom Value 3,      // 6
//Custom Field 4,Custom Value 4,Custom Field 5,Custom Value 5,Custom Field 6,Custom Value 6,      // 6
//Custom Field 7,Custom Value 7,Custom Field 8,Custom Value 8,Custom Field 9,Custom Value 9,END   // 6
*/


void RWracesDBDoc::ebHeader() {

  notePad.clear();

  notePad << _T("First Name,");
  notePad << _T("Middle Initial,");
  notePad << _T("Last Name,");
  notePad << _T("Suffix,");
  notePad << _T("External ID,");
  notePad << _T("Country,");
  notePad << _T("Business Name,");
  notePad << _T("Record Type,");
  notePad << _T("Groups,");
  notePad << _T("SSO User ID,");
  notePad << _T("Travel Arranger,");
  notePad << _T("Location 1,");
  notePad << _T("Street Address 1,");
  notePad << _T("Apt/Suite/Unit 1,");
  notePad << _T("City 1,");
  notePad << _T("State/Province 1,");
  notePad << _T("Postal Code 1,");
  notePad << _T("Country 1,");
  notePad << _T("Latitude 1,");
  notePad << _T("Longitude 1,");
  notePad << _T("Location Id 1,");
  notePad << _T("Location 2,");
  notePad << _T("Street Address 2,");
  notePad << _T("Apt/Suite/Unit 2,");
  notePad << _T("City 2,");
  notePad << _T("State/Province 2,");
  notePad << _T("Postal Code 2,");
  notePad << _T("Country 2,");
  notePad << _T("Latitude 2,");
  notePad << _T("Longitude 2,");
  notePad << _T("Location Id 2,");
  notePad << _T("Location 3,");
  notePad << _T("Street Address 3,");
  notePad << _T("Apt/Suite/Unit 3,");
  notePad << _T("City 3,");
  notePad << _T("State/Province 3,");
  notePad << _T("Postal Code 3,");
  notePad << _T("Country 3,");
  notePad << _T("Latitude 3,");
  notePad << _T("Longitude 3,");
  notePad << _T("Location Id 3,");
  notePad << _T("Location 4,");
  notePad << _T("Street Address 4,");
  notePad << _T("Apt/Suite/Unit 4,");
  notePad << _T("City 4,");
  notePad << _T("State/Province 4,");
  notePad << _T("Postal Code 4,");
  notePad << _T("Country 4,");
  notePad << _T("Latitude 4,");
  notePad << _T("Longitude 4,");
  notePad << _T("Location Id 4,");
  notePad << _T("Location 5,");
  notePad << _T("Street Address 5,");
  notePad << _T("Apt/Suite/Unit 5,");
  notePad << _T("City 5,");
  notePad << _T("State/Province 5,");
  notePad << _T("Postal Code 5,");
  notePad << _T("Country 5,");
  notePad << _T("Latitude 5,");
  notePad << _T("Longitude 5,");
  notePad << _T("Location Id 5,");
  notePad << _T("Extension Phone 1,");
  notePad << _T("Extension 1,");
  notePad << _T("Extension Phone Country 1,");
  notePad << _T("Extension Phone 2,");
  notePad << _T("Extension 2,");
  notePad << _T("Extension Phone Country 2,");
  notePad << _T("Extension Phone 3,");
  notePad << _T("Extension 3,");
  notePad << _T("Extension Phone Country 3,");
  notePad << _T("Extension Phone 4,");
  notePad << _T("Extension 4,");
  notePad << _T("Extension Phone Country 4,");
  notePad << _T("Extension Phone 5,");
  notePad << _T("Extension 5,");
  notePad << _T("Extension Phone Country 5,");
  notePad << _T("Phone 1,");
  notePad << _T("Phone Country 1,");
  notePad << _T("Phone 2,");
  notePad << _T("Phone Country 2,");
  notePad << _T("Phone 3,");
  notePad << _T("Phone Country 3,");
  notePad << _T("Phone 4,");
  notePad << _T("Phone Country 4,");
  notePad << _T("Phone 5,");
  notePad << _T("Phone Country 5,");
  notePad << _T("Phone 6,");
  notePad << _T("Phone Country 6,");
  notePad << _T("");
  notePad << _T("Email Address 1,");
  notePad << _T("Email Address 2,");
  notePad << _T("Email Address 3,");
  notePad << _T("Email Address 4,");
  notePad << _T("Email Address 5,");
  notePad << _T("Plain Text Email - 1 way,");
  notePad << _T("Plain Text - 1 way Pager Service,");
  notePad << _T("Plain Text Email - 2 way,");
  notePad << _T("SMS 1,");
  notePad << _T("SMS 1 Country,");
  notePad << _T("SMS 2,");
  notePad << _T("SMS 2 Country,");
  notePad << _T("SMS 3,");
  notePad << _T("SMS 3 Country,");
  notePad << _T("SMS 4,");
  notePad << _T("SMS 4 Country,");
  notePad << _T("SMS 5,");
  notePad << _T("SMS 5 Country,");
  notePad << _T("FAX 1,");
  notePad << _T("FAX Country 1,");
  notePad << _T("FAX 2,");
  notePad << _T("FAX Country 2,");
  notePad << _T("FAX 3,");
  notePad << _T("FAX Country 3,");
  notePad << _T("TTY 1,");
  notePad << _T("TTY Country 1,");
  notePad << _T("TTY 2,");
  notePad << _T("TTY Country 2,");
  notePad << _T("TTY 3,");
  notePad << _T("TTY Country 3,");
  notePad << _T("Numeric Pager,");
  notePad << _T("Numeric Pager Country,");
  notePad << _T("Numeric Pager Pin,");
  notePad << _T("Numeric Pager Service,");
  notePad << _T("TAP Pager,");
  notePad << _T("TAP Pager Country,");
  notePad << _T("TAP Pager Pin,");
  notePad << _T("One Way SMS,");
  notePad << _T("One Way SMS Country,");
  notePad << _T("Custom Field 1,");
  notePad << _T("Custom Value 1,");
  notePad << _T("Custom Field 2,");
  notePad << _T("Custom Value 2,");
  notePad << _T("Custom Field 3,");
  notePad << _T("Custom Value 3,");
  notePad << _T("Custom Field 4,");
  notePad << _T("Custom Value 4,");
  notePad << _T("Custom Field 5,");
  notePad << _T("Custom Value 5,");
  notePad << _T("Custom Field 6,");
  notePad << _T("Custom Value 6,");
  notePad << _T("Custom Field 7,");
  notePad << _T("Custom Value 7,");
  notePad << _T("Custom Field 8,");
  notePad << _T("Custom Value 8,");
  notePad << _T("Custom Field 9,");
  notePad << _T("Custom Value 9,");
  notePad << _T("Custom Field 10,");
  notePad << _T("Custom Value 10,");
  notePad << _T("Custom Field 11,");
  notePad << _T("Custom Value 11,");
  notePad << _T("Custom Field 12,");
  notePad << _T("Custom Value 12,");
  notePad << _T("Custom Field 13,");
  notePad << _T("Custom Value 13,");
  notePad << _T("Custom Field 14,");
  notePad << _T("Custom Value 14,");
  notePad << _T("END");

  notePad << nCrlf;
  }

/*
//First Name,Middle Initial,Last Name,Suffix,External ID,                                         // 5
Craig,,Anderson,,RACES-N6YXK,

//Country,Business Name,Record Type,Groups,SSO User ID,Group Remove,                              // 6
US,,RACES,SJS RACES|SJS RACES 5 No Dispatch,,,

//Location 1,Street Address 1,Apt/Suite/Unit 1,City 1,State/Province 1,Postal Code 1,             // 6
Home,14656 Bronson Avenue,,San Jose,CA,95124,

//Country 1,Latitude 1,Longitude 1,Location Id 1,                                                 // 4
US,37.25438,-121.92522,,

//Location 2,Street Address 2,Apt/Suite/Unit 2,City 2,State/Province 2,Postal Code 2,             // 6
,,,,,,
//Country 2,Latitude 2,Longitude 2,Location Id 2,                                                 // 4
,,,,
//Location 3,Street Address 3,Apt/Suite/Unit 3,City 3,State/Province 3,Postal Code 3,             // 6
,,,,,,
//Country 3,Latitude 3,Longitude 3,Location Id 3,                                                 // 4
,,,,
//Location 4,Street Address 4,Apt/Suite/Unit 4,City 4,State/Province 4,Postal Code 4,             // 6
,,,,,,
//Country 4,Latitude 4,Longitude 4,Location Id 4,                                                 // 4
,,,,
//Location 5,Street Address 5,Apt/Suite/Unit 5,City 5,State/Province 5,Postal Code 5,             // 6
,,,,,,
//Country 5,Latitude 5,Longitude 5,Location Id 5,                                                 // 4
,,,,

//Extension Phone 1,Extension 1,Extension Phone Country 1,                                        // 3
,,,
//Extension Phone 2,Extension 2,Extension Phone Country 2,                                        // 3
,,,
//Extension Phone 3,Extension 3,Extension Phone Country 3,                                        // 3
,,,
//Extension Phone 4,Extension 4,Extension Phone Country 4,                                        // 3
,,,
//Extension Phone 5,Extension 5,Extension Phone Country 5,                                        // 3
,,,
      Cell                       Work?                       Home
//Phone 1,Phone Country 1,Phone 2,Phone Country 2,Phone 3,Phone Country 3,                        // 6
4087686025,US,,,4083718904,US,

//Phone 4,Phone Country 4,Phone 5,Phone Country 5,Phone 6,Phone Country 6,                        // 6
,,,,,,
//Email Address 1,Email Address 2,Email Address 3,Email Address 4,Email Address 5,                // 5
,acraiga@pacbell.net,,,,

//Plain Text Email - 1 way,Plain Text - 1 way Pager Service,                                      // 2
,,
//Plain Text Email - 2 way,                                                                       // 1
,
//SMS 1,SMS 1 Country,SMS 2,SMS 2 Country,SMS 3,SMS 3 Country,                                    // 6
4087686025,US,,,,,
//SMS 4,SMS 4 Country,SMS 5,SMS 5 Country,                                                        // 4
,,,,
//FAX 1,FAX Country 1,FAX 2,FAX Country 2,FAX 3,FAX Country 3,                                    // 6
,,,,,,
//TTY 1,TTY Country 1,TTY 2,TTY Country 2,TTY 3,TTY Country 3,                                    // 6
,,,,,,
//Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,                    // 4
,,,,
//TAP Pager,TAP Pager Country,TAP Pager Pin,                                                      // 3
,,,
//One Way SMS,One Way SMS Country,                                                                // 2
,,
//Custom Field 1,Custom Value 1,Custom Field 2,Custom Value 2,Custom Field 3,Custom Value 3,      // 6
,Certifications,RACES,,,,
//Custom Field 4,Custom Value 4,Custom Field 5,Custom Value 5,Custom Field 6,Custom Value 6,      // 6
,,,,,,
//Custom Field 7,Custom Value 7,Custom Field 8,Custom Value 8,Custom Field 9,Custom Value 9,END   // 6
,,,,,,
,,,,,,,,,,END
*/

/*


Scott,L,Bordelon,,RACES-K6SLB,US,,RACES,SJS RACES|SJS RACES 1 Priority|SJS RACES 0 Officers,,,
Home,5659 Algonquin Way,,San Jose,CA,951382245,US,37.27084,-121.7694,,
Work,150 Rose Orchard Way,,San Jose,CA,95134,US,37.41737,-121.94735,,
,,,,,,,,,,END


//First Name,Middle Initial,Last Name,Suffix,External ID,                                         // 5
//Scott,L,Bordelon,,RACES-K6SLB

//Country,Business Name,Record Type,Groups,SSO User ID,Group Remove,                              // 6
//US,,RACES,SJS RACES|SJS RACES 1 Priority|SJS RACES 0 Officers,,,

//Location 1,Street Address 1,Apt/Suite/Unit 1,City 1,State/Province 1,Postal Code 1,             // 6
Home,5659 Algonquin Way,,San Jose,CA,951382245,

//Country 1,Latitude 1,Longitude 1,Location Id 1,                                                 // 4
US,37.27084,-121.7694,,

//Location 2,Street Address 2,Apt/Suite/Unit 2,City 2,State/Province 2,Postal Code 2,             // 6
Work,150 Rose Orchard Way,,San Jose,CA,95134

//Country 2,Latitude 2,Longitude 2,Location Id 2,                                                 // 4
US,37.41737,-121.94735,,

//Location 3,Street Address 3,Apt/Suite/Unit 3,City 3,State/Province 3,Postal Code 3,             // 6
,,,,,,
//Country 3,Latitude 3,Longitude 3,Location Id 3,                                                 // 4
,,,,
//Location 4,Street Address 4,Apt/Suite/Unit 4,City 4,State/Province 4,Postal Code 4,             // 6
,,,,,,
//Country 4,Latitude 4,Longitude 4,Location Id 4,                                                 // 4
,,,,
//Location 5,Street Address 5,Apt/Suite/Unit 5,City 5,State/Province 5,Postal Code 5,             // 6
,,,,,,
//Country 5,Latitude 5,Longitude 5,Location Id 5,                                                 // 4
,,,,
//Extension Phone 1,Extension 1,Extension Phone Country 1,                                        // 3
,,,
//Extension Phone 2,Extension 2,Extension Phone Country 2,                                        // 3
,,,
//Extension Phone 3,Extension 3,Extension Phone Country 3,                                        // 3
,,,
//Extension Phone 4,Extension 4,Extension Phone Country 4,                                        // 3
,,,
//Extension Phone 5,Extension 5,Extension Phone Country 5,                                        // 3
,,,
//Phone 1,Phone Country 1,Phone 2,Phone Country 2,Phone 3,Phone Country 3,                        // 6
4084311862,US,4085761341,US,4082700422,US,
//Phone 4,Phone Country 4,Phone 5,Phone Country 5,Phone 6,Phone Country 6,                        // 6
,,,,,,
//Email Address 1,Email Address 2,Email Address 3,Email Address 4,Email Address 5,                // 5
scott.bordelon@intel.com,scott.bordelon@gmail.com,,,,
//Plain Text Email - 1 way,Plain Text - 1 way Pager Service,                                      // 2
,,
//Plain Text Email - 2 way,                                                                       // 1
,
//SMS 1,SMS 1 Country,SMS 2,SMS 2 Country,SMS 3,SMS 3 Country,                                    // 6
4084311862,US,,,,,
//SMS 4,SMS 4 Country,SMS 5,SMS 5 Country,                                                        // 4
,,,,
//FAX 1,FAX Country 1,FAX 2,FAX Country 2,FAX 3,FAX Country 3,                                    // 6
,,,,,,
//TTY 1,TTY Country 1,TTY 2,TTY Country 2,TTY 3,TTY Country 3,                                    // 6
,,,,,,
//Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,                    // 4
,,,,
//TAP Pager,TAP Pager Country,TAP Pager Pin,                                                      // 3
,,,
//One Way SMS,One Way SMS Country,                                                                // 2
,,
//Custom Field 1,Custom Value 1,Custom Field 2,Custom Value 2,Custom Field 3,Custom Value 3,      // 6
Certifications,RACES,,,,,
//Custom Field 4,Custom Value 4,Custom Field 5,Custom Value 5,Custom Field 6,Custom Value 6,      // 6
,,,,,,
//Custom Field 7,Custom Value 7,Custom Field 8,Custom Value 8,Custom Field 9,Custom Value 9,      // 6
,,,,,,
//END
*/




void RWracesDBDoc::dspOneEverbridgeRcd(MemberRecord& rcd) {
int                 mbrID             = rcd.MbrEntityID;
int                 emplID            = rcd.EmplEntityID;
int                 assgnPrefID       = rcd.AssgnPrefID;
int                 locPrefID         = rcd.LocationPrefID;
int                 statusID          = rcd.StatusID;
String              responder         = rcd.Responder.trim();
String              dsw               = rcd.DSWDate.trim();

EntityRecord*       mbrRcd            = entityTable.find(mbrID);      if (!mbrRcd) return;
EntityRecord*       emplRcd           = entityTable.find(emplID);

AssgnPrefRecord*    assgnPrefRcd      = assgnPrefTable.find(assgnPrefID);
LocationPrefRecord* locationPrefRcd   = locationPrefTable.find(locPrefID);
StatusRecord*       statusRcd         = statusTable.find(statusID);
String              key;
String              s;
String              t;                                              // The empty string

  commaOut();

  ebOut(mbrRcd->FirstName);                                         // First Name
  ebOut(mbrRcd->MiddleInitial);                                     // Middle Initial
  ebOut(mbrRcd->LastName);                                          // Last Name
  ebOut(mbrRcd->Suffix);                                            // Suffix

  s = _T("RACES-") + rcd.CallSign;  ebOut(s);                       // External ID

  s = _T("US"); ebOut(s);                                           // Country

  notePad << _T(",");                                               // Business Name

  s = _T("RACES"); ebOut(s);                                        // Record Type

  s = _T("SJS RACES");

  if (assgnPrefRcd) {
    key = assgnPrefRcd->APKey;
    if      (key == _T("P")) s += _T("|SJS RACES 1 Priority");
    else if (key == _T("E")) s += _T("|SJS RACES 2 Emergency");
    else if (key == _T("G")) s += _T("|SJS RACES 3 General");
    else if (key == _T("L")) s += _T("|SJS RACES 4 Last Resort");
    else if (key == _T("A")) s += _T("|SJS RACES 5 No Dispatch");
    }

  if (rcd.IsOfficer) s += _T("|SJS RACES 0 Officers");
  ebOut(s);                                                         // Groups

  notePad << _T(",,");                                              // SSO User ID,Group Remove,

  s.clear();

  ebLocation(_T("Home"), mbrRcd);                                   // Location 1
  ebLocation(_T("Work"), emplRcd);                                  // Location 2
  ebLocation(0, 0);                                                 // Location 3
  ebLocation(0, 0);                                                 // Location 4
  ebLocation(0, 0);                                                 // Location 5

  emptyFields(3);                                                   // Extension Phone 1
  emptyFields(3);                                                   // Extension Phone 2
  emptyFields(3);                                                   // Extension Phone 3
  emptyFields(3);                                                   // Extension Phone 4
  emptyFields(3);                                                   // Extension Phone 5

  ebPhone(mbrRcd  ? mbrRcd->Phone2  : 0);                            //Phone 1
  ebPhone(emplRcd ? emplRcd->Phone2 : 0);                            //Phone 2
  ebPhone(mbrRcd  ? mbrRcd->Phone1  : 0);                            //Phone 3
  ebPhone(emplRcd ? emplRcd->Phone1 : 0);                            //Phone 4
  ebPhone(0);                                                        //Phone 5
  ebPhone(0);                                                        //Phone 6

  ebEmail(mbrRcd  ?  mbrRcd->eMail : 0);                            // Email Address 1
  ebEmail(emplRcd ? emplRcd->eMail : 0);                            // Email Address 2
  ebOut(0);                                                         // Email Address 3
  ebOut(0);                                                         // Email Address 4
  ebOut(0);                                                         // Email Address 5

  ebOut(0);                                                         // Plain Text Email - 1 way
  ebOut(0);                                                         // Plain Text - 1 way Pager Service

  ebOut(0);                                                         // Plain Text Email - 2 way

  ebPhone(rcd.TextMsgPh1);                                          // SMS 1
  ebPhone(rcd.TextMsgPh2);                                          // SMS 2
  ebPhone(0);                                                       // SMS 3
  ebPhone(0);                                                       // SMS 4
  ebPhone(0);                                                       // SMS 5

  ebPhone(0);                                                       // FAX 1
  ebPhone(0);                                                       // FAX 2
  ebPhone(0);                                                       // FAX 3

  ebPhone(0);                                                       // TTY 1
  ebPhone(0);                                                       // TTY 2
  ebPhone(0);                                                       // TTY 3

  //Numeric Pager,Numeric Pager Country,Numeric Pager Pin,Numeric Pager Service,                    // 4
  emptyFields(4);

  //TAP Pager,TAP Pager Country,TAP Pager Pin,                                                      // 3
  emptyFields(3);

  ebPhone(0);                                                       // One Way SMS

  ebOut(_T("Certifications"));                                      // Custom Field 1
  ebOut(_T("RACES"));                                               // Custom Field 2
  emptyFields(26);
  notePad << _T("END") << nCrlf;
  }



void RWracesDBDoc::ebLocation(TCchar* title, EntityRecord* rcd) {
AddressRecord*   addrRcd = 0;
CityStateRecord* cityRcd = 0;
String           s;
String           t;

  if (rcd) {
    addrRcd = addressTable.find(rcd->AddrID);
    cityRcd = cityStateTable.find(rcd->CityStID);
    }

  if (!rcd || !addrRcd || (addrRcd->Address1.isEmpty() && !rcd->AddrIsPO)) {
    //Location n,Street Address n,Apt/Suite/Unit n,City n,State/Province n,Postal Code n,     // 6
    emptyFields(6);
    //Country n,Latitude n,Longitude n,Location Id n,                                         // 4
    emptyFields(4);   return;
    }

  ebOut(title);                                                                 // Location n

  if (rcd->AddrIsPO) {                                                          // Street Address n
    s = !addrRcd->Address1.isEmpty() ? addrRcd->Address1 : _T("PO Box 1234");  ebOut(s);
    ebOut(t);                                                                   // Apt/Suite/Unit n

    if (cityRcd) {
      s = !cityRcd->City.isEmpty()   ? cityRcd->City     : _T("San Jose");     ebOut(s); // City n
      s = !cityRcd->State.isEmpty()  ? cityRcd->State    : _T("CA");           ebOut(s); // State/Province
      ebOut(cityRcd->Zip);                                                      // Postal Code 1
      }
    else {
      s = _T("San Jose"); ebOut(s);                                             // City n
      s = _T(" CA");      ebOut(s);                                             // State/Province n
      ebOut(rcd->LocationZip);                                                  // Postal Code 1
      }
    }

  else {
    ebOut(addrRcd->Address1);                                                   // Street Address n
    ebOut(addrRcd->Address2);                                                   // Apt/Suite/Unit n

    if (cityRcd) {
      s = !cityRcd->City.isEmpty()  ? cityRcd->City  : _T("San Jose");  ebOut(s); // City n
      s = !cityRcd->State.isEmpty() ? cityRcd->State : _T(" CA");       ebOut(s); // State/Province n
      ebOut(cityRcd->Zip);                                                        // Postal Code n
      }
    else {
      s = _T("San Jose"); ebOut(s);                                               // City n
      s = _T(" CA");      ebOut(s);                                               // State/Province n
      emptyFields(1);                                                              // Postal Code n
      }
    }

  //Country 1,Latitude 1,Longitude 1,Location Id 1,                                     // 4

  s = _T("US"); ebOut(s);   emptyFields(3);
  }


void RWracesDBDoc::ebEmail(TCchar* em) {
String s;

  if (!em || !*em) {emptyFields(1); return;}

  s = em;  if (s.length() == 1) {emptyFields(1); return;}

  s = quotes(em);  notePad << s << _T(',');
  }


//Phone 1,Phone Country 1,

void RWracesDBDoc::ebPhone(TCchar* ph) {
String s;

  if (!ph || !*ph) {emptyFields(2); return;}

  s = ph;   if (s.length() == 1) {emptyFields(2); return;}

  ebOut(ph);                                                                      // Phone n
  ebOut(_T("US"));                                                                // Phone Country n
  }



void RWracesDBDoc::ebOut(TCchar* p) {
String s;

  if (!p || !*p) {emptyFields(1); return;}

  s = quotes(p);  notePad << s << _T(',');
  }



static String Commas = _T(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,");

void RWracesDBDoc::emptyFields(int n) {String s = Commas.substr(0, n);   notePad << s;}

