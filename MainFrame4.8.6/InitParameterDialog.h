#ifndef _INITPARAMETERDIALOG_H
#define _INITPARAMETERDIALOG_H
#include <CommonDialog.h>
#include <osgWidget.h>
#include <QThread>


//#include <map>

#include <MeshSupport/QuadMeshingQuad.h>
//#include "BITCoordinateSystemSupport/Bit_LPSRCSBaseInGoble.h"
#include <BITCoordinateSystemSupport/Bit_CSWithExpAndUS.h>
#include <Bit_FragmentAnalyse.h>
#include <MeshSupport/Bit_QuadMeshPlane.h>
#include <HitAndExplosionPointAnalysis/HAE_HitPointAnalysis.h>
#include <MathCalculationSupport/AdvancedMath.h>
#include <WarheadPowerAnalysis/Bit_ShockWaveFieldAnalysis.h>
#include <WarheadPowerAnalysis/Bit_PowerAnalysisBase.h>
#include <Bit_RocketAnalyse.h>
#include "CsvNumDialog.h"

#pragma comment(lib,"ArgumentDiglog.lib")
#pragma comment(lib,"OsgViewerWidget.lib")

class ShockWaveCallBack;
class LineUpDataCallBack;

//毁伤等级
enum DamageLevel
{
	Level_1 = 1,
	Level_2,
	Level_3,
	Level_4,
	Level_5,
	Level_6,
	Level_7,
	Level_8,
	Level_9,
	Level_10
};
//单元格结构体
struct GridUnit
{
	//分割单元ID编号
	int UnitID;
	//碎片个数
	int FragmentsAmount;
	//毁伤等级
	int DamageLevel;
	//冲击波毁伤等级
	int ShackDamageLevel;
	//单元点
	Element_Surface_Quad UnitNode;
	//破片编号
	std::vector<int> FragmentID;

	GridUnit()
	{
		UnitID = 0;
		FragmentsAmount = 0;
		DamageLevel = 0;
		ShackDamageLevel = 0;
	}
	GridUnit& operator= (const GridUnit& sour )
	{
		if (this != &sour)
		{
			this->DamageLevel = sour.DamageLevel;
			this->FragmentID = sour.FragmentID;
			this->FragmentsAmount = sour.FragmentsAmount;
			this->UnitID = sour.UnitID;
			this->UnitNode = sour.UnitNode;
			this->ShackDamageLevel = sour.ShackDamageLevel;
			return *this;
		}
		return *this;
	}

	GridUnit(const GridUnit& sour )
	{
		if (this != &sour)
		{
			this->DamageLevel = sour.DamageLevel;
			this->FragmentID = sour.FragmentID;
			this->FragmentsAmount = sour.FragmentsAmount;
			this->UnitID = sour.UnitID;
			this->UnitNode = sour.UnitNode;
			this->ShackDamageLevel = sour.ShackDamageLevel;
		}
	}
};
///线的结构体
struct FragMentLine
{
	//破片开始点
	CoordinatesPosition _PosBegin;
	//破片末点
	CoordinatesPosition _PosEnd;
	//连线向量
	CoordinatesPosition _PosV;
	//破片是否和目标区域交汇
	bool FragAim;
	FragMentLine()
	{
		FragAim = false;
	}
	FragMentLine& operator= (const FragMentLine& sour )
	{
		if (this != &sour)
		{
			this->_PosBegin = sour._PosBegin;
			this->_PosEnd = sour._PosEnd;
			this->_PosV = sour._PosV;
			this->FragAim = sour.FragAim;
			return *this;
		}
		return *this;
	}

	FragMentLine(const FragMentLine& sour )
	{
		if (this != &sour)
		{
			this->_PosBegin = sour._PosBegin;
			this->_PosEnd = sour._PosEnd;
			this->FragAim = sour.FragAim;
			this->_PosV = sour._PosV;
		}
	}
};
///
class OperationDisplay  : public QObject
{
	Q_OBJECT
public:
	//构造函数
	OperationDisplay();
	//获取界面显示
	void GetViewerWidget();
	//获取单位系统设置
	void GetUnitSeting(Bit_UnitSystem&);
	//获取火箭参数设置
	void GetRockSeting(LGRockParameter&);
	//获取目标区域参数设置
	void GetAreaZoneSeting(TargetAreaParameter&);
	void GetViewerWidget(ViewerWidget* pv);
	double GetDamageAreaData() const;
	double GetMassive() const;
	osg::Group* GetTheRootGroup();
	void SetContrlType(int Itype);
private:
	//交汇界面
	void  InitPlotShrapnelLine();
	//创建坐标系
	void BulidCoordinate(osg::Group *Root,CoordinatesPosition centerPoint,osg::Vec3 RotateAngle,std::string Ctype);
	//创建目标网格
	void BulidAimZoonGrid(osg::Group *root,Bit_AimDataStructure *,std::map<int,GridUnit>&);
	//创建弹体
	void BulidProjectile(osg::Group *root,WarheadPowerAnalysisData &warHead,CoordinatesPosition Frag_HitPosition,osg::Vec3 RotateAngle);
	//创建单片飞行线，没有停止
	void BulidFragmentLine(osg::Group*,CoordinatesPosition ,CoordinatesPosition );

	//创建弹片飞行线与目标交汇
	void BulidFragmentAimLineYDamage(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion);
	//创建弹片飞行线与目标未交汇
	void BulidFragmentAimLineNoAttack(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion);
	//创建弹片飞行线与目标交汇，但未有毁伤效果
	void BulidFragmentAimLineNoDamage(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion);

	//确定目标区域毁伤等级
	int GetTheDamageLevel(int&);
	//毁伤目标区域颜色
	osg::Vec4f GetTheUnitColor(int&);
	//父节点
	osg::ref_ptr<osg::Group> RootScene; 
	//显示界面指针
	ViewerWidget *_pViewWidget;
	//变量设置
	//系统参数
	Bit_UnitSystem _UnitSystem;
	//目标参数
	TargetAreaParameter _TargetArea;
	//弹体参数
	LGRockParameter _RockObject;
	//颜色容器
	std::vector<osg::Vec4f> _listColor;
	std::multimap<int,osg::Geometry*> _listGeometry;
	//毁伤面积
	double DamageArea;
	double MassiveData;
	double AxisLength;
	std::vector<LineUpDataCallBack*> NodeCallBackVec;
	std::vector<ShockWaveCallBack*> ShockWaveCallBackVec;

private slots:
	void GetChangeLevelColor(int,QColor);
};
//运算的线程
class ThreadRcokArea :public QThread
{
	 Q_OBJECT
public:
	ThreadRcokArea();
	~ThreadRcokArea();
	void SetOperationDisplay(OperationDisplay *p);
	bool GetFunc();
	void stop();
protected:
	void run();
private:
	bool FunB;
	volatile bool stopped;
	OperationDisplay *pDialog;
signals:
	//计算完成
	void EmitFuncOK(bool b);
};
#endif
