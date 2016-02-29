; qtdesktop-qrdc.nsi
; TODO:
; - Deps: QtGui, QtSvg, QtSql

!define PRODUCT_NAME "QtDesktop-QRDC"
!define PRODUCT_VERSION "0.0.1"
!define PRODUCT_BUILD "0"
!define PRODUCT_PUBLISHER "QtDesktop"
!define PRODUCT_WEB_SITE "http://www.qtdesktop.org/"
!define PRODUCT_DIR_REGKEY "Software\QtDesktop\QRDC"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_REGVAL "NSIS:StartMenuDir"

SetCompressor lzma
BrandingText "www.qtdesktop.org"
XPStyle on
RequestExecutionLevel admin

!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING

; Language Selection Dialog Settings
!define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"

; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!define MUI_LICENSEPAGE_RADIOBUTTONS
!insertmacro MUI_PAGE_LICENSE "gpl.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Start menu page
var ICONS_GROUP
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "QtDesktop\QRDC"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${PRODUCT_STARTMENU_REGVAL}"
!insertmacro MUI_PAGE_STARTMENU Application $ICONS_GROUP
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Russian"

; Reserve files
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_NAME}-${PRODUCT_VERSION}-${PRODUCT_BUILD}.exe"
InstallDir "$PROGRAMFILES\QtDesktop\QRDC"
ShowInstDetails show
ShowUnInstDetails show

;--------------------------------
Section ""
  SetOutPath $INSTDIR
  File "bin\qrdc.exe"
SectionEnd

; ==
Function .onInit
  !insertmacro MUI_LANGDLL_DISPLAY
  ; 1. check installed
  ReadRegStr $1 ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" 
  StrCmp $1 "" ChkRTL
    MessageBox MB_OK "${PRODUCT_NAME} already installed."
    Abort
  ; 2. check RTL
  ChkRTL:
  ReadRegStr $1 ${PRODUCT_UNINST_ROOT_KEY} "Software\Microsoft\Windows\CurrentVersion\Uninstall\QtDesktop-RTL" "DisplayName" 
  StrCmp $1 "" 0 ChkLibs
    MessageBox MB_OK "Install QtDesktop-RTL first."
    Abort
  ; 3. check libs
  ChkLibs:
  IfFileExists "$SYSDIR\QtSql4.dll" EndInit
    MessageBox MB_OK "Add Sql to QtDesktop-RTL."
    Abort
  EndInit:
FunctionEnd

Section -AdditionalIcons
  SetOutPath $INSTDIR
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  SetShellVarContext all
  ;CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\$ICONS_GROUP\Uninstall.lnk" "$INSTDIR\uninst.exe"
  !insertmacro MUI_STARTMENU_WRITE_END
SectionEnd

Section -Post
   WriteUninstaller "$INSTDIR\uninst.exe"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\uninst.exe"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "NoModify" "1"
   WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "NoRepair" "1"
SectionEnd

;--------------------------------
; Uninstaller

Section "Uninstall"
  !insertmacro MUI_STARTMENU_GETFOLDER "Application" $ICONS_GROUP
  ; Files
  Delete "$INSTDIR\*.*"
  RMDir "$INSTDIR"
  ; Startmenu
  Delete "$SMPROGRAMS\QtDesktop\QRDC\qrdc.lnk"
  ; Registry
  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  SetAutoClose false
SectionEnd
