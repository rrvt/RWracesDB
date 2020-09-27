// ToolBar Combo Box


#pragma once


class TBComboBox : public CMFCToolBarComboBoxButton {

public:

  TBComboBox() { }
  TBComboBox(uint uiID, int image, DWORD style = CBS_DROPDOWNLIST, int width=0) :
                                                CMFCToolBarComboBoxButton(uiID, image, style, width) { }
 ~TBComboBox() { }

  static TBComboBox* get(int id) {return (TBComboBox*) GetByCmd((uint)id);}

  int findExact(TCchar* tc) {String s = tc; return findExact(s);}
  int findExact(String& s);
  };

