echo off

rem �ݹ�ɾ����ǰ�ļ��У�".\"��"./"����ָ����չ�����ļ�

rem �����Ҫ�����������չ���ļ���������del��ͷ�ĸ�ʽ�У�������Ӷ�Ӧ����չ������

rem ���del��չ����ע�⣺��".res"�����".resx"���ļ�Ҳɾ������C#���õ�".resx"�ļ�������

rem ��rem����ͷ������Ϊע����䣬��������

set /p VAR=�Ƿ�ɾ��ָ���ļ�����ѡ��[Y, N]?

rem echo %VAR%

if /i '%VAR%' == 'y' goto s1
if /i '%VAR%' == 'n' goto end

:s1
for /f "delims=" %%a in ('dir . /b /ad /s ^|sort /r' ) do rd /q "%%a" 2>nul
)

for /d %%i in (.\) do (cd %%i
	del /s *.mdp
	del /s *.clw
	del /s *.cpl
	del /s *awk
	del /s *.map
	del /s *.scc
	del /s *.tlb
	del /s *.ncb
	del /s *.opt
	del /s *.plg
	del /s *.aps
	del /s *.res
	del /s *.idb
	del /s *.pch
	del /s *.sbr
	del /s *.obj
	del /s *.ilk
	del /s *.bsc
	del /s *.fd
	del /s *.bak
	del /s *tlh
	del /s *.tli
	del /s *.pdb
	del /s *.exp
	del /s *.positions
	del /s *.tlog
	del /s *.log
	del /s *.lastbuildstate
	del /s *.sdf
	del /s *.ipch
	del /s *.manifest
	del /s *.user
	rd /s /q ipch
	rd /s /q _UpgradeReport_Files
	del /s UpgradeLog.XML
	del /s UpgradeLog2.XML
	rd /s /q Debug
	rd /s /q Release
	rd /s /q Win32
	
	cd ..)
for /r %%i in (.\) do (cd %%i
	rd /s /q Debug
	rd /s /q Release
	rd /s /q GeneratedFiles
	cd ..)
:end
pause 



