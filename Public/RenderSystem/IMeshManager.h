/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染管理			                                        */
/* 时间： 2016-03-30                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLIC_MESHMANAGER_H_
#define _PUBLIC_MESHMANAGER_H_

#include <list>

namespace VR_Soft
{
	struct MeshObj
	{
		MeshObj(const VRString& strName, DrawObj* drawObj)
			:m_strName(strName), m_drawObj(drawObj)
		{

		}

		// 判断指针是否有效
		bool Valid(void)
		{
			return (m_drawObj.valid());
		}

		// 设置渲染体
		void SetDrawObj(DrawObj* pDrawObj)
		{
			m_drawObj = pDrawObj;
		}
		
		VRString m_strName;
		osg::ref_ptr<DrawObj> m_drawObj;
	};

	class OSGRENDER_DLL IMeshManager 
	{
	public:
		typedef std::list<MeshObj> ListMeshObjs;
	public:
		// 析构函数
		virtual ~IMeshManager(void) { }
		// 获得渲染体
		virtual DrawObj* GetDrawObj(const VRString& strName) = 0;
		// 获得所有的渲染体
		virtual const ListMeshObjs GetAllMeshObj(void) const  = 0;
	};
}

#endif // !_PUBLIC_MESHMANAGER_H_