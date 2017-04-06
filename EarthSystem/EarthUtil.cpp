#include "../../Public/EarthSystem/EarthSystem.h"
#include "EarthUtil.h"
#include <osgEarthFeatures/FeatureIndex>
#include <osgEarth/Registry>
#include <osgEarthSymbology/Stroke>
#include "FeatureManager.h"

namespace VR_Soft
{
	CEarthUtil::CEarthUtil(void)
	{
	}


	CEarthUtil::~CEarthUtil(void)
	{
	}

	// ���캯��
	CFeatureQuery::CFeatureQuery( osgEarth::Util::Controls::ControlCanvas* pContainver )
		:m_pGrid(new osgEarth::Util::Controls::Grid),m_lastFID(0u)
	{
		m_pGrid->setBackColor( osgEarth::Color(osgEarth::Color::Black,0.7f) );
		pContainver->addControl( m_pGrid );
	}

	// ������
	void CFeatureQuery::onHit( osgEarth::ObjectID id )
	{
		// ���������ռ�
		using namespace osgEarth;
		using namespace osgEarth::Features;

		// ���ʸ������
		FeatureIndex* index = Registry::objectIndex()->get<FeatureIndex>(id);
		Feature* feature = index ? index->getFeature(id) : NULL;
		if (NULL != feature && feature->getFID() != m_lastFID)
		{
			// ��ӵ���������
			m_pGrid->clearControls();
			unsigned r=0;

			m_pGrid->setControl( 0, r, new osgEarth::Util::Controls::LabelControl("FID", Color::Red) );
			m_pGrid->setControl( 1, r, new osgEarth::Util::Controls::LabelControl(Stringify()<<feature->getFID(), Color::White) );
			++r;

			const AttributeTable& attrs = feature->getAttrs();
			for( AttributeTable::const_iterator i = attrs.begin(); i != attrs.end(); ++i, ++r )
			{
				m_pGrid->setControl( 0, r, new osgEarth::Util::Controls::LabelControl(i->first, 14.0f, Color::Yellow) );
				m_pGrid->setControl( 1, r, new osgEarth::Util::Controls::LabelControl(i->second.getString(), 14.0f, Color::White) );
			}
			if ( !m_pGrid->visible() )
			{
				m_pGrid->setVisible( true );
				using namespace osgEarth::Util::Controls;
				ControlCanvas* pControlCavas = (ControlCanvas*)m_pGrid->getParent(0);
				pControlCavas->setNodeMask(0xFF);
			}

			m_lastFID = feature->getFID();

			// ���ʸ������
			CFeatureManager::GetInstance().AddFeature(feature);
			// ���õ�ǰ��ʸ��
			CFeatureManager::GetInstance().SetCurFeature(m_lastFID);
		}

	}

	// ����뿪
	void CFeatureQuery::onMiss( void )
	{
		if ( 0u != m_lastFID)
		{
			m_pGrid->setVisible( false );
			using namespace osgEarth::Util::Controls;
			ControlCanvas* pControlCavas = (ControlCanvas*)m_pGrid->getParent(0);
			pControlCavas->setNodeMask(0x00);
		}
		
		m_lastFID = 0u;
		// ���õ�ǰ��ʸ��
		CFeatureManager::GetInstance().SetCurFeature(m_lastFID);
	}

	// ��������¼�����
	bool CFeatureQuery::accept( const osgGA::GUIEventAdapter& ea, const osgGA::GUIActionAdapter& aa )
	{
		return (ea.getEventType() == ea.MOVE);
	}
			

	//////////////////////////////CMeasureToolCallback////////////////////////////////////////////
	// ���캯��
	CMeasureToolCallback::CMeasureToolCallback( osgEarth::Util::Controls::LabelControl* label )
		:m_pLabel(label)
	{

	}

	// ���ȸı�
	void CMeasureToolCallback::onDistanceChanged( osgEarth::Util::MeasureToolHandler* sender, double distance )
	{
		std::stringstream ss;
		ss << std::setprecision(10) << distance << "m" << std::endl; 
		std::string str;
		str = ss.str();
		m_pLabel->setText( str );
	}

	////////////////////////////��깤�߾��//////////////////////////////////////////////
	CMeasureToolHandler::CMeasureToolHandler( osg::Group* group, osgEarth::MapNode* mapNode )
		:osgEarth::Util::MeasureToolHandler(group, mapNode)
	{

	}

	// ������
	bool CMeasureToolHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
	{
		if ( ea.getHandled() )
		{
			return false;
		}


		osgViewer::View* view = static_cast<osgViewer::View*>(aa.asView());                
		if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH && ea.getButton() == _mouseButton)
		{        
			_mouseDown = true;
			_mouseDownX = ea.getX();
			_mouseDownY = ea.getY();
		}
		else if (/*ea.getEventType() == osgGA::GUIEventAdapter::DOUBLECLICK &&*/ ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{        
			if (_gotFirstLocation)
			{
				_gotFirstLocation = false;
				_finished = true;
				aa.requestRedraw(); 
				return true;
			}
		}
		else if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE && ea.getButton() == _mouseButton)
		{        
			float eps = 1.0f;
			_mouseDown = false;
			if (osg::equivalent(ea.getX(), _mouseDownX) && osg::equivalent(ea.getY(), _mouseDownY))
			{
				double lon, lat;
				if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat))
				{
					if (!_gotFirstLocation)
					{
						_finished = false;
						clear();                    
						_gotFirstLocation = true;
						_feature->getGeometry()->push_back( osg::Vec3d( lon, lat, 0 ) );
					}
					else
					{
						if (_lastPointTemporary)
						{
							_feature->getGeometry()->back() = osg::Vec3d( lon, lat, 0 );
							_lastPointTemporary = false;
						}
						else
						{                     
							_feature->getGeometry()->push_back( osg::Vec3d( lon, lat, 0 ) );
						}
						_featureNode->init();

						if (_finished || !_isPath) {
							_gotFirstLocation = false;
						}

						fireDistanceChanged();
						aa.requestRedraw();
					}
				}
			}
		}  

		else if (ea.getEventType() == osgGA::GUIEventAdapter::MOVE)
		{
			if (_gotFirstLocation)
			{
				double lon, lat;
				if (getLocationAt(view, ea.getX(), ea.getY(), lon, lat))
				{
					if (!_lastPointTemporary)
					{
						_feature->getGeometry()->push_back( osg::Vec3d( lon, lat, 0 ) );                 
						_lastPointTemporary = true;
					}                        
					else
					{
						_feature->getGeometry()->back() = osg::Vec3d( lon, lat, 0 );
					}
					_featureNode->init();
					fireDistanceChanged();
					aa.requestRedraw();
				}
			}
		}    
		return false;
	}

}
