/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  �ر���Ľӿ�		                                        */
/* ʱ�䣺 2016-09-16                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IPLACEFEATUREGEOMTRY_H_
#define _PUBLIC_IPLACEFEATUREGEOMTRY_H_

namespace VR_Soft
{
	class OSGRPLOT_DLL IPlaceFeatureGeomtry : public IFeatureGeomtry
	{
	public:
		// ��������
		virtual ~IPlaceFeatureGeomtry(void) { }
		// ��������
		virtual void SetText(const VRString& strText) = 0;
		// ����ͼ��
		virtual void SetIcon(const VRString& strIcon) = 0;
	};
}

#endif // !_PUBLIC_IPLACEFEATUREGEOMTRY_H_