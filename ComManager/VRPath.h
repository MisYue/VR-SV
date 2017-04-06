/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ·���ؼ������		                                        */
/* ʱ�䣺 2016-07-06                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _VRPATH_H_
#define _VRPATH_H_

#pragma once

namespace VR_Soft
{
	class CVRPath : public IPath
	{
	public:
		// ���캯��
		CVRPath(const uint64_t ID, const VRString& strName);
		// ��������
		virtual ~CVRPath(void);

	public:
		// ���ID
		virtual uint64_t GetID(void) const;
		// ��������
		virtual void SetName(const VRString& strName) ;
		// �������
		virtual VRString GetName(void) const ;
		// ���һ�������������
		virtual void AddKeyPoint(const osg::Vec3d& vPos) ;
		// �Ƴ�һ����
		virtual void RemoveKeyPoint(const int index) ;
		// ���ĵ�
		virtual void ChangeKeyPoint(const int index, const osg::Vec3d& vPos);
		// ���ĳһ���ؼ���
		virtual osg::Vec3d GetKeyPoint(int index) const ;
		// ���·���ؼ���
		virtual const ListPoints& GetKeyPoints(void) const;
		// ���·����
		virtual const ListPoints& GetPathPoints(void) const;
		// ���ָ��·����
		virtual osg::Vec3d GetPathPoint(const int index) const ;
		// ����·������
		virtual void SetPathStrategy(const IPathStrategy* pIPathStratey);
		// ���·������
		virtual IPathStrategy* GetPathStrtegy(void) const ;
		// ������Ⱦ
		virtual void SetFeatureGeomtry(const IFeatureGeomtry* pIFeatureGeomtry) ;
		// �����Ⱦ
		virtual IFeatureGeomtry* GetFeatureGeomtry(void) const ;

	protected:
		// ��ֵ����
		void InterPolate( void );
	private:
		uint64_t m_ID;
		VRString m_strName; // ����
		IPathStrategy* m_pIPathStrategy; // ·������
		IFeatureGeomtry* m_pIFeatureGeomtry; // ��ʾ·��
		ListPoints m_listKeyPoints; // �ؼ���λ��
		ListPoints m_listPathPoints; // �ؼ���λ��
	};
}


#endif // !_VRPATH_H_