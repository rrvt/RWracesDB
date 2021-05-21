// Defines all Database Tables and a list of them
// The DBtable object must be defined before the individual table objects.
// This module determines the order of initialization.


#include "stdafx.h"
#include "DBtables.h"
#include "AddressTbl.h"
#include "AssgnPrefTbl.h"
#include "CityStateTbl.h"
#include "DAOtables.h"
#include "EntityTbl.h"
#include "LocationPrefTbl.h"
#include "MemberTbl.h"
#include "StatusTbl.h"


DAOtables       daoTables;
DBtables        dbTables;
AddressTbl      addressTbl;
AssgnPrefTbl    assgnPrefTbl;
CityStateTbl    cityStateTbl;
EntityTbl       entityTbl;
LocationPrefTbl locationPrefTbl;
MemberTbl       memberTbl;
StatusTbl       statusTbl;
