/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������ӿ�		                                        */
/* ʱ�䣺 2015-06-12                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLICE_IATTRIBUTEITEM_H_
#define _PUBLICE_IATTRIBUTEITEM_H_

#include <list>
#include <osg/Vec3>
#include <osg/Vec3d>
#include <osg/Vec4>
#include <osg/Vec4d>

namespace VR_Soft
{
	class IAttributeItemUI;
	typedef enum _Typ
	{
		CTRL_EDIT,			// �ı���
		CTRL_SPINBOX,		// �����
		CTRL_BUTTON,		// ��ť
		CTRL_COMBOX,		// ��Ͽ�
		CTRL_TREE,			// ���ο�
		CTRL_TRATEGY,		// ���Կ�
		CTRL_FILE_SELECT,	// �����ı�ѡ��ؼ�
		CTRL_ITEM_SELECT,	// ������ѡ��ؼ�
		CTRL_COLOR			// ��ɫ�ؼ�

	}Contrl;


	class VRSOFT_DLL IAttributeItem
	{
	public:
		// ��������
		virtual ~IAttributeItem(void) {}
		// ������Խӿڶ���
		virtual IProperty* GetProperty(void) = 0;
		// �����������
		virtual VRString GetTypeName(void) const = 0;
		// ���������ʾ�Ŀؼ�����
		virtual Contrl GetCtrlType(void) const = 0;
		// ���ֵ���Ҳ���STring���ͱ���
		virtual VRString GetValueToString(void) const = 0;
		// ת����osg::Vec3 ���ͱ���
		virtual osg::Vec3 GetValueToVec3(void) const= 0;
		// ת����osg::Vec3 ���ͱ���
		virtual osg::Vec3d GetValueToVec3d(void) const = 0;
		// ת����osg::Vec4 ���ͱ���
		virtual osg::Vec4 GetValueToVec4(void) const = 0;
		// ת����osg::Vec4 ���ͱ���
		virtual osg::Vec4d GetValueToVec4d(void) const = 0;
		// ת����Int����
		virtual int GetValueToInt(void) const = 0;
		// ת����float����
		virtual float GetValueToFloat(void) const = 0;
		// ����ֵ ͨ�������ַ���
		virtual void SetValue(const VRVariant& var, bool bUI = true) = 0;
		// ת����Int����
		virtual bool GetValueToBool(void) const = 0;
		// ת����Double����
		virtual double GetValueToDobule(void) const = 0;
		// ��ô�ѡ�б�
		virtual  std::vector<VRString> GetCandidatas(void) const = 0;
		// ��ÿɱ�ζ���
		virtual VRVariant GetVariant(void) const = 0;
		// ��ǰ����ֵ�Ƿ��б��
		virtual bool IsChanged(void) const = 0;
		// ��õ�ǰѡ������
		virtual int SelectCandidata(void) = 0;
		// ����ѡ������
		virtual void SetSelect(const int index) = 0;
		// ���浽�ڴ濨��
		virtual void WriteMemory(void) const = 0;
		// ռ�ÿռ�Ĵ�С
		virtual size_t GetSize(void) const = 0;
		// ��õ�λ
		virtual const VRString& GetUntil(void) const = 0;
	};

	template<class T>
	bool CanvartType(const IAttributeItem* pAttributeItem, T& var) 
	{
		// �������
		try
		{
			var = boost::any_cast<T>(pAttributeItem->GetVariant());

		}
		catch (const boost::bad_any_cast )
		{
			return (false);
		}

		return (true);
	}

}

#endif // _PUBLICE_IATTRIBUTEITEM_H_