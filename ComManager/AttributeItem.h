/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������ʵ����		                                        */
/* ʱ�䣺 2015-06-29                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _ATTRIBUTEITEM_H_
#define _ATTRIBUTEITEM_H_

#pragma once

#include "CandidatasManager.h"

namespace VR_Soft
{
	class CAttributeItem : public CAttributeItemImp<IAttributeItem>
	{
	public:
		explicit CAttributeItem(IAttribute* pIAttribute,const VRString& strText, const VRString& strUntil, const VRVariant& var);
		explicit CAttributeItem(IAttribute* pIAttribute,const VRString& strText, const VRString& strUntil, IProperty* pProperty);
		virtual ~CAttributeItem(void);

	public:
		// ������Խӿڶ���
		virtual IProperty* GetProperty(void);
		// ����ֵ 
		virtual void SetValue(const VRVariant& var, bool bUI = true);
		// ����ֵ  ��ֱֹ�Ӵ����ѡ������
		virtual void SetValue(const VRString& strCandidata);
		// ���ֵ���Ҳ���STring���ͱ���
		virtual VRString GetValueToString(void) const;
		// ת����osg::Vec3 ���ͱ���
		virtual osg::Vec3 GetValueToVec3(void) const;
		// ת����osg::Vec3 ���ͱ���
		virtual osg::Vec3d GetValueToVec3d(void) const;
		// ת����osg::Vec4 ���ͱ���
		virtual osg::Vec4 GetValueToVec4(void) const;
		// ת����osg::Vec4 ���ͱ���
		virtual osg::Vec4d GetValueToVec4d(void) const;
		// ת����Int����
		virtual int GetValueToInt(void) const;
		// ת����Int����
		virtual bool GetValueToBool(void) const;
		// ת����float����
		virtual float GetValueToFloat(void) const;
		// ת����Double����
		virtual double GetValueToDobule(void) const;
		// ��ô�ѡ�б�
		virtual std::vector<VRString> GetCandidatas(void) const ;
		// ��ÿɱ�ζ���
		virtual VRVariant GetVariant(void) const;
		// ��ǰ�Ƿ�ı�������ֵ
		virtual bool IsChanged(void) const;
		// ��õ�ǰѡ������
		virtual int SelectCandidata(void) ;
		// ����ѡ������
		virtual void SetSelect(const int index) ;
		// ���浽�ڴ濨��
		virtual void WriteMemory(void) const;
		// ���ڴ��ж�ȡ����
		virtual void ReadFromMem(void);
		// ռ�ÿռ�Ĵ�С
		virtual size_t GetSize(void) const;
		// ��õ�λ
		virtual const VRString& GetUntil(void) const;

	private:
		mutable bool m_bChanged; // �ı�ֵ
		bool m_bAdded; // ��ӵ���ѡ����
//		CCandidatasManager m_lstCandidata; // ��ѡ�б�
		const VRString m_strUntil; // ��λ��
		IProperty* m_pProperty; // ����ָ��

		VR_AUTO_MUTEX
	};
}



#endif // _ATTRIBUTEITEM_H_