/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  地球几何体头文件		                                        */
/* 时间： 2016-07-14                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IFEATUREGEOMTRY_H_
#define _PUBLIC_IFEATUREGEOMTRY_H_

namespace VR_Soft
{
	class VRSOFT_DLL IFeatureGeomtry
	{
	public: 
		// 贴地技术
		enum Technique
		{
			TECHNIQUE_MAP,
			TECHNIQUE_SCENE,
			TECHNIQUE_GPU,
			TECHNIQUE_DRAPE
		};

		// 控制模型嵌入
		enum Clamping
		{
			CLAMP_NONE,
			CLAMP_TO_TERRAIN,
			CLAMP_RELATIVE_TO_TERRAIN,
			CLAMP_ABSOLUTE
		};

	public:
		// 析构函数
		virtual ~IFeatureGeomtry(void) { }
		// 设置颜色
		virtual void SetColor(const osg::Vec4& vColor) = 0;
		// 获得颜色
		virtual osg::Vec4 GetColor(void) const = 0;
		// 设置线宽
		virtual void SetWidth(const float fWidth) = 0;
		// 获得线宽
		virtual float GetWidth(void) const = 0;
		// 设置贴地技术
		virtual void SetTechnique(const Technique technique) = 0;
		// 获得贴地技术
		virtual Technique GetTechnique(void) const = 0;
		// 设置高程
		virtual void SetClamping(const Clamping clamping) = 0;
		// 获得模型嵌入
		virtual  Clamping GetClamping(void) const = 0;
		// 获得所有点
		virtual std::vector<osg::Vec3d> GetAllPoints(void) const = 0;
		// 设置所有点
		virtual void SetAllPoints(const std::vector<osg::Vec3d>& listPoints) = 0;
		// 获得索引点
		virtual osg::Vec3d GetPoint(const int index) = 0;
		// 设置点
		virtual void SetPoint(const int index, const osg::Vec3d& vPoint) = 0;
		// 移除点
		virtual void Remove(const int index) = 0;
		// 移除所有的点
		virtual void RemoveAll(void) = 0;
		// 设置2D地图
		virtual void SetMapNode2D(EarthMap* pEarthMap) = 0;
		// 设置3D地图
		virtual void SetMapNode3D(EarthMap* pEarthMap) = 0;
		// 获得渲染节点
		virtual DrawObj* GetDrawObj2D(void) const = 0;
		// 获得渲染节点
		virtual DrawObj* GetDrawObj3D(void) const = 0;
	};
}

#endif // !_PUBLIC_IFEATUREGEOMTRY_H_