/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ģ��ͷ�ļ�		                                        */
/* ʱ�䣺 2016-09-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_PLOTIMP_H_
#define _PUBLIC_PLOTIMP_H_

namespace VR_Soft
{
	template <class T>
	class CPlotImp : public T
	{
	public:
		// ���캯��
		explicit CPlotImp(const uint64_t ID, const VRString& strName);
		// ��������
		virtual ~CPlotImp(void);

		// ���ID
		virtual uint64_t GetID(void) const;
		// ��������
		virtual void SetName(const VRString& strName) ;
		// �������
		virtual VRString GetName(void) const ;
		// ���һ�������������
		virtual void AddKeyPoint(const osg::Vec3d& vPos) ;
		// �Ƴ�һ����
		virtual void RemoveKeyPoint(const int index) ;
		// ���ĵ�
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos);
		// ���ĳһ���ؼ���
		virtual osg::Vec3d GetKeyPoint(int index) const ;
		// ���·���ؼ���
		virtual const IPlot::ListPoints& GetKeyPoints(void) const;
		// ���·����
		virtual const IPlot::ListPoints& GetPathPoints(void) const;
		// ���ָ��·����
		virtual osg::Vec3d GetPathPoint(const int index) const ;
		// ����·������
		virtual void SetPathStrategy(const IPathStrategy* pIPathStratey);
		// ���·������
		virtual IPathStrategy* GetPathStrtegy(void) const ;
		// ������Ⱦ
		virtual void SetFeatureGeomtry(const IFeatureGeomtry* pIFeatureGeomtry) ;
		// �����Ⱦ
		virtual IFeatureGeomtry* GetFeatureGeomtry(void) const ;

	protected:
		uint64_t m_ID;
		VRString m_strName; // ����
		IPathStrategy* m_pIPathStrategy; // ·������
		IFeatureGeomtry* m_pIFeatureGeomtry; // ��ʾ·��
		IPlot::ListPoints m_listKeyPoints; // �ؼ���λ��
		IPlot::ListPoints m_listPathPoints; // �ؼ���λ��

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

	// ���ID
	template <class T>
	uint64_t CPlotImp<T>::GetID( void ) const
	{
		return (m_ID);
	}

	// ��������
	template <class T>
	void CPlotImp<T>::SetName( const VRString& strName )
	{
		m_strName = strName;
	}

	// �������
	template <class T>
	VRString CPlotImp<T>::GetName( void ) const
	{
		return (m_strName);
	}

	// ���һ�������������
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

	// �Ƴ�һ����
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

	// ���ĵ�
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

	// ���ĳһ���ؼ���
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

	// ���·���ؼ���
	template <class T>
	const IPath::ListPoints& CPlotImp<T>::GetKeyPoints( void ) const
	{
		return (m_listKeyPoints);
	}

	// ���·����
	template <class T>
	const IPath::ListPoints& CPlotImp<T>::GetPathPoints( void ) const
	{
		return (m_listPathPoints);
	}

	// ���ָ��·����
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

	// ����·������
	template <class T>
	void CPlotImp<T>::SetPathStrategy( const IPathStrategy* pIPathStratey )
	{
		m_pIPathStrategy = const_cast<IPathStrategy*>(pIPathStratey);
	}

	// ���·����
	template <class T>
	IPathStrategy* CPlotImp<T>::GetPathStrtegy( void ) const
	{
		return (m_pIPathStrategy);
	}

	// ������Ⱦ
	template <class T>
	void CPlotImp<T>::SetFeatureGeomtry( const IFeatureGeomtry* pIFeatureGeomtry )
	{
		m_pIFeatureGeomtry = const_cast<IFeatureGeomtry*>(pIFeatureGeomtry);
	}

	// �����Ⱦ
	template <class T>
	IFeatureGeomtry* CPlotImp<T>::GetFeatureGeomtry( void ) const
	{
		return (m_pIFeatureGeomtry);
	}

}

#endif // !_PUBLIC_PLOTIMP_H_