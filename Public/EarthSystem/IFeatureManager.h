/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʸ�����ݹ�����ӿ�                                            */
/* ʱ�䣺 2016-09-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_FEATUREMANAGER_H_
#define _PUBLIC_FEATUREMANAGER_H_

namespace VR_Soft
{
	class IFeatureManager 
	{
	public:
		// ��������
		virtual ~IFeatureManager(void) { }

		// ���ʸ������
		virtual bool AddFeature(IFeature* pIFearth) = 0;
		// �Ƴ�ʸ������
		virtual void RemoveFeature(unsigned long ID) = 0;
		// ��ѯID
		virtual IFeature* GetFeature(unsigned long ID) const = 0;
		// ��õ�ǰ��ѡ���ʸ��
		virtual IFeature* GetCurFeature(void) const = 0;
	};
}

#endif // !_PUBLIC_FEATUREMANAGER_H_