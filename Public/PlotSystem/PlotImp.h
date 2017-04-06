/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  标绘的模板头文件		                                        */
/* 时间： 2016-09-16                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_PLOTIMP_H_
#define _PUBLIC_PLOTIMP_H_

namespace VR_Soft
{
	template <class T>
	class CPlotImp : public T
	{
	public:
		// 构造函数
		explicit CPlotImp(const uint64_t ID, const VRString& strName);
		// 析构函数
		virtual ~CPlotImp(void);

		// 获得ID
		virtual uint64_t GetID(void) const;
		// 设置名称
		virtual void SetName(const VRString& strName) ;
		// 获得名称
		virtual VRString GetName(void) const ;
		// 添加一个点进入属性中
		virtual void AddKeyPoint(const osg::Vec3d& vPos) ;
		// 移除一个点
		virtual void RemoveKeyPoint(const int index) ;
		// 更改点
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos);
		// 获得某一个关键点
		virtual osg::Vec3d GetKeyPoint(int index) const ;
		// 获得路径关键点
		virtual const IPlot::ListPoints& GetKeyPoints(void) const;
		// 获得路径点
		virtual const IPlot::ListPoints& GetPathPoints(void) const;
		// 获得指定路径点
		virtual osg::Vec3d GetPathPoint(const int index) const ;
		// 设置路径策略
		virtual void SetPathStrategy(const IPathStrategy* pIPathStratey);
		// 获得路径策略
		virtual IPathStrategy* GetPathStrtegy(void) const ;
		// 设置渲染
		virtual void SetFeatureGeomtry(const IFeatureGeomtry* pIFeatureGeomtry) ;
		// 获得渲染
		virtual IFeatureGeomtry* GetFeatureGeomtry(void) const ;

	protected:
		uint64_t m_ID;
		VRString m_strName; // 名称
		IPathStrategy* m_pIPathStrategy; // 路径策略
		IFeatureGeomtry* m_pIFeatureGeomtry; // 显示路径
		IPlot::ListPoints m_listKeyPoints; // 关键点位置
		IPlot::ListPoints m_listPathPoints; // 关键点位置

	};

	template <class T>
	CPlotImp<T>::CPlotImp(const uint64_t ID, const VRString& strName)
		:m_ID(ID), m_strName(strName),m_pIPathStrategy(NULL), m_pIFeatureGeomtry(NULL)
	{

	}

	template <class T>
	CPlotImp<T>::~CPlotImp(void)
	{
		VRSOFT_DELETE(m_pIFeatureGeomtry);
		VRSOFT_DELETE(m_pIPathStrategy);
	}

	// 获得ID
	template <class T>
	uint64_t CPlotImp<T>::GetID( void ) const
	{
		return (m_ID);
	}

	// 设置名称
	template <class T>
	void CPlotImp<T>::SetName( const VRString& strName )
	{
		m_strName = strName;
	}

	// 获得名称
	template <class T>
	VRString CPlotImp<T>::GetName( void ) const
	{
		return (m_strName);
	}

	// 添加一个点进入属性中
	template <class T>
	void CPlotImp<T>::AddKeyPoint( const osg::Vec3d& vPos )
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

		m_pIFeatureGeomtry->SetAllPoints(m_listPathPoints);
	}

	// 移除一个点
	template <class T>
	void CPlotImp<T>::RemoveKeyPoint( const int index )
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

		m_pIFeatureGeomtry->SetAllPoints(m_listPathPoints);


	}

	// 更改点
	template <class T>
	void CPlotImp<T>::ChangeKeyPoint( const int index, const osg::Vec3d& vPos )
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
	template <class T>
	osg::Vec3d CPlotImp<T>::GetKeyPoint( int index ) const
	{
		if (index < 0)
		{
			return (osg::Vec3());
		}

		if (index >= (int)m_listKeyPoints.size())
		{
			return (m_listKeyPoints[index]);
		}

		return (m_listKeyPoints[index]);
	}

	// 获得路径关键点
	template <class T>
	const IPath::ListPoints& CPlotImp<T>::GetKeyPoints( void ) const
	{
		return (m_listKeyPoints);
	}

	// 获得路径点
	template <class T>
	const IPath::ListPoints& CPlotImp<T>::GetPathPoints( void ) const
	{
		return (m_listPathPoints);
	}

	// 获得指定路径点
	template <class T>
	osg::Vec3d CPlotImp<T>::GetPathPoint( const int index ) const
	{
		if (index < 0)
		{
			return (osg::Vec3());
		}

		if (index > (int)m_listPathPoints.size())
		{
			return (osg::Vec3());
		}

		return (m_listPathPoints[index]);
	}

	// 设置路径策略
	template <class T>
	void CPlotImp<T>::SetPathStrategy( const IPathStrategy* pIPathStratey )
	{
		m_pIPathStrategy = const_cast<IPathStrategy*>(pIPathStratey);
	}

	// 获得路径策
	template <class T>
	IPathStrategy* CPlotImp<T>::GetPathStrtegy( void ) const
	{
		return (m_pIPathStrategy);
	}

	// 设置渲染
	template <class T>
	void CPlotImp<T>::SetFeatureGeomtry( const IFeatureGeomtry* pIFeatureGeomtry )
	{
		m_pIFeatureGeomtry = const_cast<IFeatureGeomtry*>(pIFeatureGeomtry);
	}

	// 获得渲染
	template <class T>
	IFeatureGeomtry* CPlotImp<T>::GetFeatureGeomtry( void ) const
	{
		return (m_pIFeatureGeomtry);
	}

}

#endif // !_PUBLIC_PLOTIMP_H_