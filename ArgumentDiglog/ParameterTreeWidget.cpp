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
	 _headList<<QString::fromLocal8Bit("��������");
	 _headList<<QString::fromLocal8Bit("ֵ");
	 this->setHeaderLabels(_headList);
  

	 //��λ������ʾ
	 QStringList UnitSystem;
	 UnitSystem <<QString::fromLocal8Bit("��λϵͳ");
	 UnitSystemRoot = new QTreeWidgetItem(this, UnitSystem);

	 //Ŀ������
	 QStringList TargetArea;
	 TargetArea << QString::fromLocal8Bit("Ŀ������");
	 TargetAreaRoot = new QTreeWidgetItem(this, TargetArea);

	 //��������
	 QStringList RockBody;
	 RockBody << QString::fromLocal8Bit("��������");
	 RockBodyRoot = new QTreeWidgetItem(this, RockBody);
}
//
void ParameterTree::GetUnitSystemParameter(std::vector<int>& _unitLisy)
{
	QStringList UnitSystemLength;
	switch(_unitLisy.at(0))
	{
	case 1:
		UnitSystemLength << QString::fromLocal8Bit("���ȵ�λ") <<QString::fromLocal8Bit("mm(����)");
		break;
	case 2:
		UnitSystemLength << QString::fromLocal8Bit("���ȵ�λ") <<QString::fromLocal8Bit("cm(����)");
		break;
	case 3:
		UnitSystemLength << QString::fromLocal8Bit("���ȵ�λ") <<QString::fromLocal8Bit("m(��)");
		break;
	case 4:
		UnitSystemLength << QString::fromLocal8Bit("���ȵ�λ") <<QString::fromLocal8Bit("km(ǧ��)");
		break;
	}
	QTreeWidgetItem *leafLength = new QTreeWidgetItem(UnitSystemRoot, UnitSystemLength);
	UnitSystemRoot->addChild(leafLength);
	////////////////////
	QStringList UnitSystemTime;
	switch(_unitLisy.at(1))
	{
	case 1:
		UnitSystemTime << QString::fromLocal8Bit("ʱ�䵥λ") << QString::fromLocal8Bit("us(΢��)");
		break;
	case 2:
		UnitSystemTime << QString::fromLocal8Bit("ʱ�䵥λ") << QString::fromLocal8Bit("ms(����)");
		break;
	case 3:
		UnitSystemTime << QString::fromLocal8Bit("ʱ�䵥λ") << QString::fromLocal8Bit("s(��)");
		break;
	}
	QTreeWidgetItem *leafTime = new QTreeWidgetItem(UnitSystemRoot, UnitSystemTime);
	UnitSystemRoot->addChild(leafTime);
	///////////
	QStringList UnitSystemMass;
	switch(_unitLisy.at(2))
	{
	case 1:
		UnitSystemMass << QString::fromLocal8Bit("������λ") << QString::fromLocal8Bit("g(��)");
		break;
	case 2:
		UnitSystemMass << QString::fromLocal8Bit("������λ") << QString::fromLocal8Bit("kg(ǧ��)");
		break;
	}
	QTreeWidgetItem *leafMass = new QTreeWidgetItem(UnitSystemRoot, UnitSystemMass);
	UnitSystemRoot->addChild(leafMass);
	///////////
	QStringList UnitSystemArc;
	/*switch(_unitLisy.at(2))
	{
	case 1:
	UnitSystemMass << QString::fromLocal8Bit("������λ") << QString::fromLocal8Bit("g(��)");
	break;
	case 2:
	UnitSystemMass << QString::fromLocal8Bit("������λ") << QString::fromLocal8Bit("kg(ǧ��)");
	break;
	}*/
	UnitSystemArc << QString::fromLocal8Bit("�Ƕ���") << QString::fromLocal8Bit("����");
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
	_list1 << QString::fromLocal8Bit("Ŀ������") <<_value.setNum(TargetObject.Aim_Long);
	QTreeWidgetItem *_list1Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list1Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("Ŀ�������") <<_value.setNum(TargetObject.Aim_Wide);
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
	_list1 << QString::fromLocal8Bit("���ľ���") <<_value.setNum(TargetObject.AimCenterPointLon);
	QTreeWidgetItem *_list5Item = new QTreeWidgetItem(TargetAreaRoot, _list1);
	TargetAreaRoot->addChild(_list5Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("����γ��") <<_value.setNum(TargetObject.AimCenterPointLat);
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
	_list1 << QString::fromLocal8Bit("��Ƭ����") <<_value.setNum(RockObject.FragmentNumber);
	QTreeWidgetItem *_list1Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list1Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("��Ƭ����") <<_value.setNum(RockObject.Frag_Mass);
	QTreeWidgetItem *_list2Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list2Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ս������̬��ɢ��") <<_value.setNum(RockObject.Rock_WarheadStaticAngle);
	QTreeWidgetItem *_list3Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list3Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ս������̬��ɢ�Ƿֲ��������뵯��ϵx��н�") <<_value.setNum(RockObject.Rock_WarheadStaticAngleToCenter);
	QTreeWidgetItem *_list4Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list4Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("������ٶ�") <<_value.setNum(RockObject.Rock_RocketVelocity);
	QTreeWidgetItem *_list5Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list5Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("�����") <<_value.setNum(RockObject.Rock_CEP);
	QTreeWidgetItem *_list6Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list6Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("Բ���ο�������") <<_value.setNum(RockObject.ShellMass_Clylinder);
	QTreeWidgetItem *_list7Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list7Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("Բ����װҩ����") <<_value.setNum(RockObject.ChargeMass_Clylinder);
	QTreeWidgetItem *_list8Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list8Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ս������������") <<_value.setNum(RockObject.AllMass_Whole);
	QTreeWidgetItem *_list9Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list9Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("װҩ��������") <<_value.setNum(RockObject.ChargeMass_Whole);
	QTreeWidgetItem *_list10Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list10Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ս����Բ�����ھ�") <<_value.setNum(RockObject.ShellInterDiameter);
	QTreeWidgetItem *_list11Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list11Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ս����Բ�����⾶") <<_value.setNum(RockObject.ShellOuterDiameter);
	QTreeWidgetItem *_list12Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list12Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ս����Բ�������Ѱ뾶") <<_value.setNum(RockObject.ShellBrokenDiameter);
	QTreeWidgetItem *_list13Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list13Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("װҩ�ܶ�") <<_value.setNum(RockObject.Density);
	QTreeWidgetItem *_list14Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list14Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("װҩ����") <<_value.setNum(RockObject.ExplosionVelocity);
	QTreeWidgetItem *_list15Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list15Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("װҩ����") <<_value.setNum(RockObject.ExplosionHeat);
	QTreeWidgetItem *_list16Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list16Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("װҩ��ѹ") <<_value.setNum(RockObject.ExplosinPressure);
	QTreeWidgetItem *_list17Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list17Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("��״ϵ��") <<_value.setNum(RockObject.SC);
	QTreeWidgetItem *_list18Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list18Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("���θ߶�") <<_value.setNum(RockObject.ASL);
	QTreeWidgetItem *_list19Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list19Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("��������ϵ��") <<_value.setNum(RockObject.RC);
	QTreeWidgetItem *_list20Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list20Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("�����γ��") <<_value.setNum(RockObject.FireLat);
	QTreeWidgetItem *_list21Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list21Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("����㾭��") <<_value.setNum(RockObject.FireLon);
	QTreeWidgetItem *_list22Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list22Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("��׼��γ��") <<_value.setNum(RockObject.AimLat);
	QTreeWidgetItem *_list23Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list23Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("��׼�㾭��") <<_value.setNum(RockObject.AimLon);
	QTreeWidgetItem *_list24Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list24Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ը������") <<_value.setNum(RockObject.BHE);
	QTreeWidgetItem *_list25Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list25Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("ը�߱�׼��") <<_value.setNum(RockObject.BHD);
	QTreeWidgetItem *_list26Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list26Item);

	_list1.clear();
	_value.clear();
	_list1 << QString::fromLocal8Bit("�����о�") <<_value.setNum(RockObject.Frag_FragmentDamageCriterion);
	QTreeWidgetItem *_list27Item = new QTreeWidgetItem(RockBodyRoot, _list1);
	RockBodyRoot->addChild(_list27Item);
}