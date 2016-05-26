; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "TempDetection"
#define MyAppVersion "2.0.1"
#define MyAppPublisher "������˷�������Ƽ����޹�˾"
#define MyAppURL "http://www.hshiot.com/"
#define MyAppExeName "TempDetection.exe"

[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
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
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

