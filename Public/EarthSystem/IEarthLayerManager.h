/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  osgEarth接口		                                            */
/* 时间： 2016-07-28                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IEARTHLAYERMANAGER_H_
#define _PUBLIC_IEARTHLAYERMANAGER_H_

namespace VR_Soft
{
	enum LayerType
	{
		IMAGET_TYPE, // 影像图层
		ELEVATION_TYPE, // 高程图层
		FEARTRUE_TYPE // 适量图层
	};

	class OSGEARTH_DLL IEarthLayer
	{
	public:
		virtual ~IEarthLayer() { }
		// 设置图层名称
		virtual void SetLayerName(const VRString& strLayerName) = 0;
		// 获得图层名称
		virtual VRString GetLayerName(void) const = 0;
		// 获得图层路径
		virtual VRString GetLayerPath(void) const = 0;
		// 设置图层透明度
		virtual void SetOpacity(float fOpacity) = 0;
		// 获得透明度
		virtual float GetOpacity(void) const = 0;
		// 设置显示状态
		virtual void SetVisible(bool bValue) = 0;
		// 获得显示状态
		virtual bool GetVisible(void) const = 0;
		// 获得图层类型
		virtual LayerType GetLayerType(void) const = 0;
	};

//////////////////////////////////////////////////////////////////////////
	class OSGEARTH_DLL IEarthLayerManager
	{
	public:
		typedef std::vector<IEarthLayer*> ListEarthLayers;

	public:
		// 析构函数
		virtual ~IEarthLayerManager(void) { }
		// 创建图层
		virtual IEarthLayer* CreateEarthLayer(const VRString& strLayerPath, LayerType lt) = 0;
		// 查找图层
		virtual ListEarthLayers FindEarthLayer(const VRString& strEarthLayerName) const = 0;
		// 查找图层
		virtual IEarthLayer* FindEarthLayer(const int ID) const = 0;
		// 删除图层
		virtual void RemoveEarthLayer(const int ID) = 0;
		// 删除图层
		virtual void RemoveEarthLayer(IEarthLayer* pIEarthLayer) = 0;
		// 获得所有的图层
		virtual ListEarthLayers GetAllLayer(void) = 0;
	};
}

#endif //! _PUBLIC_IEARTHLAYERMANAGER_H_