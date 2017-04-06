/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项实现类		                                        */
/* 时间： 2015-06-29                                                    */
/* 修改时间:                                                            */
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
		virtual ~CAttributeItem(void);

	public:
		// 设置值 
		virtual void SetValue(const VRVariant& var, bool bUI = true);
		// 设置值  防止直接传入待选项名称
		virtual void SetValue(const VRString& strCandidata);
		// 获得值并且采用STring类型表现
		virtual VRString GetValueToString(void) const;
		// 转换成osg::Vec3 类型表现
		virtual osg::Vec3 GetValueToVec3(void);
		// 转换成osg::Vec3 类型表现
		virtual osg::Vec3d GetValueToVec3d(void);
		// 转换成Int类型
		virtual int GetValueToInt(void) const;
		// 转换成Int类型
		virtual bool GetValueToBool(void) const;
		// 转换成float类型
		virtual float GetValueToFloat(void) const;
		// 转换成Double类型
		virtual double GetValueToDobule(void) const;
		// 添加待选项
		virtual void AddCandidatas(const VRString& strText, const VRVariant& value, bool bSelect = false) ;
		// 获得待选列表
		virtual const LstCandidatas& GetCandidatas(void) const ;
		// 获得可变参对象
		virtual VRVariant GetVariant(void) const;
		// 当前是否改变了属性值
		virtual bool IsChanged(void) const;
		// 获得当前选择的序号
		virtual int SelectCandidata(void) ;
		// 设置选择的序号
		virtual void SetSelect(const int index) ;
		// 保存到内存卡中
		virtual void WriteMemory(void) const;
		// 从内存中读取出来
		virtual void ReadFromMem(void);
		// 占用空间的大小
		virtual size_t GetSize(void) const;
		// 获得单位
		virtual const VRString& GetUntil(void) const;

	private:
		Candidatas m_curCanDidatas; // 当前的值
		mutable bool m_bChanged; // 改变值
		bool m_bAdded; // 添加到待选项中
		CCandidatasManager m_lstCandidata; // 候选列表
		const VRString m_strUntil; // 单位量

		VR_AUTO_MUTEX
	};
}



#endif // _ATTRIBUTEITEM_H_