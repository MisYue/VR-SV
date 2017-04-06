/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体文件操作类		                                        */
/* 时间： 2016-06-18                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _ENTITYFILEOPERATOR_H_
#define _ENTITYFILEOPERATOR_H_

#pragma once

namespace VR_Soft
{
	class CEntityFile
	{
	public:
		// 构造函数
		CEntityFile(const VRString& strPath);
		// 析构函数
		~CEntityFile(void);

	public:
		// 从文件夹中加载
		bool Parse(void);
		// 获得名称
		VRString GetType(void) const;
		// 获得名称
		VRString GetName(void) const;
		// 获得所有的属性
		ListString GetAllAttribute(void) const;
		// 获得属性节点
		TiXmlElement* GetXmlElement(const VRString& strAttribute) const;
		// 创建实体
		IEntityBase* CreateEntity( const VRString& strName, const uint64_t ID );

	protected:
		// 判断是否为xml
		bool IsVaild(void);

		// 解析文件 实体基本信息
		void ParseBaseInfo(const TiXmlElement* pElement);
		// 解析属性
		void ParseAttribute(TiXmlElement* pElement);

	protected:
		// 创建属性
		void CreateAttribute(IEntityBase* pIEntity);

	protected:
		typedef boost::unordered_map<VRString, TiXmlElement*> ListAttributes;

	private:
		VRString m_strPath;
		VRString m_strType; // 类型
		VRString m_strName; // 名称
		TiXmlDocument* m_pXmlDocument; // xml文件
		ListAttributes m_listAttributes; // 属性列表
	};
}


#endif // !_ENTITYFILEOPERATOR_H_