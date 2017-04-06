/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��̬���������		                                        */
/* ʱ�䣺 2015-05-13                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef DYLIBMANAGER_H
#define DYLIBMANAGER_H

#pragma once


namespace VR_Soft
{
	class CDyLib;

	class CDyLibManager : public CSingleton<CDyLibManager>
	{
	public:
		explicit CDyLibManager(void);
		virtual ~CDyLibManager(void);

	public:
		// �������
		CDyLib* Load(const VRString& fileName);
		// ж�����
		void Unload(CDyLib* pLib);

	private:
		typedef std::map<VRString, CDyLib*> MapStrLib;
		MapStrLib m_mapStrLib;
	};

}

#endif // DYLIBMANAGER_H
