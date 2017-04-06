/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ���Ի���		                                        */
/* ʱ�䣺 2016-03-17                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IDRAWATTRIBUTE_H_
#define _PUBLICE_IDRAWATTRIBUTE_H_


namespace VR_Soft
{
	class IDrawAttribute : public IAttribute
	{
	public:
		// ��������
		virtual ~IDrawAttribute(void) { }
		// �����Ⱦ��
		virtual DrawObj* GetDrawObj(void) = 0;
		// �Ƿ������ƶ�
		virtual bool IsMove(void) const  = 0;
	};
}

#endif // ! _PUBLICE_IDRAWATTRIBUTE_H_