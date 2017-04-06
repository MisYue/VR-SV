/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ����			                                        */
/* ʱ�䣺 2016-03-30                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _MESHMANAGER_H_
#define _MESHMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class CMeshManager : public CSingleton<CMeshManager>, public IMeshManager
	{
	public:
		CMeshManager(void);
		virtual ~CMeshManager(void);

	public:
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(const VRString& strName);
		// ������е���Ⱦ��
		virtual const ListMeshObjs GetAllMeshObj(void) const ;

	protected:
		// ��ʼ��
		void Init(void);
		// ��ȡ��������ֵ
		VRString GetValue(const VRString& strName);


	private:
		// IMeshManager::ListMeshObjs m_listMeshObjs;
		typedef boost::unordered_map<VRString, MeshObj> ListNameMeshObj;
		ListNameMeshObj m_listNameMeshObj;
	};

}

#endif // !_MESHMANAGER_H_