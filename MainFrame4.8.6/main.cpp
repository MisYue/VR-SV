#include "../../Public/VRSoft.h"
#include "../../Public/ComManager/IComManager.h"
#include "MainFrame.h"
#include <QApplication>
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

	//VR_Soft::ISimManager* pISimMgr = VR_Soft::CComManagerImp::GetComponent<VR_Soft::ISimManager>(VR_Soft::INSTANCE_NAME_SIMSYSTEM);
	//if (NULL != pISimMgr)
	//{
	///*	pISimMgr->SetServer(true);
	//	pISimMgr->SetCmd(VR_Soft::ISimManager::Start);*/
	//}

	QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	// 启动动图片
	QString exetopath = QDir::currentPath();
	QSplashScreen screen;  

	CMainFrame *w = new CMainFrame(0,&screen);
//	w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);

//	a.setFont(QFont("微软雅黑"));
//	a.setStyleSheet("QTreeView,QListView,QTableView{ \
//		background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #636363, stop:1 #575757);	\
//border: 0px solid #636363; \
//	selection-background-color: #4D4D4D; \
//	selection-color: #F0F0F0; \
//background: transparent; \
//font:15px; \
//}");
	//w.setGeometry(0, 0, 1920 << 1, 1080);
	w->showMaximized();
	screen.finish(w); 
	//w.show();
	a.exec();

	//VRSOFT_DELETE(pComManager);
	return (0);
}
