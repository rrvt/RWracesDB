

RWracesDB.chm : *.htm RWracesDB.hhp RWracesDB.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" RWracesDB


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F RWracesDB.chm


Release/RWracesDB.chm : RWracesDB.chm
  copy $(MAKEDIR)\RWracesDB.chm  $(MAKEDIR)\..\Release\RWracesDB.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del RWracesDB.chm
  cd $(MAKEDIR)


Debug/RWracesDB.chm : RWracesDB.chm
  copy $(MAKEDIR)\RWracesDB.chm  $(MAKEDIR)\..\Debug\RWracesDB.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del RWracesDB.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/RWracesDB.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/RWracesDB.chm


