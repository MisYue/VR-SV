/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体属性基类			                                        */
/* 时间： 2015-06-02                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _IATTRIBUT_H_
#define _IATTRIBUT_H_

#include <list>

namespace VR_Soft
{
	class IEntityBase;
	class IAttributeItem;

	class VRSOFT_DLL IAttribute
	{
	public:
		typedef std::vector<IAttributeItem* > ListAttrItems;

	public:
		// 析构函数
		virtual ~IAttribute() { }
		// 初始化属性
		virtual void Init(void) = 0;
		// 获得模型对象
		virtual IEntityBase* GetEntity(void) const = 0;
		// 获得名称
		virtual const VRString& GetName(void) const = 0;
		// 设置名称
		virtual void SetName(const VRString& strName) = 0;
		// 获得属性列表
		virtual ListAttrItems GetAttrItems(void) const = 0;
		// 通过属性的名称获取属性项
		virtual IAttributeItem* GetItem(const VRString& strName) const = 0;
		// 设置属性
		virtual void AddAttrItem(IAttributeItem* pIItem) = 0;
		// 更新
		virtual void Update(void) = 0;
		// 读取XML文件
		virtual void ReadXmlNode(TiXmlElement* pTiXmlElement) = 0;
		// 保存XML节点
		virtual void SaveXmlNode(TiXmlElement* pTiXmlElement) const = 0;
	};
}

#endif // _IATTRIBUT_H_