/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦ�����幤���ӿ�											*/
/* ʱ�䣺 2016-07-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _FEATUREGEOMTRYFACTORY_H_
#define _FEATUREGEOMTRYFACTORY_H_

#pragma once

namespace VR_Soft
{
	class CFeatureGeomtryFactory : public IFeatureGeomtryFactory
	{
	public:
		// ���캯��
		CFeatureGeomtryFactory(void);
		// ��������
		virtual ~CFeatureGeomtryFactory(void);

	public:
		// ���������
		virtual OsgEarthGeomtry* CreatePolygon(void);
		// �������������ַ���
		virtual OsgEarthGeomtry* CreateLineString(void) ;
	};
}


#endif // !_FEATUREGEOMTRYFACTORY_H_