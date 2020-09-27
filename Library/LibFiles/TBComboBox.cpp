// ToolBar Combo Box


#include "stdafx.h"
#include "TBComboBox.h"


int TBComboBox::findExact(String& s) {
int n = GetCount();
int i;

  for (i = 0; i < n; i++) if (s == GetItem(i)) return i;

  return -1;
  }

