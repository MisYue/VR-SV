/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  osgEarth�ӿ�		                                            */
/* ʱ�䣺 2016-07-28                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IEARTHLAYERMANAGER_H_
#define _PUBLIC_IEARTHLAYERMANAGER_H_

namespace VR_Soft
{
	enum LayerType
	{
		IMAGET_TYPE, // Ӱ��ͼ��
		ELEVATION_TYPE, // �߳�ͼ��
		FEARTRUE_TYPE // ����ͼ��
	};

	class OSGEARTH_DLL IEarthLayer
	{
	public:
		virtual ~IEarthLayer() { }
		// ����ͼ������
		virtual void SetLayerName(const VRString& strLayerName) = 0;
		// ���ͼ������
		virtual VRString GetLayerName(void) const = 0;
		// ���ͼ��·��
		virtual VRString GetLayerPath(void) const = 0;
		// ����ͼ��͸����
		virtual void SetOpacity(float fOpacity) = 0;
		// ���͸����
		virtual float GetOpacity(void) const = 0;
		// ������ʾ״̬
		virtual void SetVisible(bool bValue) = 0;
		// �����ʾ״̬
		virtual bool GetVisible(void) const = 0;
		// ���ͼ������
		virtual LayerType GetLayerType(void) const = 0;
	};

//////////////////////////////////////////////////////////////////////////
	class OSGEARTH_DLL IEarthLayerManager
	{
	public:
		typedef std::vector<IEarthLayer*> ListEarthLayers;

	public:
		// ��������
		virtual ~IEarthLayerManager(void) { }
		// ����ͼ��
		virtual IEarthLayer* CreateEarthLayer(const VRString& strLayerPath, LayerType lt) = 0;
		// ����ͼ��
		virtual ListEarthLayers FindEarthLayer(const VRString& strEarthLayerName) const = 0;
		// ����ͼ��
		virtual IEarthLayer* FindEarthLayer(const int ID) const = 0;
		// ɾ��ͼ��
		virtual void RemoveEarthLayer(const int ID) = 0;
		// ɾ��ͼ��
		virtual void RemoveEarthLayer(IEarthLayer* pIEarthLayer) = 0;
		// ������е�ͼ��
		virtual ListEarthLayers GetAllLayer(void) = 0;
	};
}

#endif //! _PUBLIC_IEARTHLAYERMANAGER_H_