/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ·������				                                        */
/* ʱ�䣺 2015-12-01                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IPATHSTRATEGY_H_
#define _PUBLIC_IPATHSTRATEGY_H_

namespace VR_Soft
{
	class VRSOFT_DLL IPathStrategy
	{
	public:
		// ��������
		virtual ~IPathStrategy(void) { }
		// ����ͨ���ؼ������·��
		virtual std::vector<osg::Vec3d> ComputePath(const std::vector<osg::Vec3d>& listKeyPoints) = 0;
	};
}

#endif // !_PUBLIC_IPATHSTRATEGY_H_
