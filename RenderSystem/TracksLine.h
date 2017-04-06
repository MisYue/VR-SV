/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  航迹线实现类			                                        */
/* 时间： 2015-05-27                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _TRACKSLINE_H_
#define _TRACKSLINE_H_

#pragma once

#include <osg/LineWidth>
#include <osg/Geode>
#include <osg/Geometry>

namespace VR_Soft
{
	class CTracksLine : public CAttributeImp<IDrawAttribute>
	{
	public:
		// 构造函数
		explicit CTracksLine(IEntityBase* pIEntityBase); 
		// 析构函数
		virtual ~CTracksLine(void);

	public:
		// 初始化
		virtual void Init();
		// 更新
		virtual void Update(void);
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void);
		// 是否随着移动
		virtual bool IsMove(void) const ;

	public:
		// 设置是否隐藏
		void SetShow(bool bShow) ;
		// 获得是否隐藏
		bool GetShow(void) const;
		// 设置线宽
		void SetLineWidth(int nWidth);
		// 获得线宽
		int GetLineWidth(void) const;
		// 是否打开光照
		void SetLightOn(bool bOn);
		// 获得光照状态
		bool IsOpenLight(void) const;

	public:
		// 属性
		//AutoProperty(osg::Vec3d, Postion);
		DECLARE_PROPERTY(CTracksLine, bool, Show);
		DECLARE_PROPERTY(CTracksLine, int, LineWidth);
		DECLARE_PROPERTY(CTracksLine, bool, Light);


	protected:
		// 添加点数到渲染体中
		void AddPoint(const osg::Vec3f& vWorld);
		// 更新渲染体
		void UpdateGeomerty(void);

	private:
		osg::Geode* m_pGeode; // 渲染节点
		osg::Geometry* m_pGeomerty; // 渲染体

		int m_nMaxCount; // 渲染体中最大点数
		bool m_bShow; // 是否显示
		int n_nCurrent; // 当前属性
		osg::LineWidth* m_pLineWidth; // 线宽
		bool m_bOpenLight; // 是否打开光照
	};
}


#endif // !_TRACKSLINE_H_