/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʸ�����ݹ�����	                                            */
/* ʱ�䣺 2016-09-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _FEATUREMANAGER_H_
#define _FEATUREMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

#include <osgEarthFeatures/Feature>

namespace VR_Soft
{
	class IFeature; 

	class CFeatureManager : public CSingleton<CFeatureManager>, public IFeatureManager
	{
	public:
		typedef boost::unordered_map<unsigned long, IFeature*> ListFeatures;
	public:
		// ���캯��
		CFeatureManager(void);
		// ��������
		virtual ~CFeatureManager(void);

		// ���ʸ������
		virtual bool AddFeature(IFeature* pIFearth);
		// �Ƴ�ʸ������
		virtual void RemoveFeature(unsigned long ID);
		// ��ѯID
		virtual IFeature* GetFeature(unsigned long ID) const;
		// ��õ�ǰ��ѡ���ʸ��
		virtual IFeature* GetCurFeature(void) const;

	public:
		// ���õ�ǰ��ʸ������
		virtual void SetCurFeature(IFeature* pIFeature);
		// ���õ�ǰ��ʸ������
		virtual void SetCurFeature(unsigned long ID);
		// ���ʸ��
		virtual bool AddFeature(osgEarth::Features::Feature* pIFeature);

	protected:
		// �������
		void Clear(void);

	private:
		ListFeatures m_listFeatures;
		IFeature* m_pICurFeature; // ��ǰ��ʸ������
	};
}


#endif // !_FEATUREMANAGER_H_
