#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "SynchroMainpulator2D.h"
#include "SynchroManipManager.h"

namespace VR_Soft
{
	CSynchroMainpultor2D::CSynchroMainpultor2D(void)
	{
	}


	CSynchroMainpultor2D::~CSynchroMainpultor2D(void)
	{
	}

	// 设置视点
	void CSynchroMainpultor2D::SetViewPoint( const osgEarth::Viewpoint& vp, double duration_s /*= 0.0 */ )
	{
		m_dPitch = vp.getPitch();
		m_dHeading = vp.getHeading();

		osgEarth::Viewpoint vw(vp);
		vw.setPitch(-89.0) ;
		vw.setHeading(0.0);
		//double dPtich = vp.getPitch();
		CSynchroManipulator::SetViewPoint(vw, duration_s);
	}

	// 发送同步
	void CSynchroMainpultor2D::SendSynchro( double duration_s /*=0.0 */ )
	{
		osgEarth::Viewpoint vp = getViewpoint();

		;//_setVPDuration.getValue();
		vp.setHeading(m_dHeading);
		vp.setPitch(m_dPitch);

		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->SetViewPoint(this, vp, duration_s);
//		CSynchroManipManager::GetInstance().SetViewPoint(this, vp, duration_s);
	}

	// 发送同步
	void CSynchroMainpultor2D::SendSynchro( const osgEarth::Viewpoint& vp, double duration_s /*=0.0 */ )
	{
		osgEarth::Viewpoint vw(vp);

		;//_setVPDuration.getValue();
		vw.setHeading(m_dHeading);
		vw.setPitch(m_dPitch);

	//	CSynchroManipManager::GetInstance().SetViewPoint(this, vw, duration_s);
		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->SetViewPoint(this, vp, duration_s);
	}

	// 重置算法
	void CSynchroMainpultor2D::rotate( double dx, double dy )
	{

	}

	// 设置跟踪实体
	void CSynchroMainpultor2D::SetTrackEntity( IEntityBase* pIEntity )
	{
		osg::Node* pNode = pIEntity->GetDrawManager()->GetDrawObj2D();
		setTetherNode(pNode, 5.0);
		getSettings()->setTetherMode(this->TETHER_CENTER);
	}

}
