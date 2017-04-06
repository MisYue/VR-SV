/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性项接口		                                        */
/* 时间： 2015-09-08                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _CANDIDATASMANAGER_H_
#define _CANDIDATASMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CCandidatasManager
	{
	public:
		explicit CCandidatasManager(void);
		~CCandidatasManager(void);

		// 添加待选项
		void Add(const Candidatas& candidata);
		// 移除带选项
		void Remove(VRString& strName);
		// 是否为空
		bool Empty(void) const ;
		// 根据名称获得值
		Candidatas GetCandidata(const VRString& strName, bool& b);
		// 获取所有的值
		const IAttributeItem::LstCandidatas& GetCandidatas(void) const;
		// 获得当前选择的序号
		int SelectCandidata(void) const;
		// 设置选择的序号
		void SetSelect(const int index);
		// 获得可变参对象
		VRVariant GetVariant(void) const;

	protected:
		// 当前是已经有相同的名称
		bool IsHave(const VRString& strName);
		// 当前是已经有相同的名称
		bool IsHave(const Candidatas& candidata);

	private:
		IAttributeItem::LstCandidatas m_lstCandidatas; // 当前选项列表

	};
}


#endif // _CANDIDATASMANAGER_H_