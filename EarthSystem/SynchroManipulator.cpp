#include "../../Public/VRSoft.h"
#include "../../Public/EarthSystem/EarthSystem.h"
#include "SynchroManipulator.h"
#include "SynchroManipManager.h"
#include "Compass.h"
namespace VR_Soft
{
	const double MAX_DISTANCE = 37467894.0;

	CSynchroManipulator::CSynchroManipulator(void)
	{
		getSettings()->setArcViewpointTransitions( true ); 
	}


	CSynchroManipulator::~CSynchroManipulator(void)
	{
	}

	// 设置视点
	void CSynchroManipulator::SetViewPoint( const osgEarth::Viewpoint& vp, double duration_s/* =0.0*/ )
	{
		setViewpoint(vp, duration_s);
	}

	void CSynchroManipulator::pan( double dx, double dy )
	{
		osgEarth::Util::EarthManipulator::pan(dx, dy);
		
		SendSynchro();
	}

	// 双击
	bool CSynchroManipulator::handlePointAction( const osgEarth::Util::EarthManipulator::Action& action, float mx, float my, osg::View* view )
	{
		if (action._type == ACTION_NULL)
			return true;

		osg::Vec3d point;
		if ( screenToWorld( mx, my, view, point ))
		{
			switch( action._type )
			{
			case ACTION_GOTO:
				{
					osgEarth::Viewpoint here = getViewpoint();                
					here.focalPoint()->fromWorld(_srs.get(), point);

					double duration_s = GetDoubleOption(action, OPTION_DURATION, 1.0);
					double range_factor = GetDoubleOption(action, OPTION_GOTO_RANGE_FACTOR, 1.0);


					here.range() = here.range().get() * range_factor;
					//here.setRange( here.getRange() * range_factor );

					if (here.getRange() >= MAX_DISTANCE)
					{
						here.setRange(MAX_DISTANCE);
					}

					SendSynchro(here, duration_s);

					setViewpoint( here, duration_s );
				}
				break;
			default:
				break;
			}
		}
		return true;
	}

	// 发送同步
	void CSynchroManipulator::SendSynchro( double duration_s /*= 0.0*/ )
	{
		// 判断是否跟着目标
		
		if (NULL == getTetherNode())
		{
			const osgEarth::Viewpoint& vp = getViewpoint();

			CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
			pSynchroManip->SetViewPoint(this, vp, duration_s);
		}
		else
		{
			// 设置距离
			double dDistance = getDistance();
			CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
			pSynchroManip->SetDistance(this, dDistance);
		}
		
		//CSynchroManipManager::GetInstance().SetViewPoint(this, vp, duration_s);
	}

	// 发送同步
	void CSynchroManipulator::SendSynchro( const osgEarth::Viewpoint& vp, double duration_s /*= 0.0*/ )
	{
		CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
		pSynchroManip->SetViewPoint(this, vp, duration_s);
		// CSynchroManipManager::GetInstance().SetViewPoint(this, vp, duration_s);
	}


	// 缩放
	void CSynchroManipulator::zoom( double dx, double dy )
	{
		
		osgEarth::Util::EarthManipulator::zoom(dx, dy);

		double d = getDistance();
		if (d >= MAX_DISTANCE)
		{
			setDistance(MAX_DISTANCE);
		}
		

		SendSynchro();
	}

	double CSynchroManipulator::GetDoubleOption( const osgEarth::Util::EarthManipulator::Action& action, int option, double defaultValue )
	{
		for(osgEarth::Util::EarthManipulator::ActionOptions::const_iterator i = action._options.begin(); i != action._options.end(); i++ ) {
			if ( i->option() == option )
				return i->doubleValue();
		}

		return (defaultValue);
	}

	// 旋转
	void CSynchroManipulator::rotate( double dx, double dy )
	{
		osgEarth::Util::EarthManipulator::rotate(dx, dy);

		SendSynchro();
	}

	// 事件处理器
	bool CSynchroManipulator::handleKeyboardAction( const osgEarth::Util::EarthManipulator::Action& action, double duration_s /*= DBL_MAX */)
	{
		bool bHandle = osgEarth::Util::EarthManipulator::handleAction(action, 0, 0, duration_s); //handleKeyboardAction(action, duration_s);

		if (osgEarth::Util::EarthManipulator::ACTION_HOME == action._type)
		{
			CSynchroManipManager* pSynchroManip = (CSynchroManipManager*)(ISynchroManIpManager::GetInstancePtr());
			pSynchroManip->SetHomeViewPoint(this, _homeViewpoint.value(), duration_s == 0.0 ? 5.0 : duration_s);
			//SendSynchro(duration_s);
		}

		return (bHandle);
	}

	// 设置跟踪实体
	void CSynchroManipulator::SetTrackEntity( IEntityBase* pIEntity )
	{
		
	}

	void CSynchroManipulator::SlotZoom( double value )
	{
		double dx = value*(-0.0005);
		double dy = value*(-0.0005);

		dx *= getSettings()->getMouseSensitivity();
		dy *= getSettings()->getMouseSensitivity();

		zoom(dx, dy);
	}

	void CSynchroManipulator::SlotTraval(const osg::Vec2& _direction )
	{
		double dx = _direction.x()*(-0.02);
		double dy = _direction.y()*(-0.01);

		dx *= getSettings()->getMouseSensitivity();
		dy *= getSettings()->getMouseSensitivity();

		pan(dx, dy);
	}

	void CSynchroManipulator::SetCompass( Compass* pCompass )
	{
		m_pCompass = pCompass;
	}

	void CSynchroManipulator::SlotPitch(const osg::Vec2& _direction )
	{
		double dx = -_direction.x()*0.0005;
		double dy = -_direction.y()*0.0005;

		dx *= getSettings()->getMouseSensitivity();
		dy *= getSettings()->getMouseSensitivity();

		if ( getSettings()->getSingleAxisRotation() )
		{
			if ( ::fabs(dx) > ::fabs(dy) )
			{
				dy = 0.0;
			}
			else
			{
				dx = 0.0;
			}
		}

		rotate(dx, dy);
	}


}
