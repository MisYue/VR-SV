/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  渲染几何体工厂接口											*/
/* 时间： 2016-07-05                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _FEATUREGEOMTRY_H_
#define _FEATUREGEOMTRY_H_

#include <osgEarthSymbology/Style>
#include <osgEarthSymbology/Geometry>
#include <osgEarthAnnotation/FeatureNode>

namespace VR_Soft
{
	class CFeatureGeomtry : public IFeatureGeomtry
	{
	public:
		// 构造函数
		explicit CFeatureGeomtry(OsgEarthGeomtry* pOsgEarthGeomtry);
		// 析构函数
		virtual ~CFeatureGeomtry(void);

	public:
		// 设置颜色
		virtual void SetColor(const osg::Vec4& vColor);
		// 获得颜色
		virtual osg::Vec4 GetColor(void) const;
		// 设置线宽
		virtual void SetWidth(const float fWidth);
		// 获得线宽
		virtual float GetWidth(void) const ;
		// 设置贴地技术
		virtual void SetTechnique(const Technique technique) ;
		// 获得贴地技术
		virtual Technique GetTechnique(void) const;
		// 设置高程
		virtual void SetClamping(const Clamping clamping) ;
		// 获得模型嵌入
		virtual  Clamping GetClamping(void) const ;
		// 获得所有点
		virtual std::vector<osg::Vec3d> GetAllPoints(void) const ;
		// 设置所有点
		virtual void SetAllPoints(const std::vector<osg::Vec3d>& listPoints);
		// 获得索引点
		virtual osg::Vec3d GetPoint(const int index) ;
		// 设置点
		virtual void SetPoint(const int index, const osg::Vec3d& vPoint) ;
		// 移除点
		virtual void Remove(const int index) ;
		// 移除所有的点
		virtual void RemoveAll(void) ;
		// 设置2D地图
		virtual void SetMapNode2D(EarthMap* pEarthMap) ;
		// 设置3D地图
		virtual void SetMapNode3D(EarthMap* pEarthMap) ;
		// 获得渲染节点
		virtual DrawObj* GetDrawObj2D(void) const ;
		// 获得渲染节点
		virtual DrawObj* GetDrawObj3D(void) const ;
		// 设置渲染体
		void SetGeomtry( osgEarth::Symbology::Geometry* pGeomtry );
		// 更新集合体
		void UpdateDrawable(void);
	private:
		osgEarth::Symbology::Style m_style;  // 3D线条样式
		osgEarth::Symbology::Style m_style2D; // 2D线条样式
		osgEarth::Symbology::Geometry* m_pGeomety; // 几何体

		osgEarth::Annotation::FeatureNode* m_pFeatureNode2D; // 3D绘制
		osgEarth::Annotation::FeatureNode* m_pFeatureNode3D; // 2D绘制

		osg::Vec4 m_vColor; // 颜色
		float m_fWidth; // 线宽
		Technique m_tchnique;
		Clamping m_clamping;

	};
}

#endif // !_FEATUREGEOMTRY_H_