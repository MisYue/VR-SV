/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ·������ӿ�ͷ�ļ�	                                        */
/* ʱ�䣺 2016-06-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPATHMANAGER_H_
#define _PUBLIC_IPATHMANAGER_H_

namespace VR_Soft
{
	class VRSOFT_DLL IPathManager : public CSingleton<IPathManager>
	{
	public:
		// ��������
		virtual ~IPathManager(void) { }
		// ���·��
		virtual IPath* Create(const uint64_t uID, const VRString& strName, IFeatureGeomtry* pIFeatureGeomtry, IPathStrategy* pIPathStragey = NULL) = 0;
		// �Ƴ�·��
		virtual void Remove(const uint64_t uID) = 0;
		// ��ѯ·��
		virtual IPath* GetPath(const uint64_t uID) const = 0;
		// ��ѯ·��ͨ������
		virtual std::vector<IPath*> GetPath(const VRString& strName) const = 0;
		// �������·��
		virtual std::vector<IPath*> GetAllPath(void) const = 0;
	};
}

#endif // !_PUBLIC_IPATHMANAGER_H_