/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ⱦ�����幤���ӿ�											*/
/* ʱ�䣺 2016-07-05                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IFEATUREGEOMTRYFACTORY_H_
#define _PUBLIC_IFEATUREGEOMTRYFACTORY_H_

namespace VR_Soft
{
	class VRSOFT_PLUGIN_DLL IFeatureGeomtryFactory
	{
	public:
		// ��������
		virtual ~IFeatureGeomtryFactory(void) { }
		// ���������
		virtual OsgEarthGeomtry* CreatePolygon(void) = 0;
		// �������������ַ���
		virtual OsgEarthGeomtry* CreateLineString(void) = 0;
	};
}

#endif // !_PUBLIC_IFEATUREGEOMTRYFACTORY_H_