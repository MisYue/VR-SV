/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ����			                                        */
/* ʱ�䣺 2016-03-30                                                    */
/* �޸�ʱ��:                                                            */
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

		// �ж�ָ���Ƿ���Ч
		bool Valid(void)
		{
			return (m_drawObj.valid());
		}

		// ������Ⱦ��
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
		// ��������
		virtual ~IMeshManager(void) { }
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(const VRString& strName) = 0;
		// ������е���Ⱦ��
		virtual const ListMeshObjs GetAllMeshObj(void) const  = 0;
	};
}

#endif // !_PUBLIC_MESHMANAGER_H_