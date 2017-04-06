#include "XMLOperation.h"
#include<QtGui/QFileDialog>
#include <QtGui/QDialog>
#include <QtGui/QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include<BITFuzeDataBase/Bit_AirExplosion.h>
#include <BITProjectileDataBase/Bit_TerminalData.h>
#include <BITTargetModelSupport/Bit_GroundArea.h>
#include <MaterialDataBase/ChargeData.h>
#include <MaterialDataBase/Bit_Hardness.h>
#include <MaterialDataBase/Bit_MetalData.h>
#include <WarheadDataBase/Bit_FragmentBaseData.h>
#include <WarheadDataBase/Bit_SFragVPData_P.h>
#include <WarheadDataBase/WarheadPowerAnalysisData.h>
#include <Bit_RocketAnalyse.h>
//
XMLOperation::XMLOperation(const QString FileName) : filename(FileName)
{
	_plog = new QDialog;
	_playout = new QVBoxLayout;
	_pRockTab = new QTableWidget;
	_pAreaTab = new QTableWidget;

	_pAreaTab->setSelectionBehavior( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	_pAreaTab->setSelectionMode( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

	_pRockTab->setSelectionBehavior( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
	_pRockTab->setSelectionMode( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

	//设定火箭表格宽
	_pRockTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_pRockTab->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	//设定目标区域表头宽
	_pAreaTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_pAreaTab->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

	area_row = 0;
	rock_row = 0;

	_plog->setLayout(_playout);
};
//
XMLOperation::~XMLOperation()
{

};
//
void XMLOperation::SetFileName(QString name)
{
	filename.clear();
	filename = name;
};
bool XMLOperation::SaveXMLFile(const TargetAreaParameter &_pT,const LGRockParameter &_pLG)
{

	//保存文件
	QString file_Name = QFileDialog::getSaveFileName(this,QString::fromLocal8Bit("保存文件"), "D:/", QString::fromLocal8Bit("XML文件(*.xml)"));

	QFile file_(file_Name);
	int count(0);
	QDomElement root; 
	QString str;
	if (!file_.open(QIODevice::ReadOnly))
	{
		//return false;
	}
	QDomDocument doc;
	if (!doc.setContent(&file_))
	{
		file_.close();
		root = doc.createElement(QString("实验数据配置"));
	}
	else
	{
		file_.close();
		root = doc.documentElement();
		QDomElement book_ = doc.createElement(QString("图书"));
		// 我们获得了最后一个孩子结点的编号，然后加1，便是新的编号
		QString num = root.lastChild().toElement().attribute(QString("编号"));
		count = num.toInt();
	}


	// 添加第一个图书元素及其子元素
	QDomElement book = doc.createElement(QString("配置"));
	QDomAttr id = doc.createAttribute(QString("编号"));

	QDomElement  UnitSystem = doc.createElement(QString("系统单位"));
	QDomAttr Unit_lenght = doc.createAttribute(QString("长度单位"));
	QDomAttr Unit_time = doc.createAttribute(QString("时间单位"));
	QDomAttr Unit_mass = doc.createAttribute(QString("重量单位"));
	QDomElement  TargetZone = doc.createElement(QString("目标区域"));
	QDomAttr Area_length = doc.createAttribute(QString("目标区域长度"));
	QDomAttr Area_widgth = doc.createAttribute(QString("目标区域宽度"));
	QDomAttr Area_lat = doc.createAttribute(QString("中心纬度"));
	QDomAttr Area_lon = doc.createAttribute(QString("中心经度"));
	QDomAttr Area_N_02 = doc.createAttribute(QString("长划分"));
	QDomAttr Area_N_13 = doc.createAttribute(QString("宽划分"));
	QDomElement RockParameter = doc.createElement(QString("弹体属性"));
	QDomAttr FragmentNumber = doc.createAttribute(QString("破片数量"));
	QDomAttr Frag_Mass = doc.createAttribute(QString("破片质量"));
	QDomAttr Rock_WarheadStaticAngle = doc.createAttribute(QString("火箭弹战斗部静态飞散角"));
	QDomAttr Rock_WarheadStaticAngleToCenter = doc.createAttribute(QString("战斗部静态飞散角分布中心线与弹体系X轴夹角"));
	QDomAttr Rock_RocketVelocity = doc.createAttribute(QString("火箭弹速度"));
	QDomAttr Rock_CEP = doc.createAttribute(QString("火箭弹CEP"));
	QDomAttr ShellInterDiameter = doc.createAttribute(QString("圆柱内径"));
	QDomAttr ShellOuterDiameter = doc.createAttribute(QString("圆柱外径"));
	QDomAttr ShellBrokenDiameter = doc.createAttribute(QString("圆柱破径"));
	QDomAttr WarheadLength_Whole = doc.createAttribute(QString("弹头全部长度"));
	QDomAttr WarheadLength_Clylinder = doc.createAttribute(QString("弹头圆柱长度"));
	QDomAttr ShellMass_Clylinder = doc.createAttribute(QString("圆柱段壳体质量"));
	QDomAttr ChargeMass_Clylinder = doc.createAttribute(QString("圆柱段装药质量"));
	QDomAttr ChargeMass_Whole = doc.createAttribute(QString("装药整体质量"));
	QDomAttr AllMass_Whole = doc.createAttribute(QString("战斗部整体质量"));
	QDomAttr Density = doc.createAttribute(QString("装药密度"));
	QDomAttr ExplosionVelocity = doc.createAttribute(QString("装药爆速"));
	QDomAttr ExplosionHeat = doc.createAttribute(QString("装药暴热"));
	QDomAttr ExplosinPressure = doc.createAttribute(QString("装药爆压"));
	QDomAttr SC = doc.createAttribute(QString("球形破片"));
	QDomAttr ASL = doc.createAttribute(QString("海拔高度"));
	QDomAttr RC = doc.createAttribute(QString("气动阻力系数"));
	QDomAttr FireLat = doc.createAttribute(QString("发射点纬度"));
	QDomAttr FireLon = doc.createAttribute(QString("发射点经度"));
	QDomAttr BHE = doc.createAttribute(QString("炸高期望"));
	QDomAttr BHD = doc.createAttribute(QString("炸高标准差"));
	QDomAttr Frag_FragmentDamageCriterion = doc.createAttribute(QString("毁伤判据"));
	QDomAttr InterpolationNumber = doc.createAttribute(QString("插值表数据个数"));
	QDomAttr FallingAngle = doc.createAttribute(QString("落角插值"));
	QDomAttr FireDistance = doc.createAttribute(QString("落距插值"));
	QDomText text;

	if (count == 0)
	{
		// 添加处理指令即XML说明
		QDomProcessingInstruction instruction;
		QString ModeTarget = "xml";
		QString ModeData = "version=\"1.0\" encoding=\"UTF-8\"";

		instruction = doc.createProcessingInstruction(ModeTarget,ModeData);
		doc.appendChild(instruction);

		// 添加根元素
		doc.appendChild(root);
		str.setNum(count+1);
		id.setValue(str);
		str.clear();
		book.setAttributeNode(id);


		switch(_length)
		{
		case 1:
			str = QString::fromLocal8Bit("mm(毫米)");
			break;
		case 2:
			str =QString::fromLocal8Bit("cm(厘米)");
			break;
		case 3:
			str =QString::fromLocal8Bit("m(米)");
			break;
		case 4:
			str =QString::fromLocal8Bit("km(千米)");
			break;
		}
		Unit_lenght.setValue(str);
		switch(_time)
		{
		case 1:
			str = QString::fromLocal8Bit("us(微秒)");
			break;
		case 2:
			str = QString::fromLocal8Bit("ms(毫秒)");
			break;
		case 3:
			str = QString::fromLocal8Bit("s(秒)");
			break;
		}
		Unit_time.setValue(str);
		QStringList UnitSystemMass;
		switch(_mass)
		{
		case 1:
			str = QString::fromLocal8Bit("g(克)");
			break;
		case 2:
			str = QString::fromLocal8Bit("kg(千克)");
			break;
		}
		Unit_mass.setValue(str);
		UnitSystem.setAttributeNode(Unit_lenght);
		UnitSystem.setAttributeNode(Unit_time);
		UnitSystem.setAttributeNode(Unit_mass);

		Area_length.setValue(str.setNum(_pT.Aim_Long));
		Area_widgth.setValue(str.setNum(_pT.Aim_Wide));
		Area_lat.setValue(str.setNum(_pT.AimCenterPointLat));
		Area_lon.setValue(str.setNum(_pT.AimCenterPointLon));
		Area_N_02.setValue(str.setNum(_pT.Length_N_02));
		Area_N_13.setValue(str.setNum(_pT.Length_N_13));

		TargetZone.setAttributeNode(Area_length);
		TargetZone.setAttributeNode(Area_widgth);
		TargetZone.setAttributeNode(Area_lat);
		TargetZone.setAttributeNode(Area_lon);
		TargetZone.setAttributeNode(Area_N_02);
		TargetZone.setAttributeNode(Area_N_13);
		////
		////弹体属性表
		/*text = doc.createTextNode(QString("shiming"));
		RockParameter.appendChild(text);*/

		FragmentNumber.setValue(str.setNum(_pLG.FragmentNumber));
		Frag_Mass.setValue(str.setNum(_pLG.Frag_Mass));
		Rock_WarheadStaticAngle.setValue(str.setNum(_pLG.Rock_WarheadStaticAngle));
		Rock_WarheadStaticAngleToCenter.setValue(str.setNum(_pLG.Rock_WarheadStaticAngleToCenter));
		Rock_RocketVelocity.setValue(str.setNum(_pLG.Rock_RocketVelocity));
		Rock_CEP.setValue(str.setNum(_pLG.Rock_CEP));
		ShellInterDiameter.setValue(str.setNum(_pLG.ShellInterDiameter));
		ShellOuterDiameter.setValue(str.setNum(_pLG.ShellOuterDiameter));
		ShellBrokenDiameter.setValue(str.setNum(_pLG.ShellBrokenDiameter));
		WarheadLength_Whole.setValue(str.setNum(_pLG.WarheadLength_Whole));
		WarheadLength_Clylinder.setValue(str.setNum(_pLG.WarheadLength_Clylinder));
		ShellMass_Clylinder.setValue(str.setNum(_pLG.ShellMass_Clylinder));
		ChargeMass_Clylinder.setValue(str.setNum(_pLG.ChargeMass_Clylinder));
		AllMass_Whole.setValue(str.setNum(_pLG.AllMass_Whole));
		ChargeMass_Whole.setValue(str.setNum(_pLG.ChargeMass_Whole));
		Density.setValue(str.setNum(_pLG.Density));
		ExplosionVelocity.setValue(str.setNum(_pLG.ExplosionVelocity));
		ExplosionHeat.setValue(str.setNum(_pLG.ExplosionHeat));
		ExplosinPressure.setValue(str.setNum(_pLG.ExplosinPressure));
		SC.setValue(str.setNum(_pLG.SC));
		ASL.setValue(str.setNum(_pLG.ASL));
		RC.setValue(str.setNum(_pLG.RC));
		FireLat.setValue(str.setNum(_pLG.FireLat));
		FireLon.setValue(str.setNum(_pLG.FireLon));
		BHE.setValue(str.setNum(_pLG.BHE));
		BHD.setValue(str.setNum(_pLG.BHD));
		Frag_FragmentDamageCriterion.setValue(str.setNum(_pLG.Frag_FragmentDamageCriterion));
		InterpolationNumber.setValue(str.setNum(_pLG.InterpolationNumber));
		QString strList;
		for (int i = 0; i < _pLG.FallingAngle.size();++i)
		{
			strList = strList + str.setNum(_pLG.FallingAngle.at(i))+",";
		}
		FallingAngle.setValue(strList);

		strList.clear();
		for (int i = 0; i < _pLG.FireDistance.size();++i)
		{
			strList = strList + str.setNum(_pLG.FireDistance.at(i))+",";
		}
		FireDistance.setValue(strList);

		RockParameter.setAttributeNode(FragmentNumber);
		RockParameter.setAttributeNode(Frag_Mass);
		RockParameter.setAttributeNode(Rock_WarheadStaticAngle);
		RockParameter.setAttributeNode(Rock_WarheadStaticAngleToCenter);
		RockParameter.setAttributeNode(Rock_RocketVelocity);
		RockParameter.setAttributeNode(Rock_CEP);
		RockParameter.setAttributeNode(ShellInterDiameter);
		RockParameter.setAttributeNode(ShellOuterDiameter);
		RockParameter.setAttributeNode(ShellBrokenDiameter);
		RockParameter.setAttributeNode(WarheadLength_Whole);
		RockParameter.setAttributeNode(WarheadLength_Clylinder);
		RockParameter.setAttributeNode(ShellMass_Clylinder);
		RockParameter.setAttributeNode(ChargeMass_Clylinder);
		RockParameter.setAttributeNode(AllMass_Whole);
		RockParameter.setAttributeNode(ChargeMass_Whole);
		RockParameter.setAttributeNode(Density);
		RockParameter.setAttributeNode(ExplosionVelocity);
		RockParameter.setAttributeNode(ExplosionHeat);
		RockParameter.setAttributeNode(ExplosinPressure);
		RockParameter.setAttributeNode(SC);
		RockParameter.setAttributeNode(ASL);
		RockParameter.setAttributeNode(RC);
		RockParameter.setAttributeNode(FireLat);
		RockParameter.setAttributeNode(FireLon);
		RockParameter.setAttributeNode(BHE);
		RockParameter.setAttributeNode(BHD);
		RockParameter.setAttributeNode(Frag_FragmentDamageCriterion);
		RockParameter.setAttributeNode(InterpolationNumber);
		RockParameter.setAttributeNode(FallingAngle);
		RockParameter.setAttributeNode(FireDistance);
		////
		book.appendChild(UnitSystem);
		book.appendChild(TargetZone);
		book.appendChild(RockParameter);
		root.appendChild(book);
	}
	else
	{
		str.setNum(count+1);
		id.setValue(str);
		str.clear();
		book.setAttributeNode(id);
		switch(_length)
		{
		case 1:
			str = QString::fromLocal8Bit("mm(毫米)");
			break;
		case 2:
			str =QString::fromLocal8Bit("cm(厘米)");
			break;
		case 3:
			str =QString::fromLocal8Bit("m(米)");
			break;
		case 4:
			str =QString::fromLocal8Bit("km(千米)");
			break;
		}
		Unit_lenght.setValue(str);
		switch(_time)
		{
		case 1:
			str = QString::fromLocal8Bit("us(微秒)");
			break;
		case 2:
			str = QString::fromLocal8Bit("ms(毫秒)");
			break;
		case 3:
			str = QString::fromLocal8Bit("s(秒)");
			break;
		}
		Unit_time.setValue(str);
		QStringList UnitSystemMass;
		switch(_mass)
		{
		case 1:
			str = QString::fromLocal8Bit("g(克)");
			break;
		case 2:
			str = QString::fromLocal8Bit("kg(千克)");
			break;
		}
		Unit_mass.setValue(str);
		UnitSystem.setAttributeNode(Unit_lenght);
		UnitSystem.setAttributeNode(Unit_time);
		UnitSystem.setAttributeNode(Unit_mass);

		Area_length.setValue(str.setNum(_pT.Aim_Long));
		Area_widgth.setValue(str.setNum(_pT.Aim_Wide));
		Area_lat.setValue(str.setNum(_pT.AimCenterPointLat));
		Area_lon.setValue(str.setNum(_pT.AimCenterPointLon));
		Area_N_02.setValue(str.setNum(_pT.Length_N_02));
		Area_N_13.setValue(str.setNum(_pT.Length_N_13));

		TargetZone.setAttributeNode(Area_length);
		TargetZone.setAttributeNode(Area_widgth);
		TargetZone.setAttributeNode(Area_lat);
		TargetZone.setAttributeNode(Area_lon);
		TargetZone.setAttributeNode(Area_N_02);
		TargetZone.setAttributeNode(Area_N_13);
		////
		////弹体属性表
		/*text = doc.createTextNode(QString("shiming"));
		RockParameter.appendChild(text);*/

		FragmentNumber.setValue(str.setNum(_pLG.FragmentNumber));
		Frag_Mass.setValue(str.setNum(_pLG.Frag_Mass));
		Rock_WarheadStaticAngle.setValue(str.setNum(_pLG.Rock_WarheadStaticAngle));
		Rock_WarheadStaticAngleToCenter.setValue(str.setNum(_pLG.Rock_WarheadStaticAngleToCenter));
		Rock_RocketVelocity.setValue(str.setNum(_pLG.Rock_RocketVelocity));
		Rock_CEP.setValue(str.setNum(_pLG.Rock_CEP));
		ShellInterDiameter.setValue(str.setNum(_pLG.ShellInterDiameter));
		ShellOuterDiameter.setValue(str.setNum(_pLG.ShellOuterDiameter));
		ShellBrokenDiameter.setValue(str.setNum(_pLG.ShellBrokenDiameter));
		WarheadLength_Whole.setValue(str.setNum(_pLG.WarheadLength_Whole));
		WarheadLength_Clylinder.setValue(str.setNum(_pLG.WarheadLength_Clylinder));
		ShellMass_Clylinder.setValue(str.setNum(_pLG.ShellMass_Clylinder));
		ChargeMass_Clylinder.setValue(str.setNum(_pLG.ChargeMass_Clylinder));
		AllMass_Whole.setValue(str.setNum(_pLG.AllMass_Whole));
		ChargeMass_Whole.setValue(str.setNum(_pLG.ChargeMass_Whole));
		Density.setValue(str.setNum(_pLG.Density));
		ExplosionVelocity.setValue(str.setNum(_pLG.ExplosionVelocity));
		ExplosionHeat.setValue(str.setNum(_pLG.ExplosionHeat));
		ExplosinPressure.setValue(str.setNum(_pLG.ExplosinPressure));
		SC.setValue(str.setNum(_pLG.SC));
		ASL.setValue(str.setNum(_pLG.ASL));
		RC.setValue(str.setNum(_pLG.RC));
		FireLat.setValue(str.setNum(_pLG.FireLat));
		FireLon.setValue(str.setNum(_pLG.FireLon));
		BHE.setValue(str.setNum(_pLG.BHE));
		BHD.setValue(str.setNum(_pLG.BHD));
		Frag_FragmentDamageCriterion.setValue(str.setNum(_pLG.Frag_FragmentDamageCriterion));
		InterpolationNumber.setValue(str.setNum(_pLG.InterpolationNumber));
		QString strList;
		for (int i = 0; i < _pLG.FallingAngle.size();++i)
		{
			strList = strList + str.setNum(_pLG.FallingAngle.at(i))+",";
		}
		FallingAngle.setValue(strList);

		strList.clear();
		for (int i = 0; i < _pLG.FireDistance.size();++i)
		{
			strList = strList + str.setNum(_pLG.FireDistance.at(i))+",";
		}
		FireDistance.setValue(strList);

		RockParameter.setAttributeNode(FragmentNumber);
		RockParameter.setAttributeNode(Frag_Mass);
		RockParameter.setAttributeNode(Rock_WarheadStaticAngle);
		RockParameter.setAttributeNode(Rock_WarheadStaticAngleToCenter);
		RockParameter.setAttributeNode(Rock_RocketVelocity);
		RockParameter.setAttributeNode(Rock_CEP);
		RockParameter.setAttributeNode(ShellInterDiameter);
		RockParameter.setAttributeNode(ShellOuterDiameter);
		RockParameter.setAttributeNode(ShellBrokenDiameter);
		RockParameter.setAttributeNode(WarheadLength_Whole);
		RockParameter.setAttributeNode(WarheadLength_Clylinder);
		RockParameter.setAttributeNode(ShellMass_Clylinder);
		RockParameter.setAttributeNode(ChargeMass_Clylinder);
		RockParameter.setAttributeNode(AllMass_Whole);
		RockParameter.setAttributeNode(ChargeMass_Whole);
		RockParameter.setAttributeNode(Density);
		RockParameter.setAttributeNode(ExplosionVelocity);
		RockParameter.setAttributeNode(ExplosionHeat);
		RockParameter.setAttributeNode(ExplosinPressure);
		RockParameter.setAttributeNode(SC);
		RockParameter.setAttributeNode(ASL);
		RockParameter.setAttributeNode(RC);
		RockParameter.setAttributeNode(FireLat);
		RockParameter.setAttributeNode(FireLon);
		RockParameter.setAttributeNode(BHE);
		RockParameter.setAttributeNode(BHD);
		RockParameter.setAttributeNode(Frag_FragmentDamageCriterion);
		RockParameter.setAttributeNode(InterpolationNumber);
		RockParameter.setAttributeNode(FallingAngle);
		RockParameter.setAttributeNode(FireDistance);
		////
		book.appendChild(UnitSystem);
		book.appendChild(TargetZone);
		book.appendChild(RockParameter);
		root.appendChild(book);
	}
	QFile file(file_Name);
	if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
	{
		return false;
	}
	QTextStream out(&file);
	// 将文档保存到文件，4为子元素缩进字符数
	doc.save(out, 4);
	file.close();

	return true;
};
//
bool XMLOperation::OpenXMLFile()
{
	AreaVector.clear();
	RockVector.clear();
	//选择文件
	QString file_Name = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("打开文件"), "E:/", QString::fromLocal8Bit("XML文件(*.xml)"));

	// 新建QDomDocument类对象，它代表一个XML文档
	QDomDocument doc;
	QFile file(file_Name);
	if (!file.open(QIODevice::ReadOnly))
	{
		//未能正确的打开文件
	}
	// 将文件内容读到doc中
	if (!doc.setContent(&file))
	{
		//未能正确的读取xml文件内容
		file.close();
	}
	// 关闭文件
	file.close();
	// 获得doc的第一个结点，即XML说明
	QDomNode firstNode = doc.firstChild();
	// 返回根元素
	QDomElement docElem = doc.documentElement();
	// 返回根节点的第一个子结点
	QDomNode n = docElem.firstChild();
	// 如果结点不为空，则转到下一个节点
	while(!n.isNull())
	{
		// 如果结点是元素
		if (n.isElement())
		{
			// 将其转换为元素
			QDomElement e = n.toElement();
			// 返回元素标记和id属性的值
			qDebug() << qPrintable(e.tagName())
				<< qPrintable(e.attribute(QString::fromLocal8Bit("编号")));
			// 获得元素e的所有子结点的列表
			QDomNodeList list = e.childNodes();
			// 遍历该列表
			for(int i=0; i<list.count(); i++)
			{
				QDomNode node = list.at(i);
				if(node.isElement())
				{
					QDomElement _pE = node.toElement();
					if (_pE.tagName() == QString::fromLocal8Bit("系统单位"))
					{
						int l,m,t;
						QString _length = _pE.attribute("长度单位");
						if (_length == "mm(毫米)")
						{
							l = 1;
						}
						if (_length == "m(米)")
						{
							l = 3;
						}
						if (_length == "cm(厘米)")
						{
							l = 2;
						}
						if (_length == "km(千米)")
						{
							l = 4;
						}
						QString _mass = _pE.attribute("重量单位");
						if (_mass == "g(克)")
						{
							m = 1;
						}
						if (_mass == "kg(千克)")
						{
							m = 2;
						}
						QString _time= _pE.attribute("时间单位");
						if (_time == "us(微秒)")
						{
							t = 1;
						}
						if (_time == "ms(毫秒)")
						{
							t = 2;
						}
						if (_time == "s(秒)")
						{
							t = 3;
						}
						Bit_UnitSystem *p = new Bit_UnitSystem(l,m,t);
						XMLFileUnity.push_back(p);
						QString str_ = _length+_mass+_time;
						_xmlFileUnity.push_back(str_);
					}
					else if (_pE.tagName() == QString::fromLocal8Bit("目标区域"))
					{
						_TargetArea.Aim_Long = _pE.attribute("目标区域长度").toDouble();
						_TargetArea.Aim_Wide = _pE.attribute("目标区域宽度").toDouble();
						_TargetArea.AimCenterPointLon = _pE.attribute("中心经度").toDouble();
						_TargetArea.AimCenterPointLat = _pE.attribute("中心纬度").toDouble();
						_TargetArea.Length_N_02 = _pE.attribute("长划分").toDouble();
						_TargetArea.Length_N_13 = _pE.attribute("宽划分").toDouble();

						AreaVector.push_back(_TargetArea);
					}
					else if(_pE.tagName() == QString::fromLocal8Bit("弹体属性"))
					{
						_RockObject.Frag_Mass = _pE.attribute("破片质量").toDouble();
						_RockObject.FragmentNumber = _pE.attribute("破片数量").toInt();
						_RockObject.Rock_WarheadStaticAngle = _pE.attribute("火箭弹战斗部静态飞散角").toDouble();
						_RockObject.Rock_WarheadStaticAngleToCenter = _pE.attribute("战斗部静态飞散角分布中心线与弹体系X轴夹角").toDouble();
						_RockObject.Rock_RocketVelocity = _pE.attribute("火箭弹速度").toDouble();
						_RockObject.Rock_CEP = _pE.attribute("火箭弹CEP").toDouble();
						_RockObject.ShellInterDiameter = _pE.attribute("圆柱内径").toDouble();
						_RockObject.ShellOuterDiameter = _pE.attribute("圆柱外径").toDouble();
						_RockObject.ShellBrokenDiameter = _pE.attribute("圆柱破径").toDouble();
						_RockObject.WarheadLength_Whole = _pE.attribute("弹头全部长度").toDouble();
						_RockObject.WarheadLength_Clylinder = _pE.attribute("弹头圆柱长度").toDouble();
						_RockObject.ShellMass_Clylinder = _pE.attribute("圆柱段壳体质量").toDouble();
						_RockObject.ChargeMass_Clylinder = _pE.attribute("圆柱段装药质量").toDouble();
						_RockObject.ChargeMass_Whole = _pE.attribute("装药整体质量").toDouble();
						_RockObject.AllMass_Whole = _pE.attribute("战斗部整体质量").toDouble();
						_RockObject.Density = _pE.attribute("装药密度").toDouble();
						_RockObject.ExplosionVelocity = _pE.attribute("装药爆速").toDouble();
						_RockObject.ExplosionHeat = _pE.attribute("装药暴热").toDouble();
						_RockObject.ExplosinPressure = _pE.attribute("装药爆压").toDouble();
						_RockObject.SC = _pE.attribute("球形破片").toDouble();
						_RockObject.ASL = _pE.attribute("海拔高度").toDouble();
						_RockObject.RC = _pE.attribute("气动阻力系数").toDouble();
						_RockObject.FireLat = _pE.attribute("发射点纬度").toDouble();
						_RockObject.FireLon = _pE.attribute("发射点经度").toDouble();
						_RockObject.BHE = _pE.attribute("炸高期望").toDouble();
						_RockObject.BHD = _pE.attribute("炸高标准差").toDouble();
						_RockObject.Frag_FragmentDamageCriterion = _pE.attribute("毁伤判据").toDouble();
						_RockObject.InterpolationNumber = _pE.attribute("插值表数据个数").toInt();
						//落距，落角
						QStringList FallList= _pE.attribute("落角插值").split(",");
						_RockObject.FallingAngle.clear();
						for (int i = 0; i < FallList.size();++i)
						{
							_RockObject.FallingAngle.push_back(FallList.at(i).toDouble());
						}

						FallList.clear();

						FallList = _pE.attribute("落距插值").split(",");
						_RockObject.FireDistance.clear();
						for (int i = 0; i < FallList.size();++i)
						{
							_RockObject.FireDistance.push_back(FallList.at(i).toDouble());
						}

						RockVector.push_back(_RockObject);
					}
				}
			}
		}
		// 转到下一个兄弟结点
		n = n.nextSibling();
	}
	AreaTable();
	RockTable();
	return true;
};
//
TargetAreaParameter XMLOperation::GetAreaParameter()  
{
	_p = XMLFileUnity.at(area_row);
	TargetAreaParameter p_t =  AreaVector.at(area_row);
	GetRatioChangeArea(p_t,_p);
	return  p_t;
};
//
LGRockParameter XMLOperation::GetLgRockParameter()  
{
	_p = XMLFileUnity.at(rock_row);
	LGRockParameter p_l =  RockVector.at(rock_row);
	GetRatioChangeRock(p_l,_p);
	return p_l;
};
//
void XMLOperation::GetTheUnitSystem(int length,int time,int mass)
{
	_length = length;
	_mass = mass;
	_time = time;
}
//
void XMLOperation::AreaTable()
{
	if (!AreaVector.empty())
	{
		int TRow = 0;
		int TCol = 0;
		_plog->setWindowTitle(QString::fromLocal8Bit("目标区域列表"));
		_playout->addWidget(_pAreaTab);
		_plog->setMinimumHeight(620);
		_plog->resize(800,400);
		//
		QStringList _tabHeadList;
		QString str;
		QFile file("Resource/AreaHead.txt");
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			while (!file.atEnd()) 
			{
				str = file.readLine();
			}
		}
		_tabHeadList = str.split(",");
		TCol = _tabHeadList.size();
		_pAreaTab->setColumnCount(_tabHeadList.size());
		_pAreaTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
		//////设定表头
		_pAreaTab->setHorizontalHeaderLabels(_tabHeadList);
		_pAreaTab->setRowCount(AreaVector.size());
		//
		std::vector<TargetAreaParameter>::const_iterator it_tor = AreaVector.begin();
		for (;it_tor != AreaVector.end();++it_tor)
		{
			_pAreaTab->setItem(TRow,0,new QTableWidgetItem(str.setNum(it_tor->Aim_Long)));
			_pAreaTab->setItem(TRow,1,new QTableWidgetItem(str.setNum(it_tor->Aim_Wide)));
			_pAreaTab->setItem(TRow,2,new QTableWidgetItem(str.setNum(it_tor->AimCenterPointLon)));
			_pAreaTab->setItem(TRow,3,new QTableWidgetItem(str.setNum(it_tor->AimCenterPointLat)));
			_pAreaTab->setItem(TRow,4,new QTableWidgetItem(str.setNum(it_tor->Length_N_02)));
			_pAreaTab->setItem(TRow,5,new QTableWidgetItem(str.setNum(it_tor->Length_N_13)));
			_pAreaTab->setItem(TRow,6,new QTableWidgetItem(_xmlFileUnity.at(TRow)));
			++TRow;
		}
		connect(_pAreaTab,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(GetAreaNum(int,int)));
		//
		_plog->exec();
	}
};
//
void XMLOperation::RockTable()
{
	if (!RockVector.empty())
	{
		int TRow = 0;
		int TCol = 0;
		_plog->setWindowTitle(QString::fromLocal8Bit("弹体参数列表"));
		_playout->removeWidget(_pAreaTab);
		_playout->addWidget(_pRockTab);
		_plog->setMaximumWidth(1800);
		_plog->resize(1200,400);
		//
		QStringList _tabHeadList;
		QString str;
		QFile file("Resource/RockHead.txt");
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			while (!file.atEnd()) 
			{
				str = file.readLine();
			}
		}
		_tabHeadList = str.split(",");
		TCol = _tabHeadList.size();
		_pRockTab->setColumnCount(_tabHeadList.size());
		_pRockTab->setEditTriggers(QAbstractItemView::NoEditTriggers);
		//////设定表头
		_pRockTab->setHorizontalHeaderLabels(_tabHeadList);
		_pRockTab->setRowCount(RockVector.size());
		//
		std::vector<LGRockParameter>::const_iterator it_tor = RockVector.begin();
		for (;it_tor != RockVector.end();++it_tor)
		{
			_pRockTab->setItem(TRow,0,new QTableWidgetItem(str.setNum(it_tor->Frag_Mass)));
			_pRockTab->setItem(TRow,1,new QTableWidgetItem(str.setNum(it_tor->Frag_Mass)));
			_pRockTab->setItem(TRow,2,new QTableWidgetItem(str.setNum(it_tor->Rock_WarheadStaticAngle)));
			_pRockTab->setItem(TRow,3,new QTableWidgetItem(str.setNum(it_tor->Rock_WarheadStaticAngleToCenter)));
			_pRockTab->setItem(TRow,4,new QTableWidgetItem(str.setNum(it_tor->Rock_RocketVelocity)));
			_pRockTab->setItem(TRow,5,new QTableWidgetItem(str.setNum(it_tor->Rock_CEP)));
			_pRockTab->setItem(TRow,6,new QTableWidgetItem(str.setNum(it_tor->ShellInterDiameter)));
			_pRockTab->setItem(TRow,7,new QTableWidgetItem(str.setNum(it_tor->ShellOuterDiameter)));
			_pRockTab->setItem(TRow,8,new QTableWidgetItem(str.setNum(it_tor->ShellBrokenDiameter)));
			_pRockTab->setItem(TRow,9,new QTableWidgetItem(str.setNum(it_tor->WarheadLength_Whole)));
			_pRockTab->setItem(TRow,10,new QTableWidgetItem(str.setNum(it_tor->WarheadLength_Clylinder)));
			_pRockTab->setItem(TRow,11,new QTableWidgetItem(str.setNum(it_tor->ShellMass_Clylinder)));
			_pRockTab->setItem(TRow,12,new QTableWidgetItem(str.setNum(it_tor->ChargeMass_Clylinder)));
			_pRockTab->setItem(TRow,13,new QTableWidgetItem(str.setNum(it_tor->AllMass_Whole)));
			_pRockTab->setItem(TRow,14,new QTableWidgetItem(str.setNum(it_tor->ChargeMass_Whole)));
			_pRockTab->setItem(TRow,15,new QTableWidgetItem(str.setNum(it_tor->Density)));
			_pRockTab->setItem(TRow,16,new QTableWidgetItem(str.setNum(it_tor->ExplosionVelocity)));
			_pRockTab->setItem(TRow,17,new QTableWidgetItem(str.setNum(it_tor->ExplosionHeat)));
			_pRockTab->setItem(TRow,18,new QTableWidgetItem(str.setNum(it_tor->ExplosinPressure)));
			_pRockTab->setItem(TRow,19,new QTableWidgetItem(str.setNum(it_tor->SC)));
			_pRockTab->setItem(TRow,20,new QTableWidgetItem(str.setNum(it_tor->ASL)));
			_pRockTab->setItem(TRow,21,new QTableWidgetItem(str.setNum(it_tor->RC)));
			_pRockTab->setItem(TRow,22,new QTableWidgetItem(str.setNum(it_tor->FireLat)));
			_pRockTab->setItem(TRow,23,new QTableWidgetItem(str.setNum(it_tor->FireLon)));
			_pRockTab->setItem(TRow,24,new QTableWidgetItem(str.setNum(it_tor->BHE)));
			_pRockTab->setItem(TRow,25,new QTableWidgetItem(str.setNum(it_tor->BHD)));
			_pRockTab->setItem(TRow,25,new QTableWidgetItem(str.setNum(it_tor->BHD)));
			_pRockTab->setItem(TRow,26,new QTableWidgetItem(str.setNum(it_tor->Frag_FragmentDamageCriterion)));
			_pRockTab->setItem(TRow,27,new QTableWidgetItem(str.setNum(it_tor->InterpolationNumber)));

			str.clear();
			for (int i = 0; i < it_tor->FallingAngle.size();++i)
			{
				QString str_ff;
				str_ff.setNum(it_tor->FallingAngle.at(i));
				str = str + str_ff+",";
			}
			_pRockTab->setItem(TRow,28,new QTableWidgetItem(str));

			str.clear();
			for (int i = 0; i < it_tor->FireDistance.size();++i)
			{
				QString str_ff;
				str_ff.setNum(it_tor->FireDistance.at(i));
				str = str + str_ff+",";
			}
			_pRockTab->setItem(TRow,29,new QTableWidgetItem(str));
			_pRockTab->setItem(TRow,30,new QTableWidgetItem(_xmlFileUnity.at(TRow)));
			++TRow;
		}
		connect(_pRockTab,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(GetRockNum(int,int)));
		//
		_plog->exec();
	}
};
//
void XMLOperation::GetAreaNum(int row,int column)
{
	area_row = row;
	_plog->close();
};
//
void XMLOperation::GetRockNum(int row,int column)
{
	rock_row = row;
	_plog->close();
};
//
void XMLOperation::SetLocalUnity(Bit_UnitSystem *unity)
{
	_LocalUnity = new Bit_UnitSystem(unity->Get_LengthUnit(),unity->Get_MassUnit(),unity->Get_TimeUnit());
};
//
void XMLOperation::GetRatioChangeArea(TargetAreaParameter &Tarea,const Bit_UnitSystem *pV)
{
	Bit_GroundArea _pArea;
	_pArea.Set_Initial(*pV,Tarea.Aim_Long,Tarea.Aim_Wide,Tarea.Length_N_02,Tarea.Length_N_13);
	_pArea.TransitionUS(*_LocalUnity);


	Tarea.Aim_Long = _pArea.Get_AreaLength();
	Tarea.Aim_Wide = _pArea.Get_AreaWidth();
	Tarea.Length_N_02 = _pArea.Get_LengthDivideV();
	Tarea.Length_N_13 = _pArea.Get_WidthDivideV();
};
//
void XMLOperation::GetRatioChangeRock(LGRockParameter &LRock,const Bit_UnitSystem *pV)
{
	Bit_AirExplosion p_air;
	p_air.Set_Initial(*pV,LRock.BHE,LRock.BHD);
	p_air.TransitionUS(*_LocalUnity);
	LRock.BHE = p_air.Get_AirExplosionHE();
	LRock.BHD = p_air.Get_AirExplosionHS();

	Bit_TerminalData p_ter;
	p_ter.Set_Initial(*pV,LRock.Rock_RocketVelocity,LRock.Rock_CEP);
	p_ter.TransitionUS(*_LocalUnity);
	LRock.Rock_RocketVelocity = p_ter.Get_TerminalV();
	LRock.Rock_CEP = p_ter.Get_CEP();

	ChargeData p_charge;
	p_charge.Set_Initial(0,*pV,LRock.Density,LRock.ExplosionVelocity,LRock.ExplosionHeat,LRock.ExplosinPressure);
	p_charge.TransitionUS(*_LocalUnity);
	LRock.Density = p_charge.Get_Density();
	LRock.ExplosionVelocity = p_charge.Get_ExplosionVelocity();
	LRock.ExplosionHeat = p_charge.Get_ExplosionHeat();
	LRock.ExplosinPressure = p_charge.Get_ExplosinPressure();

	WarheadPowerAnalysisData p_war;
	p_war.Set_Initial(0,*pV,LRock.ShellMass_Clylinder,LRock.ChargeMass_Clylinder,LRock.AllMass_Whole,LRock.ChargeMass_Whole,
		0,0,
		LRock.ShellInterDiameter,LRock.ShellOuterDiameter,LRock.ShellBrokenDiameter,LRock.WarheadLength_Whole,LRock.WarheadLength_Clylinder);
	p_war.TransitionUS(*_LocalUnity);
	LRock.ChargeMass_Clylinder    =p_war.Get_ChargeMassClylinder();
	LRock.ChargeMass_Whole        = p_war.Get_ChargeMassWhole();
	LRock.ShellBrokenDiameter     = p_war.Get_ShellBrokenDiameter();
	LRock.ShellInterDiameter      = p_war.Get_ShellInterDiameter();
	LRock.ShellMass_Clylinder     = p_war.Get_ShellMassClylinder();
	LRock.ShellOuterDiameter      = p_war.Get_ShellOuterDiameter();
	LRock.WarheadLength_Clylinder = p_war.Get_WarheadLengthClylinder();
	LRock.WarheadLength_Whole     =p_war.Get_WarheadLengthWhole();
	LRock.AllMass_Whole           =p_war.Get_AllMassWhole();

	Bit_RocketAnalyse p_rocker;

	LRock.ASL = LRock.ASL*_p->Get_LengthCoefficient()/_LocalUnity->Get_LengthCoefficient();
	LRock.Frag_dis = LRock.Frag_dis*_p->Get_LengthCoefficient()/_LocalUnity->Get_LengthCoefficient();
	LRock.Frag_FragmentDamageCriterion = LRock.Frag_FragmentDamageCriterion*_p->Get_LengthCoefficient()/_LocalUnity->Get_LengthCoefficient();
	LRock.Frag_Mass = LRock.Frag_Mass*_p->Get_TimeCoefficient()/_LocalUnity->Get_TimeCoefficient();
	LRock.Frag_ResidualVelocity_Initialization = LRock.Frag_ResidualVelocity_Initialization*_p->Get_TimeCoefficient()/_LocalUnity->Get_TimeCoefficient();
	LRock.RC = LRock.RC*_p->Get_TimeCoefficient()/_LocalUnity->Get_TimeCoefficient();
	
	for (int i = 0; i < LRock.FireDistance.size();++i)
	{
		LRock.FireDistance.at(i) = LRock.FireDistance.at(i)*_p->Get_LengthCoefficient()/_LocalUnity->Get_LengthCoefficient();
	}

};
