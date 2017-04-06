/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  实体渲染属性基类		                                        */
/* 时间： 2016-03-17                                                    */
/* 修改时间:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWATTRIBUTE_H_
#define _PUBLICE_IDRAWATTRIBUTE_H_


namespace VR_Soft
{
	class IDrawAttribute : public IAttribute
	{
	public:
		// 析构函数
		virtual ~IDrawAttribute(void) { }
		// 获得渲染体
		virtual DrawObj* GetDrawObj(void) = 0;
		// 是否随着移动
		virtual bool IsMove(void) const  = 0;
	};
}

#endif // ! _PUBLICE_IDRAWATTRIBUTE_H_