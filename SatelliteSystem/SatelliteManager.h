/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ����ģ�͹���													*/
/* ʱ�䣺 2015-11-20                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _SATELLITEMANAGER_H_
#define _SATELLITEMANAGER_H_

#pragma once

namespace VR_Soft
{
	class CSatelliteManager
	{
	public:
		explicit CSatelliteManager(void);
		virtual ~CSatelliteManager(void);

		void LoadAllElecDll(void);

	protected:
		// ��ǰ��̬���Ƿ������
		bool IsLoaded(const VRString& strElecName);
		// ���ص���dll�ļ�
		void LoadElecDll(const VRString& strElecName);
		// ж�ص���dll�ļ�
		void UnLoadElecDll(const VRString& strElecName);

	};

}

#endif