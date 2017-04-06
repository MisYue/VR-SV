echo off

rem 递归删除当前文件夹（".\"或"./"）下指定扩展名的文件

rem 如果想要添加其它的扩展名文件，按下面del开头的格式行，继续添加对应的扩展名即可

rem 添加del扩展名需注意：如".res"，会把".resx"的文件也删除掉（C#中用到".resx"文件）！！

rem 【rem】开头的内容为注释语句，不起作用

set /p VAR=是否删除指定文件，请选择[Y, N]?

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



