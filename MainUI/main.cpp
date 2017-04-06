#include "MainUI.h"
#include <QtGui/QApplication>

#include "../../Public/VRSoft.h"
#include "../../Public/Plugin/PluginDepined.h"

#include <QTextCodec>
#include <QTextEncoder>

#ifdef _DEBUG
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgGAd.lib")
#pragma comment(lib, "osgQtd.lib")
#pragma comment(lib, "osgEarthd.lib")
#pragma comment(lib, "osgEarthUtil.lib")
#else
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osgGA.lib")
#pragma comment(lib, "osgQt.lib")
#pragma comment(lib, "osgEarth.lib")
#pragma comment(lib, "osgEarthUtil.lib")
#endif // _DEBUG


int main(int argc, char *argv[])
{
	VR_Soft::IComManager* pComManager = VR_Soft::CreateInstance(argc, argv);
	if (NULL == pComManager)
	{
		return (0);
	}
	// 初始化组件
	VR_Soft::IComManager::GetInstance().InitCom();
	pComManager->EnableServer(true);


	QApplication a(argc, argv);
	CMainUI w;
	w.show();
	return a.exec();
}
