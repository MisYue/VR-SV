/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ת��������			                                        */
/* ʱ�䣺 2015-05-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _CONVERT_H_
#define _CONVERT_H_

#pragma once

namespace osgEarth
{
	class SpatialReference;
}

namespace VR_Soft
{
	class IAttributeItem;

	const double WGS_84_RADIUS_EQUATOR = 6378137.0;
	const double WGS_84_RADIUS_POLAR = 6356752.3142;

	class VRSOFT_TOOLCLASS_DLL CConvert
	{
	public:
		// ��γ�߶�ת������������
		static void LatLongHeightToWord(const double latitude, const double longitude, const double height, \
			double& X, double& Y, double& Z) ;
		template <class T>
		static bool CanvartType(const IAttributeItem* pAttributeItem, T& var);

	private:
		//  ��������� ���쿽�� �ж��Ƿ���� ��ֵ ���Ҳ����г�ʼ������������Ĭ��c++����
		explicit CConvert(void);
		CConvert(const CConvert& other);
		CConvert operator= (const CConvert& other);
		bool operator== (const CConvert& other);
		bool operator!= (const CConvert& other);

	};
}


#endif // _CONVERT_H_