/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  路径策略				                                        */
/* 时间： 2015-12-01                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IPATHSTRATEGY_H_
#define _PUBLIC_IPATHSTRATEGY_H_

namespace VR_Soft
{
	class VRSOFT_DLL IPathStrategy
	{
	public:
		// 析构函数
		virtual ~IPathStrategy(void) { }
		// 计算通过关键点计算路径
		virtual std::vector<osg::Vec3d> ComputePath(const std::vector<osg::Vec3d>& listKeyPoints) = 0;
	};
}

#endif // !_PUBLIC_IPATHSTRATEGY_H_
