/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ��������Խӿ���	                                        */
/* ʱ�䣺 2016-03-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLICE_IBASETTRIBUTE_H_
#define _PUBLICE_IBASETTRIBUTE_H_

namespace VR_Soft
{
	class IEntityID;

	class VRSOFT_DLL IEntityBaseAttribute : public IAttribute
	{
	public:
		// ����ϵͳ
		enum EntityCoordinate
		{
			MODEL, // ģ������ϵ
			EARTH, // ��������ϵ
			WORLD // ��������ϵ
		};

	public:
		// ��������
		virtual ~IEntityBaseAttribute(void) { }
		// ����ʵ������
		virtual void SetEntityName(const VRString& strName) = 0;
		// ���ʵ������
		virtual VRString GetEntityName(void) const = 0;
		// ����ID�� �ڲ�����
		virtual void SetEntityID(IEntityID* pEntityID) = 0;
		// ����ID��
		virtual void SetEntityID(const uint64_t uid) = 0;
		// ���ID��
		virtual uint64_t GetEntityID(void) const = 0;
		// ��������ϵ
		virtual void SetEntityCoordinate(const EntityCoordinate ec) = 0 ;
		// �������ϵ
		virtual EntityCoordinate GetEntityCoordinate(void) const = 0;
		// ��������
		virtual void SetEntityType(const VRString& strType ) = 0;
		// �������
		virtual VRString GetEntityType(void) const = 0;
	};
}

#endif // !_PUBLICE_IBASETTRIBUTE_H_