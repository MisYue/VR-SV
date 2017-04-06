#include "ArrowLine.h"
#include <iterator>
#include <algorithm>

namespace VR_Soft
{
	CArrowLine::CArrowLine(CPlotStrategy* pPlotStrategy)
		:CBaseContrl(pPlotStrategy)
	{
	}


	CArrowLine::~CArrowLine(void)
	{
	}

	// 添加鼠标点
	void CArrowLine::AddMousePoint( const osg::Vec3d& vMousePoint )
	{
		int nSize = (int)m_mouseContrlPoint.size();
		if (2 > nSize)
		{
			m_mouseContrlPoint.push_back(vMousePoint);
		}
		else
		{
			m_mouseContrlPoint[1] = vMousePoint;
		}

		CBaseContrl::AddMousePoint(vMousePoint);
	}


	CArrowLineStrategy::CArrowLineStrategy( CPlot* pPlot )
		:CPlotStrategy(pPlot)
	{

	}

	CArrowLineStrategy::~CArrowLineStrategy( void )
	{

	}

	// 重新构建
	void CArrowLineStrategy::Rebuild( const std::vector<osg::Vec3d>& listKeyPoints )
	{
		std::vector<osg::Vec3d> listPathPoints;
		double ArrowLenth;  //箭头长度
		double ArrowAngle;  //箭头夹角

		if (listKeyPoints.size() >=2)
		{

			ArrowAngle = 0.4;
			std::copy(listKeyPoints.begin(), listKeyPoints.end(), std::back_inserter(listPathPoints));
			const osg::Vec3d& pE = listKeyPoints[1]; // m_conP->at(m_conP->size()-1);
			const osg::Vec3d& pS = listKeyPoints[0] ; // m_conP->at(m_conP->size()-2);
			const osg::Vec3d& vDis(pE - pS);
			ArrowLenth = vDis.length() * 0.1;
			osg::Vec3d varP;

			double datanx2(atan2(vDis.x() , vDis.y()) - ArrowAngle);
			varP.x() = pE.x() - ArrowLenth * sin(datanx2);  
			varP.y() = pE.y() - ArrowLenth * cos(datanx2);  
			varP.z() = pE.z();
			listPathPoints.push_back(varP);

			// 回画中点
			listPathPoints.push_back(listPathPoints[1]);

			double datany2(atan2(vDis.y() , vDis.x()) - ArrowAngle);

			varP.x() = pE.x() - ArrowLenth * cos(datany2);  
			varP.y() = pE.y() - ArrowLenth * sin(datany2);  
			varP.z() = pE.z();

			listPathPoints.push_back(varP);

			CPlotStrategy::RebuildPlot(listPathPoints);
		}
	}

	double CArrowLineStrategy::GetLengthTwoPoint( const osg::Vec3d& pS, const osg::Vec3d& pE )
	{
		return ((pE - pS).length());
	}



	/////////////////////////////单曲箭头/////////////////////////////////////////////
	CArrowCureLine::CArrowCureLine( CPlotStrategy* pPlotStrategy )
		:CBaseContrl(pPlotStrategy)
	{

	}

	CArrowCureLine::~CArrowCureLine( void )
	{

	}

	// 添加鼠标点
	void CArrowCureLine::AddMousePoint( const osg::Vec3d& vMousePoint )
	{
		int nSize = (int)m_mouseContrlPoint.size();
		if (m_mouseContrlPoint.empty())
		{
			m_mouseContrlPoint.push_back(vMousePoint);
		}
		else
		{
			m_mouseContrlPoint[nSize - 1] = vMousePoint;
		}
		

		CBaseContrl::AddMousePoint(vMousePoint);
	}


	CArrowCureLineStrategy::CArrowCureLineStrategy( CPlot* pPlot )
		:CPlotStrategy(pPlot)
	{

	}

	CArrowCureLineStrategy::~CArrowCureLineStrategy( void )
	{

	}

	// 重新构建
	void CArrowCureLineStrategy::Rebuild( const std::vector<osg::Vec3d>& listKeyPoints )
	{
		std::vector<osg::Vec3d> listPathPoints;
		double ArrowLenth;  //箭头长度
		double ArrowAngle;  //箭头夹角

		int varIb = (int)listKeyPoints.size();

		if (listKeyPoints.size() >=2)
		{

			ArrowAngle = 0.4;
			
			listPathPoints.push_back(listKeyPoints[0]);

			osg::Vec3d varP;
			for (int i = 0; i < varIb-2;++i)
			{
				for (double t = 0.0;t <= 1.0;t+=0.1)
				{
					/*varP = contralPoint.at(i)*((-pow(t,3)+3*pow(t,2)-3*t+1)/6.0f)+contralPoint.at(i+1)*((3.0f*pow(t,3)-6.0*pow(t,2)+4.0)/6.0f)
					+contralPoint.at(i+2)*((-3.0f*pow(t,3)+3*pow(t,2)+3*t+1)/6.0f)+contralPoint.at(i+3)*(pow(t,3)/6.0f);*/
					varP = listKeyPoints[i] * ((pow(1-t,2))/2.0)
						+listKeyPoints[i + 1] * ((-2.0f*pow(t,2)+2*t+1.0)/2.0)
						+listKeyPoints[i + 2] * ((pow(t,2))/2.0);

					listPathPoints.push_back(varP);
				
				}
			}
			listPathPoints.push_back(listKeyPoints[varIb-1]);
		
			const osg::Vec3d& pE = listKeyPoints[varIb- 1]; // m_conP->at(m_conP->size()-1);
			const osg::Vec3d& pS = listKeyPoints[varIb - 2] ; // m_conP->at(m_conP->size()-2);
			const osg::Vec3d& vDis(pE - pS);
			ArrowLenth = vDis.length() * 0.1;

			double datanx2(atan2(vDis.x() , vDis.y()) - ArrowAngle);
			varP.x() = pE.x() - ArrowLenth * sin(datanx2);  
			varP.y() = pE.y() - ArrowLenth * cos(datanx2);  
			varP.z() = pE.z();
			listPathPoints.push_back(varP);

			// 回画中点
			listPathPoints.push_back(listPathPoints[listPathPoints.size() - 2]);

			double datany2(atan2(vDis.y() , vDis.x()) - ArrowAngle);

			varP.x() = pE.x() - ArrowLenth * cos(datany2);  
			varP.y() = pE.y() - ArrowLenth * sin(datany2);  
			varP.z() = pE.z();

			listPathPoints.push_back(varP);

			CPlotStrategy::RebuildPlot(listPathPoints);
		}
	}
}
