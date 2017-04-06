#include "../../Public/VRSoft.h"
#include "TreeUI.h"

#include <QDoubleSpinBox>


CTreeUI::CTreeUI(void)
{
//	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->Register(this);
	m_title = "xyzw";
}


CTreeUI::~CTreeUI(void)
{
//	VR_Soft::IComManager::GetInstance().GetAttributeUiFactory()->UnRegister(this);
}



VR_Soft::IAttributeItemUI* CTreeUI::Clone(void)
{
	return (new CTreeUI());
}

void CTreeUI::SetInfor(void)
{
	

	//// ��ú�ѡ�б�
	//const VR_Soft::IAttributeItem::LstCandidatas& lstCanditatas = pIItem->GetCandidatas();
	//VR_Soft::IAttributeItem::LstCandidatas::const_iterator cstItor = lstCanditatas.begin();
	//for (; lstCanditatas.end() != cstItor; ++cstItor)
	//{
	//	VR_Soft::VRString &str = (*cstItor)->GetValueToString();
	//	// m_treeWidget.addItem(QString::fromLocal8Bit(str.c_str()));
	//}
	
}

// ������Ϣ
void CTreeUI::SaveInfo(void)
{

}

// �������
VR_Soft::Contrl CTreeUI::GetContrlType(void)
{
	return VR_Soft::CTRL_TREE;
}

// ��ÿؼ�
void CTreeUI::GetContrl(void* pContrl)
{
	QTreeWidgetItem* pTreeWidgetItem = static_cast<QTreeWidgetItem*>(pContrl);
	if (NULL == pTreeWidgetItem)
	{
		return;
	}

	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	if (NULL == pIItem)
	{
		return;
	}

	//QTreeWidgetItem* pSubTreeWidgetItem = new QTreeWidgetItem(pTreeWidgetItem);
	pTreeWidgetItem->addChild(this);
	
	QString qstrName = QString::fromLocal8Bit(pIItem->GetTypeName().c_str());
	setText(0, qstrName);
	VR_Soft::VRString &str = pIItem->GetValueToString();
	QString qstr(str.c_str());

	QStringList qstrShowList;
	if (0 == qstrName.compare(QString::fromLocal8Bit("λ��")) || 0 == qstrName.compare(QString::fromLocal8Bit("Ŀ��")))
	{
		qstrShowList.append(QString::fromLocal8Bit("����(��)"));
		qstrShowList.append(QString::fromLocal8Bit("γ��(��)"));
		qstrShowList.append(QString::fromLocal8Bit("�߶�(��)"));
	}
	else if (0 == qstrName.compare(QString::fromLocal8Bit("����")))
	{
		qstrShowList.append(QString::fromLocal8Bit("ˮƽ(��)"));
		qstrShowList.append(QString::fromLocal8Bit("����(��)"));
		qstrShowList.append(QString::fromLocal8Bit("����(��)"));
	}
	else if (0 == qstrName.compare(QString::fromLocal8Bit("��ת")))
	{
		qstrShowList.append(QString::fromLocal8Bit("����(��)"));
		qstrShowList.append(QString::fromLocal8Bit("����(��)"));
		qstrShowList.append(QString::fromLocal8Bit("����(��)"));
	}
	else
	{
		qstrShowList.append(QString::fromLocal8Bit("x"));
		qstrShowList.append(QString::fromLocal8Bit("y"));
		qstrShowList.append(QString::fromLocal8Bit("z"));
		qstrShowList.append(QString::fromLocal8Bit("w"));
	}

	QStringList qstrList = qstr.split(",");
	for (int index = 0; index < qstrList.count(); ++index)
	{
		QTreeWidgetItem* pItemUI = new QTreeWidgetItem(this);
		pItemUI->setText(0, qstrShowList.at(index));
		QDoubleSpinBox* pDoubleSpinBox = new QDoubleSpinBox;
		m_lstDoubleSpinBox.push_back(pDoubleSpinBox);
		QObject::connect(pDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(setValueToSystem(double)));
		pDoubleSpinBox->setMaximum(LLONG_MAX);
		pDoubleSpinBox->setMinimum(-LLONG_MIN);
		pDoubleSpinBox->setDecimals(7);
		double dValue = qstrList.at(index).toDouble();
		pDoubleSpinBox->setValue(dValue);
		pTreeWidgetItem->treeWidget()->setItemWidget(pItemUI, 1, pDoubleSpinBox);
	}
}


void CTreeUI::setValueToSystem(double d)
{
	VR_Soft::IAttributeItem* pIItem = GetAttributeItem();
	osg::Vec3d v(0.0f, 0.0f, 0.0f);
	// ������е�����
	const int nChildCount = childCount();
	if (nChildCount == 3)
	{
		v.x() = m_lstDoubleSpinBox[0]->value();

		v.y() = m_lstDoubleSpinBox[1]->value();

		v.z() = m_lstDoubleSpinBox[2]->value();

		pIItem->SetValue(v);
	}
	//pIItem->SetValue((float)d);
}
