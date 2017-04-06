#include "ParameterTreeWidget.h"
//
ParameterTree::ParameterTree(QTreeWidget *parent) : QTreeWidget(parent)
{
	InitWidget();
}
//
ParameterTree::~ParameterTree()
{

}
//
void ParameterTree::InitWidget()
{
	 this->setColumnCount(2);
	 QStringList _headList;
	 _headList<<QString::fromLocal8Bit("属性名称");
	 _headList<<QString::fromLocal8Bit("值");
	 this->setHeaderLabels(_headList);
  

	 //单位设置显示
	 QStringList UnitSystem;
	 UnitSystem <<QString::fromLocal8Bit("单位系统");
	 UnitSystemRoot = new QTreeWidgetItem(this, UnitSystem);

	 //目标区域
	 QStringList TargetArea;
	 TargetArea << QString::fromLocal8Bit("目标区域");
	 TargetAreaRoot = new QTreeWidgetItem(this, TargetArea);

	 //弹体属性
	 QStringList RockBody;
	 RockBody << QString::fromLocal8Bit("弹体属性");
	 RockBodyRoot = new QTreeWidgetItem(this, RockBody);
}
//
void ParameterTree::GetUnitSystemParameter(std::vector<int>& _unitLisy)
{
	QStringList UnitSystemLength;
	switch(_unitLisy.at(0))
	{
	case 1:
		UnitSystemLength << QString::fromLocal8Bit("长度单位") <<QString::fromLocal8Bit("mm(毫米)");
		break;
	case 2:
		UnitSystemLength << QString::fromLocal8Bit("长度单位") <<QString::fromLocal8Bit("cm(厘米)");
		break;
	case 3:
		UnitSystemLength << QString::fromLocal8Bit("长度单位") <<QString::fromLocal8Bit("m(米)");
		break;
	case 4:
		UnitSystemLength << QString::fromLocal8Bit("长度单位") <<QString::fromLocal8Bit("km(千米)");
		break;
	}
	QTreeWidgetItem *leafLength = new QTreeWidgetItem(UnitSystemRoot, UnitSystemLength);
	UnitSystemRoot->addChild(leafLength);
	////////////////////
	QStringList UnitSystemTime;
	switch(_unitLisy.at(1))
	{
	case 1:
		UnitSystemTime << QString::fromLocal8Bit("时间单位") << QString::fromLocal8Bit("us(微秒)");
		break;
	case 2:
		UnitSystemTime << QString::fromLocal8Bit("时间单位") << QString::fromLocal8Bit("ms(毫秒)");
		break;
	case 3:
		UnitSystemTime << QString::fromLocal8Bit("时间单位") << QString::fromLocal8Bit("s(秒)");
		break;
	}
	QTreeWidgetItem *leafTime = new QTreeWidgetItem(UnitSystemRoot, UnitSystemTime);
	UnitSystemRoot->addChild(leafTime);
	///////////
	QStringList UnitSystemMass;
	switch(_unitLisy.at(2))
	{
	case 1:
		UnitSystemMass << QString::fromLocal8Bit("质量单位") << QString::fromLocal8Bit("g(克)");
		break;
	case 2:
		UnitSystemMass << QString::fromLocal8Bit("质量单位") << QString::fromLocal8Bit("kg(千克)");
		break;
	}
	QTreeWidgetItem *leafMass = new QTreeWidgetItem(UnitSystemRoot, UnitSystemMass);
	UnitSystemRoot->addChild(leafMass);
	///////////
	QStringList UnitSystemArc;
	/*switch(_unitLisy.at(2))
	{
	case 1:
	UnitSystemMass << QString::fromLocal8Bit("质量单位") << QString::fromLocal8Bit("g(克)");
	break;
	case 2:
	UnitSystemMass << QString::fromLocal8Bit("质量单位") << QString::fromLocal8Bit("kg(千克)");
	break;
	}*/
	UnitSystemArc << QString::fromLocal8Bit("角度制") << QString::fromLocal8Bit("弧度");
	QTreeWidgetItem *leafArc = new QTreeWidgetItem(UnitSystemRoot, UnitSystemArc);
	UnitSystemRoot->addChild(leafArc);
}
//
void ParameterTree::GetTargetAreaParameter(TargetAreaParameter& TargetObject)
{

	int ItemCount = TargetAreaRoot->childCount();
	for (int i = 0; i < ItemCount;++i)
	{
		QTreeWidgetItem* item = TargetAreaRoot->child(0);
		TargetAreaRoot->removeChild(item);
	}
	QStringList _list1;
	QString _value;
	_list1 << QString::fromLocal8Bit("目标区域长") <<_value.setNum(TargetObject.Aim_Long);
	QTreeWidgetItem *_list1Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list1Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("目标区域宽") <<_value.setNum(TargetObject.Aim_Wide);
	QTreeWidgetItem *_list2Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list2Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("N_02") <<_value.setNum(TargetObject.Length_N_02);
	QTreeWidgetItem *_list3Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list3Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("N_13") <<_value.setNum(TargetObject.Length_N_13);
	QTreeWidgetItem *_list4Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list4Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("中心经度") <<_value.setNum(TargetObject.AimCenterPointLon);
	QTreeWidgetItem *_list5Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list5Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("中心纬度") <<_value.setNum(TargetObject.AimCenterPointLat);
	QTreeWidgetItem *_list6Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list6Item);
}
//
void ParameterTree::GetRockObjcetParameter(LGRockParameter &RockObject)
{
	int ItemCount = RockBodyRoot->childCount();
	for (int i = 0; i < ItemCount;++i)
	{
		QTreeWidgetItem* item = RockBodyRoot->child(0);
		RockBodyRoot->removeChild(item);
	}

	QStringList _list1;
	QString _value;
	_list1 << QString::fromLocal8Bit("破片数量") <<_value.setNum(RockObject.FragmentNumber);
	QTreeWidgetItem *_list1Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list1Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("破片质量") <<_value.setNum(RockObject.Frag_Mass);
	QTreeWidgetItem *_list2Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list2Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("战斗部静态飞散角") <<_value.setNum(RockObject.Rock_WarheadStaticAngle);
	QTreeWidgetItem *_list3Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list3Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("战斗部静态飞散角分布中心线与弹体系x轴夹角") <<_value.setNum(RockObject.Rock_WarheadStaticAngleToCenter);
	QTreeWidgetItem *_list4Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list4Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("火箭弹速度") <<_value.setNum(RockObject.Rock_RocketVelocity);
	QTreeWidgetItem *_list5Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list5Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("火箭弹") <<_value.setNum(RockObject.Rock_CEP);
	QTreeWidgetItem *_list6Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list6Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("圆柱段壳体质量") <<_value.setNum(RockObject.ShellMass_Clylinder);
	QTreeWidgetItem *_list7Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list7Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("圆柱段装药质量") <<_value.setNum(RockObject.ChargeMass_Clylinder);
	QTreeWidgetItem *_list8Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list8Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("战斗部整体质量") <<_value.setNum(RockObject.AllMass_Whole);
	QTreeWidgetItem *_list9Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list9Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("装药整体质量") <<_value.setNum(RockObject.ChargeMass_Whole);
	QTreeWidgetItem *_list10Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list10Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("战斗部圆柱段内径") <<_value.setNum(RockObject.ShellInterDiameter);
	QTreeWidgetItem *_list11Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list11Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("战斗部圆柱段外径") <<_value.setNum(RockObject.ShellOuterDiameter);
	QTreeWidgetItem *_list12Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list12Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("战斗部圆柱段破裂半径") <<_value.setNum(RockObject.ShellBrokenDiameter);
	QTreeWidgetItem *_list13Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list13Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("装药密度") <<_value.setNum(RockObject.Density);
	QTreeWidgetItem *_list14Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list14Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("装药爆速") <<_value.setNum(RockObject.ExplosionVelocity);
	QTreeWidgetItem *_list15Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list15Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("装药爆热") <<_value.setNum(RockObject.ExplosionHeat);
	QTreeWidgetItem *_list16Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list16Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("装药爆压") <<_value.setNum(RockObject.ExplosinPressure);
	QTreeWidgetItem *_list17Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list17Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("形状系数") <<_value.setNum(RockObject.SC);
	QTreeWidgetItem *_list18Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list18Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("海拔高度") <<_value.setNum(RockObject.ASL);
	QTreeWidgetItem *_list19Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list19Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("气动阻力系数") <<_value.setNum(RockObject.RC);
	QTreeWidgetItem *_list20Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list20Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("发射点纬度") <<_value.setNum(RockObject.FireLat);
	QTreeWidgetItem *_list21Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list21Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("发射点经度") <<_value.setNum(RockObject.FireLon);
	QTreeWidgetItem *_list22Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list22Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("瞄准点纬度") <<_value.setNum(RockObject.AimLat);
	QTreeWidgetItem *_list23Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list23Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("瞄准点经度") <<_value.setNum(RockObject.AimLon);
	QTreeWidgetItem *_list24Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list24Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("炸高期望") <<_value.setNum(RockObject.BHE);
	QTreeWidgetItem *_list25Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list25Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("炸高标准差") <<_value.setNum(RockObject.BHD);
	QTreeWidgetItem *_list26Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list26Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("毁伤判据") <<_value.setNum(RockObject.Frag_FragmentDamageCriterion);
	QTreeWidgetItem *_list27Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list27Item);
}