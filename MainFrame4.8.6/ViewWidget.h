#pragma once

#include <QWidget>

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"

#include "ViewerUI.h"

class CViewWidget : public QWidget
{
	Q_OBJECT

public:
	CViewWidget(void);
	~CViewWidget(void);

	VR_Soft::IViewManager* GetViewerManager(void);

	// ���3D��ͼ
	CViewerUI* Get3DViewe(void);
	// ���2D��ͼ
	CViewerUI* Get2DViewe(void);

public Q_SLOTS:
	void Show2D( void );
	void Show3D( void );
	void show23D(void);

protected:
	// ��ʼ��
	void Init(void);

protected:
	virtual void paintEvent(QPaintEvent *e);

private:
	VR_Soft::IViewManager* m_pIViewrManager;
	CViewerUI* m_p3DViewUI;
	CViewerUI* m_p2DViewUI;
};

