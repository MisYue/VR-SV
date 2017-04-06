/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ͼ����� ����23Dͼ��ͬ������								*/
/* ʱ�䣺 2015-05-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _EARTHLAYERMANAGER_H_
#define _EARTHLAYERMANAGER_H_

#pragma once

#include <osgEarth/Map>
#include <osgEarthUtil/GraticuleNode>
#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	// ����ͼ��
	class CEarthLayer : public IEarthLayer
	{
	public: 
		// ���캯��
		CEarthLayer(osgEarth::Layer* pLayer, LayerType lt);
		// ��������
		virtual ~CEarthLayer(void);

	public:
		// ����ͼ������
		virtual void SetLayerName(const VRString& strLayerName);
		// ���ͼ������
		virtual VRString GetLayerName(void) const ;
		// ���ͼ��·��
		virtual VRString GetLayerPath(void) const ;
		// ����ͼ��͸����
		virtual void SetOpacity(float fOpacity) ;
		// ���͸����
		virtual float GetOpacity(void) const;
		// ������ʾ״̬
		virtual void SetVisible(bool bValue) ;
		// �����ʾ״̬
		virtual bool GetVisible(void) const ;
		// ���ͼ������
		virtual LayerType GetLayerType(void) const ;

	public:
		osgEarth::Layer* GetLayer(void) { return (m_pLayer); }

	private:
		osgEarth::Layer* m_pLayer; // ͼ��ָ��
		LayerType m_lt; // ����
		VRString m_strName; // ͼ������
	};


	//////////////////////////////////////////////////////////////////////////
	class CEarthLayerManager : public IEarthLayerManager
	{
	public:
		// ���캯��
		CEarthLayerManager(void);
		// ��������
		virtual ~CEarthLayerManager(void);

	public: 
		// ����ͼ��
		virtual IEarthLayer* CreateEarthLayer(const VRString& strLayerPath, LayerType lt);
		// ����ͼ��
		virtual ListEarthLayers FindEarthLayer(const VRString& strEarthLayerName) const ;
		// ����ͼ��
		virtual IEarthLayer* FindEarthLayer(const int ID) const ;
		// ɾ��ͼ��
		virtual void RemoveEarthLayer(const int ID) ;
		// ɾ��ͼ��
		virtual void RemoveEarthLayer(IEarthLayer* pIEarthLayer) ;
		// ������е�ͼ��
		virtual ListEarthLayers GetAllLayer(void) ;

	public:
		// ������ά��ͼ
		void SetEarthMap2D(osgEarth::MapNode* pMapNode);
		// ������ά��ͼ
		void SetEarthMap3D(osgEarth::MapNode* pMapNode);
		// ���Ӱ��ͼ��
		void AddImageLayer(osgEarth::ImageLayer* pImageLayer);
		// �Ƴ�Ӱ��ͼ��
		void RemoveImagerLayer(osgEarth::ImageLayer* imageLayer);
		// ��Ӹ߳�ͼ��
		void AddElevationLayer(osgEarth::ElevationLayer* pElevationLayer);
		// �Ƴ��߳�ͼ��
		void RemoveElevationLayer(osgEarth::ElevationLayer* pElevationLayer);
		// ���ģ��ͼ��
		void AddModelLayer(osgEarth::ModelLayer* pModelLayer);
		// �Ƴ�ģ��ͼ��
		void RemoveModelLayer( osgEarth::ModelLayer* pModelLayer );

	protected:
		// ���Ӱ��ͼ��
		void AddImageLayer(osgEarth::Map* pMap, osgEarth::ImageLayer* pImageLayer);
		// �Ƴ�Ӱ��ͼ��
		void RemoveImagerLayer(osgEarth::Map* pMap, osgEarth::ImageLayer* pImageLayer);
		// ��Ӹ߳�ͼ��
		void AddElevationLayer(osgEarth::Map* pMap, osgEarth::ElevationLayer* pElevationLayer);
		// �Ƴ��߳�ͼ��
		void RemoveElevationLayer(osgEarth::Map* pMap, osgEarth::ElevationLayer* pElevationLayer);
		// ���ͼ�����
		void AddEarthLayer( const int ID, CEarthLayer* pEarthLayer );
		
	private:
		osgEarth::Map* m_pEarthMap2D;
		osgEarth::Map* m_pEarthMap3D;
		//osgEarth::Util::GraticuleNode* m_pGraticuleNode;
		typedef boost::unordered_map<int, IEarthLayer*> ListIDEarthLayers;
		ListIDEarthLayers m_listIDEarthLayers;
	};

}

#endif // !_EARTHLAYERMANAGER_H_