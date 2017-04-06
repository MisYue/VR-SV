/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  װ��ϵͳ������												*/
/* ʱ�䣺 2015-11-11                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _EQUIPPLUGIN_H_
#define _EQUIPPLUGIN_H_

#pragma once

namespace VR_Soft
{
	class CEquipPlgin : public IPlugin
	{
	public:
		explicit CEquipPlgin(void);
		virtual ~CEquipPlgin(void);

	public:
		// ��ȡ�������
		virtual const VRString& GetPluginName(void) const;
		// ��ò���汾
		virtual const VRString GetPluginVersion(void) const ;
		// ��ò������
		virtual const VRString& GetPluginDiscribe(void) const;
		// ��װ���
		virtual void Install(void) ;
		// ��ʼ�����
		virtual void Initialise(void);
		// ������
		virtual void Shutdown(void);
		// ж�ز��
		virtual void UnInstall(void);

	private:
		IComFactory* m_pIComFactory; // �������
	};

	// ע����
	//REGISTER_VRSOFT_PLUGIN(CEquipPlgin);
	REGISTER_VRSOFT_PLUGIN(CEquipPlgin, EQUIP_DLL)
}


#endif // !_EQUIPPLUGIN_H_