/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ·��������ͷ�ļ�		                                        */
/* ʱ�䣺 2016-06-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PATHMANAGER_H_
#define _PATHMANAGER_H_

#pragma once

#include <boost/unordered_map.hpp>

namespace VR_Soft
{
	class CPathManager : public IPathManager
	{
	public:
		// ���캯��
		CPathManager(void);
		// ��������
		virtual ~CPathManager(void);

	public:
		// ���·��
		virtual IPath* Create(const uint64_t uID, const VRString& strName, IFeatureGeomtry* pIFeatureGeomtry, IPathStrategy* pIPathStragey = NULL) ;
		// �Ƴ�·��
		virtual void Remove(const uint64_t uID) ;
		// ��ѯ·��
		virtual IPath* GetPath(const uint64_t uID) const ;
		// ��ѯ·��ͨ������
		virtual std::vector<IPath*> GetPath(const VRString& strName) const ;
		// �������·��
		virtual std::vector<IPath*> GetAllPath(void) const;

	protected:
		// hash �洢·��
		typedef boost::unordered_map<const uint64_t, IPath*> ListIDPath;

		// �Ƴ����е�
		void RemoveAll(void);

	private:
		ListIDPath m_listIDPath; // ·������
	};
}


#endif // !_PATHMANAGER_H_