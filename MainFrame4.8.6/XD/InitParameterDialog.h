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

//���˵ȼ�
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
//��Ԫ��ṹ��
struct GridUnit
{
	//�ָԪID���
	int UnitID;
	//��Ƭ����
	int FragmentsAmount;
	//���˵ȼ�
	int DamageLevel;
	//��������˵ȼ�
	int ShackDamageLevel;
	//��Ԫ��
	Element_Surface_Quad UnitNode;
	//��Ƭ���
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
///�ߵĽṹ��
struct FragMentLine
{
	//��Ƭ��ʼ��
	CoordinatesPosition _PosBegin;
	//��Ƭĩ��
	CoordinatesPosition _PosEnd;
	//��������
	CoordinatesPosition _PosV;
	//��Ƭ�Ƿ��Ŀ�����򽻻�
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
	//���캯��
	OperationDisplay();
	//��ȡ������ʾ
	void GetViewerWidget();
	//��ȡ��λϵͳ����
	void GetUnitSeting(Bit_UnitSystem&);
	//��ȡ�����������
	void GetRockSeting(LGRockParameter&);
	//��ȡĿ�������������
	void GetAreaZoneSeting(TargetAreaParameter&);
	void GetViewerWidget(ViewerWidget* pv);
	double GetDamageAreaData() const;
	double GetMassive() const;
	osg::Group* GetTheRootGroup();
	void SetContrlType(int Itype);
private:
	//�������
	void  InitPlotShrapnelLine();
	//��������ϵ
	void BulidCoordinate(osg::Group *Root,CoordinatesPosition centerPoint,osg::Vec3 RotateAngle,std::string Ctype);
	//����Ŀ������
	void BulidAimZoonGrid(osg::Group *root,Bit_AimDataStructure *,std::map<int,GridUnit>&);
	//��������
	void BulidProjectile(osg::Group *root,WarheadPowerAnalysisData &warHead,CoordinatesPosition Frag_HitPosition,osg::Vec3 RotateAngle);
	//������Ƭ�����ߣ�û��ֹͣ
	void BulidFragmentLine(osg::Group*,CoordinatesPosition ,CoordinatesPosition );

	//������Ƭ��������Ŀ�꽻��
	void BulidFragmentAimLineYDamage(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion);
	//������Ƭ��������Ŀ��δ����
	void BulidFragmentAimLineNoAttack(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion);
	//������Ƭ��������Ŀ�꽻�㣬��δ�л���Ч��
	void BulidFragmentAimLineNoDamage(osg::Group *root,std::vector<FragMentLine> AimFragmeList,CoordinatesPosition HitPostion);

	//ȷ��Ŀ��������˵ȼ�
	int GetTheDamageLevel(int&);
	//����Ŀ��������ɫ
	osg::Vec4f GetTheUnitColor(int&);
	//���ڵ�
	osg::ref_ptr<osg::Group> RootScene; 
	//��ʾ����ָ��
	ViewerWidget *_pViewWidget;
	//��������
	//ϵͳ����
	Bit_UnitSystem _UnitSystem;
	//Ŀ�����
	TargetAreaParameter _TargetArea;
	//�������
	LGRockParameter _RockObject;
	//��ɫ����
	std::vector<osg::Vec4f> _listColor;
	std::multimap<int,osg::Geometry*> _listGeometry;
	//�������
	double DamageArea;
	double MassiveData;
	double AxisLength;
	std::vector<LineUpDataCallBack*> NodeCallBackVec;
	std::vector<ShockWaveCallBack*> ShockWaveCallBackVec;

private slots:
	void GetChangeLevelColor(int,QColor);
};
//������߳�
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
	//�������
	void EmitFuncOK(bool b);
};
#endif
