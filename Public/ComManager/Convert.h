/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ת��������			                                        */
/* ʱ�䣺 2015-05-18                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _CONVERT_H_
#define _CONVERT_H_

#pragma once

namespace osg
{
	class Vec3d;
}
namespace osgEarth
{
	class SpatialReference;
}

namespace VR_Soft
{
	class IAttributeItem;

	const double WGS_84_RADIUS_EQUATOR = 6378137.0;
	const double WGS_84_RADIUS_POLAR = 6356752.3142;

	class VRSOFT_DLL CConvert
	{
	public:
		// ��γ�߶�ת������������
		static void LatLongHeightToWord(const double latitude, const double longitude, const double height, \
			double& X, double& Y, double& Z) ;
		// ��γ�߶�ת������������
		static void LatLongHeightToWord(const osg::Vec3d& vGeo, osg::Vec3d& vWord);
		// ��������ת���ɵ�������
		static void WordToLatLongHeight(const osg::Vec3d& vWord, osg::Vec3d& vGeo);
		// ��������ת���ɵ�������
		static void WordToLatLongHeight(const double X, const double Y, const double Z, \
			double& latitude, double& longitude, double& height) ;

		template <class T>
		static bool CanvartType(const IAttributeItem* pAttributeItem, T& var);
	public:
		static osgEarth::SpatialReference* m_pSpatial;

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