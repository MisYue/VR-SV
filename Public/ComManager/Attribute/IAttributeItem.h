/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项接口		                                        */
/* 时间： 2015-06-12                                                    */
/* 修改时间:                                                            */
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
		CTRL_EDIT,			// 文本框
		CTRL_SPINBOX,		// 浮点框
		CTRL_BUTTON,		// 按钮
		CTRL_COMBOX,		// 组合框
		CTRL_TREE,			// 树形框
		CTRL_TRATEGY,		// 策略框
		CTRL_FILE_SELECT,	// 单个文本选择控件
		CTRL_ITEM_SELECT,	// 单个项选择控件
		CTRL_COLOR			// 颜色控件

	}Contrl;


	class VRSOFT_DLL IAttributeItem
	{
	public:
		// 析构函数
		virtual ~IAttributeItem(void) {}
		// 获得属性接口对象
		virtual IProperty* GetProperty(void) = 0;
		// 获得属性名称
		virtual VRString GetTypeName(void) const = 0;
		// 获得用于显示的控件类型
		virtual Contrl GetCtrlType(void) const = 0;
		// 获得值并且采用STring类型表现
		virtual VRString GetValueToString(void) const = 0;
		// 转换成osg::Vec3 类型表现
		virtual osg::Vec3 GetValueToVec3(void) const= 0;
		// 转换成osg::Vec3 类型表现
		virtual osg::Vec3d GetValueToVec3d(void) const = 0;
		// 转换成osg::Vec4 类型表现
		virtual osg::Vec4 GetValueToVec4(void) const = 0;
		// 转换成osg::Vec4 类型表现
		virtual osg::Vec4d GetValueToVec4d(void) const = 0;
		// 转换成Int类型
		virtual int GetValueToInt(void) const = 0;
		// 转换成float类型
		virtual float GetValueToFloat(void) const = 0;
		// 设置值 通过设置字符串
		virtual void SetValue(const VRVariant& var, bool bUI = true) = 0;
		// 转换成Int类型
		virtual bool GetValueToBool(void) const = 0;
		// 转换成Double类型
		virtual double GetValueToDobule(void) const = 0;
		// 获得待选列表
		virtual  std::vector<VRString> GetCandidatas(void) const = 0;
		// 获得可变参对象
		virtual VRVariant GetVariant(void) const = 0;
		// 当前属性值是否有变更
		virtual bool IsChanged(void) const = 0;
		// 获得当前选择的序号
		virtual int SelectCandidata(void) = 0;
		// 设置选择的序号
		virtual void SetSelect(const int index) = 0;
		// 保存到内存卡中
		virtual void WriteMemory(void) const = 0;
		// 占用空间的大小
		virtual size_t GetSize(void) const = 0;
		// 获得单位
		virtual const VRString& GetUntil(void) const = 0;
	};

	template<class T>
	bool CanvartType(const IAttributeItem* pAttributeItem, T& var) 
	{
		// 获得类型
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