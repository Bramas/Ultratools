; -- Example2.iss --
; Same as Example1.iss, but creates its icon in the Programs folder of the
; Start Menu instead of in a subfolder, and also creates a desktop icon.

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!

[Setup]   
DirExistsWarning=no
;PrivilegesRequired=lowest
;DisableDirPage=yes
UsePreviousAppDir=yes
AppName=Ultratools Editor          
AppVersion=1.6
DefaultDirName={pf}\Ultratools
; Since no icons will be created in "{group}", we don't need the wizard
; to ask for a Start Menu folder name:
DisableProgramGroupPage=yes
UninstallDisplayIcon={app}\UltratoolsEditor.exe
OutputDir=..            
SetupIconFile=../src/icone/logo2.ico
ChangesAssociations=yes
                       
#define BuilLocation "..\..\build\UltraTools Editor-Desktop_Qt_5_4_1_MinGW_32bit-Release\release"
#define FmodEXLocation "C:\FMODEx\api"
#define QtLocation "C:\Qt\5.4\mingw491_32"
[Run]
[Files]         
Source: "{#BuilLocation}\Ultratools Editor.exe"; DestDir: "{app}"   
Source: "{#QtLocation}\bin\icudt53.dll"; DestDir: "{app}"  
Source: "{#QtLocation}\bin\icuin53.dll"; DestDir: "{app}"  
Source: "{#QtLocation}\bin\icuuc53.dll"; DestDir: "{app}"      
Source: "{#QtLocation}\bin\libgcc_s_dw2-1.dll"; DestDir: "{app}"  
Source: "{#QtLocation}\bin\libstdc++-6.dll"; DestDir: "{app}"  
Source: "{#QtLocation}\bin\libwinpthread-1.dll"; DestDir: "{app}"  
Source: "{#QtLocation}\bin\Qt5Core.dll"; DestDir: "{app}" 
Source: "{#QtLocation}\bin\Qt5Gui.dll"; DestDir: "{app}" 
Source: "{#QtLocation}\bin\Qt5Network.dll"; DestDir: "{app}"  
Source: "{#QtLocation}\bin\Qt5Widgets.dll"; DestDir: "{app}"    
Source: "{#QtLocation}\plugins\platforms\qwindows.dll"; DestDir: "{app}\plugins\platforms"   
Source: "..\src\violon\*"; DestDir: "{app}\violon"     

Source: "{#FmodEXLocation}\fmodex.dll"; DestDir: "{app}"  

                                              
[Icons]
Name: "{commonprograms}\Ultratools Editor"; Filename: "{app}\Ultratools Editor.exe"
Name: "{commondesktop}\Ultratools Editor"; Filename: "{app}\Ultratools Editor.exe"
