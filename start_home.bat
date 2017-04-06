echo on 
echo "Set Environment Variables......"
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"  x86

rem 设置OSG相关环境变量
set OSG_VERSION=3.4.0F
set OSG_DIR=F:\open source\osg_and_earth\osg-3.4.0
set OSG_EARTH_DIR=F:\open source\osg_and_earth\osg-earth-2.8
set BOOST_DIR=F:\lib\boost
rem 设置PATH变量
set PATH=%OSG_DIR%\bin;%OSG_DIR%\osgPlugins-%OSG_VERSION%;%OSG_EARTH_DIR%\bin;%PATH%


start cmd /k set

start devenv vr-demonstrate.sln /useenv


echo off