/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ���ӿ�														*/
/* ʱ�䣺 2015-11-24                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENVIRONMENT_H_
#define _PUBLIC_IENVIRONMENT_H_

namespace VR_Soft
{
	class IEnvironment : public CEntityBaseImp<IEntityRenderBase>
	{
	public:
		// ��������
		virtual ~IEnvironment(void) { }
	};

	// �����״���󹤳�
	CREATE_ENTITYBASE_FACTORY(CreateEnvironmentFactory);
}

#endif // !_PUBLIC_IENVIRONMENT_H_