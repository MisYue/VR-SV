/*
    弹体等其它参数设定
	2016-07-01
	ZXD
*/
#ifndef _ROCKARGUMENTDIALOG_H
#define _ROCKARGUMENTDIALOG_H
#include "Lib.h"
#include<QtGui/QLineEdit>
//LG_Struct
struct LGRockParameter
{
	//1
	int    FragmentNumber;                      //破片数量
	double Frag_Mass;                       //破片质量
	
	//2
	double Rock_WarheadStaticAngle;        //火箭弹战斗部静态飞散角
	double Rock_WarheadStaticAngleToCenter;//战斗部静态飞散角分布中心线与弹体系x轴夹角
	double Rock_RocketVelocity;            //火箭弹速度
	double Rock_CEP;                       //火箭弹CEP

	//3
	double ShellInterDiameter;              //圆柱内径
	double ShellOuterDiameter;              //圆柱外径
	double ShellBrokenDiameter;             //圆柱破径
	double ShellMass_Clylinder;             //圆柱段壳体质量
	double ChargeMass_Clylinder;            //圆柱段装药质量
	double AllMass_Whole;                   //战斗部整体质量
	double ChargeMass_Whole;                //装药整体质量
	double WarheadLength_Whole;             //弹头全部长度
	double WarheadLength_Clylinder;         //弹头圆柱长度

	//4
	double Density;                         //装药密度
	double ExplosionVelocity;               //装药爆速
	double ExplosionHeat;                   //装药暴热
	double ExplosinPressure;                //装药爆压

	//5
	double Frag_SDA;                        //破片静态飞散角
	double Frag_dis;                        //破片飞散距离
	double Frag_ResidualVelocity_Initialization;//破片半径速度
	double SC;                                  //球形破片
	double ASL;                                 //海拔高度
	double RC;                                  //气动阻力系数

	//6
	double FireLat;                         //发射点纬度
    double FireLon;                         //发射点经度
	double AimLat;                          //瞄准点经度
	double AimLon;                          //瞄准点纬度
	double BHE;                             //炸高期望
	double BHD;                             //炸高标准差
	
	//7
	double Frag_FragmentDamageCriterion;        //毁伤判据
	double ShockWavePressure;
	//8
	int    InterpolationNumber;                 //插值表数据个数
	std::vector<double>  FallingAngle;
	std::vector<double>  FireDistance;
	LGRockParameter()
	{
		//1
		FragmentNumber = 1;                      //破片数量
		Frag_Mass = 0.001;                       //破片质量

		//2
		Rock_WarheadStaticAngle = 0.0;        //火箭弹战斗部静态飞散角
		Rock_WarheadStaticAngleToCenter= 0.0;//战斗部静态飞散角分布中心线与弹体系x轴夹角
		Rock_RocketVelocity = 0.0;            //火箭弹速度
		Rock_CEP = 0.0;                       //火箭弹CEP

		//3
		ShellInterDiameter = 0.0;              //圆柱内径
		ShellOuterDiameter = 0.0;              //圆柱外径
		ShellBrokenDiameter = 0.0;             //圆柱破径
		ShellMass_Clylinder = 0.0;             //圆柱段壳体质量
		ChargeMass_Clylinder = 0.0;            //圆柱段装药质量
		AllMass_Whole = 0.0;                   //战斗部整体质量
		ChargeMass_Whole = 0.0;                //装药整体质量
		WarheadLength_Whole = 0.0;             //弹头长度
		WarheadLength_Clylinder = 0.0;         //弹头圆柱长度
		//装药
		Density = 0.0;                         //装药密度
		ExplosionVelocity = 0.0;               //装药爆速
		ExplosionHeat = 0.0;                   //装药暴热
		ExplosinPressure = 0.0;                //装药爆压
		//
		Frag_SDA = 0.0;                        //破片静态飞散角
		Frag_dis = 0.0;                        //破片飞散距离
		Frag_ResidualVelocity_Initialization = 0.0;//破片半径速度
		SC = 0.0;                                  //球形破片
		ASL = 0.0;                                 //海拔高度
		RC = 0.0;                                  //气动阻力系数

		//6
		FireLat = 0.0;                         //发射点纬度
		FireLon = 0.0;                         //发射点经度
		AimLat = 0.0;
		AimLon = 0.0;
		BHE = 0.0;                             //炸高期望
		BHD = 0.0;                             //炸高标准差

		//7
		Frag_FragmentDamageCriterion = 0.0;        //毁伤判据
		ShockWavePressure = 0.0;
		//8
		InterpolationNumber = 0;                 //插值表数据个数
	}
	LGRockParameter& operator=(const LGRockParameter &sour)
	{
		if (this != &sour)
		{
			//1
			FragmentNumber = sour.FragmentNumber;                      //破片数量
			Frag_Mass = sour.Frag_Mass;                       //破片质量

			//2
			Rock_WarheadStaticAngle = sour.Rock_WarheadStaticAngle;        //火箭弹战斗部静态飞散角
			Rock_WarheadStaticAngleToCenter= sour.Rock_WarheadStaticAngleToCenter;//战斗部静态飞散角分布中心线与弹体系x轴夹角
			Rock_RocketVelocity = sour.Rock_RocketVelocity;            //火箭弹速度
			Rock_CEP = sour.Rock_CEP;                       //火箭弹CEP

			//3
			ShellInterDiameter = sour.ShellInterDiameter;              //圆柱内径
			ShellOuterDiameter = sour.ShellOuterDiameter;              //圆柱外径
			ShellBrokenDiameter = sour.ShellBrokenDiameter;             //圆柱破径
			ShellMass_Clylinder = sour.ShellMass_Clylinder;             //圆柱段壳体质量
			ChargeMass_Clylinder = sour.ChargeMass_Clylinder;            //圆柱段装药质量
			AllMass_Whole = sour.AllMass_Whole;                   //战斗部整体质量
			ChargeMass_Whole = sour.ChargeMass_Whole;                //装药整体质量
			WarheadLength_Whole = sour.WarheadLength_Whole;             //弹头整体长度
			WarheadLength_Clylinder = sour.WarheadLength_Clylinder;         //弹头圆柱长度
			Density = sour.Density;                         //装药密度
			ExplosionVelocity = sour.ExplosionVelocity;               //装药爆速
			ExplosionHeat = sour.ExplosionHeat;                   //装药暴热
			ExplosinPressure = sour.ExplosinPressure;                //装药爆压

			Frag_SDA = sour.Frag_SDA;                        //破片静态飞散角
			Frag_dis = sour.Frag_dis;                        //破片飞散距离
			Frag_ResidualVelocity_Initialization = sour.Frag_ResidualVelocity_Initialization;//破片半径速度
			SC = sour.SC;                                  //球形破片
			ASL = sour.ASL;                                 //海拔高度
			RC = sour.RC;                                  //气动阻力系数

			//6
			FireLat = sour.FireLat;                         //发射点纬度
			FireLon = sour.FireLon;                         //发射点经度
			AimLat = sour.AimLat;
			AimLon = sour.AimLon;
			BHE = sour.BHE;                             //炸高期望
			BHD = sour.BHD;                             //炸高标准差

			//7
			Frag_FragmentDamageCriterion = sour.Frag_FragmentDamageCriterion;        //毁伤判据
			//8
			InterpolationNumber = sour.InterpolationNumber;                 //插值表数据个数
			FireDistance = sour.FireDistance;
			FallingAngle = sour.FallingAngle;
			ShockWavePressure = sour.ShockWavePressure;
	        return *this;
		}
		return *this;
	}
};
//弹体参数
class ArgumentDialog : public QDialog
{
	Q_OBJECT
public:
	ArgumentDialog(const QStringList&,QDialog *parent = 0);
	~ArgumentDialog();
	LGRockParameter& ReadRockParameter();
	bool IsOKOrCancancle() const;
	void GetAimLatLon(double,double);
	void GetConfigFileSettings(const LGRockParameter Object);
private:
	void InitDialog();
	void InitFragmentArgument();
	void InitOrtheArgument();
private:
	QGridLayout *_layout;
	QGroupBox *_gBox_3;
	QGroupBox *_gBox_4;

	//////////////////////////////////////////////////////////////////////////
	QDoubleSpinBox *_FragmentMass_spin;
	QSpinBox *_FragmentNum_spin;
	QDoubleSpinBox *_scatteringAngle_SpinBox;
	QDoubleSpinBox *_centerline_SpinBox;
	QDoubleSpinBox *_RocketVelocity_SpinBox;
	QDoubleSpinBox *_RocketCEP_SpinBox;
	QDoubleSpinBox *_ShellMass_Clylinder_SpinBox;
	QDoubleSpinBox *_ChargeMass_Clylinder_SpinBox;
	QDoubleSpinBox *_AllMass_Wholer_SpinBox;
	QDoubleSpinBox *_AllAmmoMass_Wholer_SpinBox;
	QDoubleSpinBox *_ShellInterDiameter_SpinBox;
	QDoubleSpinBox *_ShellOuterDiameter_SpinBox;
	QDoubleSpinBox *_ShellBrokenDiameter_SpinBox;
	QDoubleSpinBox *_WarheadLength_Whole_SpinBox;
	QDoubleSpinBox *_WarheadLength_Clylinder_SpinBox;
	QDoubleSpinBox *_Density_SpinBox;
	QDoubleSpinBox *_ExplosionVelocity_SpinBox;
	QDoubleSpinBox *_ShapeCoefficient_SpinBox;
	QDoubleSpinBox *_AboveSeaLevel_SpinBox;
	QDoubleSpinBox *_ResistanceCoefficient_SpinBox;
	QDoubleSpinBox *_FragmentDamageCriterion_SpinBox;
	QDoubleSpinBox *_FireLat_SpinBox;
	QDoubleSpinBox *_FireLon_SpinBox;
	QDoubleSpinBox *_BHE_SpinBox;
	QDoubleSpinBox *_BHDt_SpinBox;
	QDoubleSpinBox *_DropLat_SpinBox;
    QDoubleSpinBox *_DropLon_SpinBox;
	QDoubleSpinBox *_shockwavepressure_SpinBox;
	//弹体属性组件
	LGRockParameter _ObjectLGRock;
	bool SetTureFalse;
	QStringList _unitList;
	QLineEdit *_ExplosionHeat_Line;
	QLineEdit *_ExplosinPressure_Line;
private slots:
	 void GetSpinBoxValue(int);
	 void GetDoubleSpinBoxValue(double);
	 void SetingOKOrCancle();
	 void PbFileChoise();
	 void ConfigurationParameter();
signals:
	 void EmitChoiseFile();
};
#endif // ARGUMENTDIALOG_H
