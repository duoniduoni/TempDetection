; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "TempDetection"
#define MyAppVersion "2.0.1"
#define MyAppPublisher "北京华朔物联网科技有限公司"
#define MyAppURL "http://www.hshiot.com/"
#define MyAppExeName "TempDetection.exe"

[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppId={{9D695402-33C6-4657-96C8-E8070C02AA08}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DisableProgramGroupPage=yes
OutputDir=D:\my_project\OutExe
OutputBaseFilename=setup
SetupIconFile=D:\my_project\TempDetection+V2.0+2016.1.22\TempDetection V2.0 2016.1.22\TempDetection\res\TempDetection.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "D:\my_project\TempDetection+V2.0+2016.1.22\TempDetection V2.0 2016.1.22\Release\TempDetection.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\my_project\TempDetection+V2.0+2016.1.22\TempDetection V2.0 2016.1.22\Debug\ReaderConfigFiles\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\my_project\TempDetection+V2.0+2016.1.22\TempDetection V2.0 2016.1.22\Release\Alarm.wav"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\my_project\TempDetection+V2.0+2016.1.22\TempDetection V2.0 2016.1.22\Release\SysLog.log"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\my_project\TempDetection+V2.0+2016.1.22\TempDetection V2.0 2016.1.22\Release\SystemInstall.ini"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Windows\SysWOW64\iPlotLibrary.tlb"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Windows\SysWOW64\MSCOMM32.OCX"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Windows\SysWOW64\TeeChart8.ocx"; DestDir: "{app}"; Flags: ignoreversion
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

