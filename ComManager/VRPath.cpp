#include "../../Public/VRSoft.h"
#include "VRPath.h"

namespace VR_Soft
{
	///////////////////////////////插值算法///////////////////////////////////////////
	void CubicSpline(std::vector<osg::Vec3d>& aSrc, std::vector<osg::Vec3d>& aDst, double dStep)
	{
		if(dStep < 0.0) dStep = 4.0;

		// 删除重复点
		int num = aSrc.size();
		int i = 0; 
		for(i = 0; i < num-1; i++)
		{
			double dx = aSrc[i+1].x()-aSrc[i].x();
			double dy = aSrc[i+1].y()-aSrc[i].y();
			double dz = aSrc[i+1].z()-aSrc[i].z();
			double dd = sqrt(dx*dx+dy*dy+dz*dz);

			if( dd < 0.0001 )
			{
				aSrc.erase(aSrc.begin()+i);
				num -= 1;
				i -= 1;
			}
		}
		if(num<=1)return ;

		// get distance from first point
		int n = aSrc.size();
		double* dis = new double[n];
		double* H   = new double[n];

		dis[0] = 0.0;
		H[0]   = 0.0;
		for( i = 1; i < n; i++)
		{
			double dx = aSrc[i].x()-aSrc[i-1].x();
			double dy = aSrc[i].y()-aSrc[i-1].y();
			double dz = aSrc[i].z()-aSrc[i-1].z();
			double dd = sqrt(dx*dx+dy*dy+dz*dz);
			dis[i] = dis[i-1] + dd;
			H[i]   = dd;
		}

		if(n<3) return ;

		double* A = new double[n]; // Miu
		double* B = new double[n]; // 对角线
		double* C = new double[n]; // Lanmida
		double* D = new double[n];
		double* COEX = new double[n];
		double* COEY = new double[n];
		double* COEZ =  new double[n];
		double* BTA = new double[n];
		double* CTA = new double[n];

		for( i = 1; i < n-1; i++)
		{
			A[i] = H[i] / (H[i]+H[i+1]); 
			B[i] = 2; 
			C[i] = 1 - A[i];
		}
		A[0] = 1;
		B[0] = 2;
		C[0] = 0;
		A[n-1] = 0;
		B[n-1] = 2; 
		C[n-1] = 1;

		// get  coef of function " x = x(s) " 
		for( i = 1; i < n-1; i++)
		{
			D[i] = 3*( C[i]*(aSrc[i].x()-aSrc[i-1].x())/H[i] + A[i]*(aSrc[i+1].x()-aSrc[i].x())/H[i+1] );
		}

		D[0]   =  3.0*(aSrc[1].x()   - aSrc[0].x())  /H[1]; 
		D[n-1] =  3.0*(aSrc[n-1].x() - aSrc[n-2].x())/H[n-1]; 

		BTA[0] = C[0] / B[0]; 
		for( i = 1; i < n-1; i++)
		{
			BTA[i] = C[i] / (B[i] - A[i]*BTA[i-1]);
		}
		CTA[0] = D[0] / B[0];
		for( i = 1; i < n; i++)
		{
			CTA[i] = (D[i] - A[i]*CTA[i-1]) / (B[i] - A[i]*BTA[i-1]); 
		}
		COEX[n-1] = CTA[n-1]; 
		for( i = n-2; i >= 0; i--)
		{
			COEX[i] = CTA[i] - BTA[i]*COEX[i+1];
		}

		//get  coef of function " y = y(s) " 
		for( i = 1; i < n-1; i++)
		{
			D[i] = 3*( C[i]*(aSrc[i].y()-aSrc[i-1].y())/H[i] + A[i]*(aSrc[i+1].y()-aSrc[i].y())/H[i+1] );
		}

		D[0]   =  3*(aSrc[1].y() - aSrc[0].y())/H[1]; 
		D[n-1] =  3*(aSrc[n-1].y() - aSrc[n-2].y())/H[n-1]; 

		CTA[0] = D[0] / B[0];
		for( i = 1; i < n; i++)
		{
			CTA[i] = (D[i] - A[i]*CTA[i-1]) / (B[i] - A[i]*BTA[i-1]); 
		}
		COEY[n-1] = CTA[n-1]; 
		for( i = n-2; i >= 0; i--)
		{
			COEY[i] = CTA[i] - BTA[i]*COEY[i+1];
		}

		//get  coef of function " Z = Z(s) " 
		for( i = 1; i < n-1; i++)
		{
			D[i] = 3*( C[i]*(aSrc[i].z()-aSrc[i-1].z())/H[i] + A[i]*(aSrc[i+1].z()-aSrc[i].z())/H[i+1] );
		}

		D[0]   =  3*(aSrc[1].z() - aSrc[0].z())/H[1]; 
		D[n-1] =  3*(aSrc[n-1].z() - aSrc[n-2].z())/H[n-1]; 

		CTA[0] = D[0] / B[0];
		for( i = 1; i < n; i++)
		{
			CTA[i] = (D[i] - A[i]*CTA[i-1]) / (B[i] - A[i]*BTA[i-1]); 
		}
		COEZ[n-1] = CTA[n-1]; 
		for( i = n-2; i >= 0; i--)
		{
			COEZ[i] = CTA[i] - BTA[i]*COEZ[i+1];
		}

		double dLen = 0.0; 
		osg::Vec3d pt;
		for( i = 1; i < n; i++)
		{
			while(dLen <= dis[i])
			{
				pt.x() =  COEX[i-1]*(dis[i]-dLen)*(dis[i]-dLen)*(dLen-dis[i-1])/(H[i]*H[i])
					-COEX[i]*(dLen-dis[i-1])*(dLen-dis[i-1])*(dis[i]-dLen)/(H[i]*H[i])
					+aSrc[i-1].x()*(dis[i]-dLen)*(dis[i]-dLen)*(2*(dLen-dis[i-1])+H[i])/(H[i]*H[i]*H[i])
					+aSrc[i].x()*(dLen-dis[i-1])*(dLen-dis[i-1])*(2*(dis[i]-dLen)+H[i])/(H[i]*H[i]*H[i]);

				pt.y() =  COEY[i-1]*(dis[i]-dLen)*(dis[i]-dLen)*(dLen-dis[i-1])/(H[i]*H[i])
					-COEY[i]*(dLen-dis[i-1])*(dLen-dis[i-1])*(dis[i]-dLen)/(H[i]*H[i])
					+aSrc[i-1].y()*(dis[i]-dLen)*(dis[i]-dLen)*(2*(dLen-dis[i-1])+H[i])/(H[i]*H[i]*H[i])
					+aSrc[i].y()*(dLen-dis[i-1])*(dLen-dis[i-1])*(2*(dis[i]-dLen)+H[i])/(H[i]*H[i]*H[i]);

				pt.z() =  COEZ[i-1]*(dis[i]-dLen)*(dis[i]-dLen)*(dLen-dis[i-1])/(H[i]*H[i])
					-COEZ[i]*(dLen-dis[i-1])*(dLen-dis[i-1])*(dis[i]-dLen)/(H[i]*H[i])
					+aSrc[i-1].z()*(dis[i]-dLen)*(dis[i]-dLen)*(2*(dLen-dis[i-1])+H[i])/(H[i]*H[i]*H[i])
					+aSrc[i].z()*(dLen-dis[i-1])*(dLen-dis[i-1])*(2*(dis[i]-dLen)+H[i])/(H[i]*H[i]*H[i]);

				aDst.push_back(pt);
				dLen += dStep;
			}
		}

		delete[] dis; delete[] A; delete[] B; delete[] C; delete[] D; delete[] H;
		delete[] COEX;  delete[] COEY; delete[] COEZ; delete[] BTA; delete[] CTA;
	}
	///////////////////////////////插值算法///////////////////////////////////////////


	// 构造函数
	CVRPath::CVRPath( const uint64_t ID, const VRString& strName )
		:m_ID(ID), m_strName(strName),m_pIPathStrategy(NULL), m_pIFeatureGeomtry(NULL)
	{

	}

	// 析构函数
	CVRPath::~CVRPath( void )
	{
		VRSOFT_DELETE(m_pIFeatureGeomtry);
		VRSOFT_DELETE(m_pIPathStrategy);
	}

	// 获得ID
	uint64_t CVRPath::GetID( void ) const
	{
		return (m_ID);
	}

	// 设置名称
	void CVRPath::SetName( const VRString& strName )
	{
		m_strName = strName;
	}

	// 获得名称
	VR_Soft::VRString CVRPath::GetName( void ) const
	{
		return (m_strName);
	}

	// 添加一个点进入属性中
	void CVRPath::AddKeyPoint( const osg::Vec3d& vPos )
	{
		m_listKeyPoints.push_back(vPos);
		if (m_pIPathStrategy != NULL)
		{
			 m_listPathPoints = m_pIPathStrategy->ComputePath(m_listKeyPoints);
		}
		else
		{
			m_listPathPoints = m_listKeyPoints;
		}

		// 插值计算
		InterPolate();

		m_pIFeatureGeomtry->SetAllPoints(m_listPathPoints);
		
		// m_pIFeatureGeomtry->SetPoint(m_listKeyPoints.size() - 1, vPos);
	}

	// 移除一个点
	void CVRPath::RemoveKeyPoint( const int index )
	{
		if (index < 0)
		{
			return;
		}

		if (index > (int)m_listKeyPoints.size())
		{
			return;
		}

		ListPoints::iterator itor = m_listKeyPoints.begin();
		for (int i = 0; m_listKeyPoints.end() != itor; ++i )
		{
			if (i == index)
			{
				m_listKeyPoints.erase(itor);
				break;
			}
		}

		if (m_pIPathStrategy != NULL)
		{
			m_listPathPoints = m_pIPathStrategy->ComputePath(m_listKeyPoints);
		}
		else
		{
			m_listPathPoints = m_listKeyPoints;
		}

	//	m_pIFeatureGeomtry->SetAllPoints(m_listPathPoints);
		m_pIFeatureGeomtry->Remove(index);


	}

	// 更改点
	void CVRPath::ChangeKeyPoint( const int index, const osg::Vec3d& vPos )
	{
		if (index < 0)
		{
			return;
		}

		if (index > (int)m_listKeyPoints.size())
		{
			return;
		}

		m_listKeyPoints[index] = vPos;

		if (m_pIPathStrategy != NULL)
		{
			m_listPathPoints = m_pIPathStrategy->ComputePath(m_listKeyPoints);
		}
		else
		{
			m_listPathPoints = m_listKeyPoints;
		}

		m_pIFeatureGeomtry->SetAllPoints(m_listPathPoints);
	}

	// 获得某一个关键点
	osg::Vec3d CVRPath::GetKeyPoint( int index ) const
	{
		if (index < 0)
		{
			return (osg::Vec3());
		}

		if (index > (int)m_listKeyPoints.size())
		{
			return (m_listKeyPoints[index - 1]);
		}

		return (m_listKeyPoints[index]);
	}

	// 获得路径关键点
	const IPath::ListPoints& CVRPath::GetKeyPoints( void ) const
	{
		return (m_listKeyPoints);
	}

	// 获得路径点
	const IPath::ListPoints& CVRPath::GetPathPoints( void ) const
	{
		return (m_listPathPoints);
	}

	// 获得指定路径点
	osg::Vec3d CVRPath::GetPathPoint( const int index ) const
	{
		if (index < 0)
		{
			return (osg::Vec3());
		}

		if (index >= (int)m_listPathPoints.size())
		{
			return (m_listPathPoints[m_listPathPoints.size() - 1]);
		}

		return (m_listPathPoints[index]);
	}

	// 设置路径策略
	void CVRPath::SetPathStrategy( const IPathStrategy* pIPathStratey )
	{
		m_pIPathStrategy = const_cast<IPathStrategy*>(pIPathStratey);
	}

	// 获得路径策
	IPathStrategy* CVRPath::GetPathStrtegy( void ) const
	{
		return (m_pIPathStrategy);
	}

	// 设置渲染
	void CVRPath::SetFeatureGeomtry( const IFeatureGeomtry* pIFeatureGeomtry )
	{
		m_pIFeatureGeomtry = const_cast<IFeatureGeomtry*>(pIFeatureGeomtry);
	}

	// 获得渲染
	IFeatureGeomtry* CVRPath::GetFeatureGeomtry( void ) const
	{
		return (m_pIFeatureGeomtry);
	}

	// 插值计算
	void CVRPath::InterPolate( void )
	{
		m_listPathPoints.clear();

		// 判断当前点是否大于一个
		int nSize = (int)m_listKeyPoints.size();
		if (nSize < 2)
		{
			m_listPathPoints = m_listKeyPoints;
			return;
		}

		// 转换成世界坐标
		osg::Vec3d vTempPos;
		ListPoints listWordPos;
		for (int index = 0; index < nSize; ++index)
		{
			CConvert::LatLongHeightToWord(m_listKeyPoints[index], vTempPos);
			listWordPos.push_back(vTempPos);
		}

		// 计算总长度
		double dLength = 0.0;
		for (int index = 1; index < nSize; ++index)
		{
			dLength += (listWordPos[index] - listWordPos[index - 1]).length();
		}

		// 计算步长
		double dStep = dLength / 1000;

		// 进行曲线插值
		CubicSpline(listWordPos, m_listPathPoints, dStep);

		// 将世界坐标转换回地理坐标
		nSize = (int)m_listPathPoints.size();
		for (int index = 0; index < nSize; ++index)
		{
			CConvert::WordToLatLongHeight(m_listPathPoints[index], vTempPos);
			m_listPathPoints[index] = vTempPos;
			
		}
	}

}