#include "AttributeBindFrame.h"


CAttributeBindFrame::CAttributeBindFrame(VR_Soft::IEntityBase* pIEntityBase, QWidget* parent)
	:QDialog(parent), m_pIEntity(pIEntityBase)
{
	ui.setupUi(this);

	connect(ui.psbBind, SIGNAL(	clicked (bool)), this, SLOT(BindAttribute()));
	connect(ui.psbUnBind, SIGNAL(	clicked (bool)), this, SLOT(UnBindAttribute()));

	// 初始化
	InitAttribute();
}


CAttributeBindFrame::~CAttributeBindFrame(void)
{
}

// 设置初始化内容
void CAttributeBindFrame::InitAttribute( void )
{
	VR_Soft::IAttributeManager::GetInstance().LoadAttributeDll();
	const VR_Soft::ListString listStr = VR_Soft::IAttributeManager::GetInstance().GetAllAttribute();
	VR_Soft::ListString::const_iterator cstItor = listStr.begin();
	while (listStr.end() != cstItor)
	{
		ui.lstWgtAttribute->addItem(QString::fromLocal8Bit(cstItor->c_str()));
		++cstItor;
	}

	// 获得已经加载的
	if (NULL == m_pIEntity)
	{
		return;
	}

	// 获得所有的属性
	VR_Soft::IEntityBase::ListAttributes listAttributes = m_pIEntity->GetAllAttribute();
	VR_Soft::IEntityBase::ListAttributes::const_iterator actCstItor = listAttributes.begin();
	while (listAttributes.end() != actCstItor)
	{
		const VR_Soft::VRString strName = (*actCstItor)->GetName();
		ui.lstWgtBindAttribute->addItem(QString::fromLocal8Bit(strName.c_str()));
		++actCstItor;
	}
}

bool CAttributeBindFrame::BindAttribute()
{
	if (NULL == m_pIEntity)
	{
		return (false);
	}

	QString strText = ui.lstWgtAttribute->currentItem()->text();
	if (VR_Soft::IAttributeManager::GetInstance().BindAttribute(m_pIEntity, strText.toLocal8Bit().data()))
	{
		ui.lstWgtBindAttribute->addItem(new QListWidgetItem(strText));
	}
	
	return (true);
}

bool CAttributeBindFrame::UnBindAttribute()
{
	if (NULL == m_pIEntity || NULL == ui.lstWgtBindAttribute->currentItem())
	{
		return (false);
	}

	QString strText = ui.lstWgtBindAttribute->currentItem()->text();
	if (VR_Soft::IAttributeManager::GetInstance().UnBindAttribute(m_pIEntity, strText.toLocal8Bit().data()))
	{
		int index = ui.lstWgtBindAttribute->currentRow();
		delete ui.lstWgtBindAttribute->takeItem(index);

	}
	
	return (true);
}
