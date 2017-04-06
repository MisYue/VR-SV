/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ʵ����Ⱦ���Խӿ���	                                        */
/* ʱ�䣺 2016-08-10                                                    */
/* �޸�ʱ��:                                                            */
/************************************************************************/

#ifndef _PUBLIC_IENTITYDRAWATTRIBUTE_H_
#define _PUBLIC_IENTITYDRAWATTRIBUTE_H_

namespace VR_Soft
{
	class IEntityDrawAttribute : public IAttribute
	{
	public: 
		enum DrawModel
		{
			DM_3D,		// ��άģʽ
			DM_2D,		// ��άģʽ
			DM_2D_3D	// ��ά��άģʽ
		};

	public: 
		// ��������
		virtual ~IEntityDrawAttribute(void) { }
		// ����λ��
		virtual void SetPosition(const osg::Vec3d& vPos) = 0;
		// ���λ��
		virtual osg::Vec3d GetPosition(void) const = 0;
		// ��������
		virtual void SetScale(const osg::Vec3d& vScale) = 0;
		// �������
		virtual osg::Vec3d GetScale(void) const = 0;
		// ������ת
		virtual void SetRotate(const osg::Vec3d& vRot) = 0;
		// �����ת
		virtual osg::Vec3d GetRotate(void) const = 0;
		// ������ʾģʽ
		virtual void SetDrawModel(const DrawModel dm) = 0;
		// �����ʾģʽ
		virtual DrawModel GetDrawModel(void) const = 0;
		// ���ö�ά��ʾͼƬ
		virtual void SetEntity2D(const VRString& strFile) = 0;
		// ��ö�ά��ʾͼƬ
		virtual VRString GetEntity2D(void) const = 0;
		// �Ƿ�ı䵱ǰ�Ķ�άͼƬ
		virtual bool ChangeEntity2D(void) const = 0;
	};
}

#endif // ! _PUBLIC_IENTITYDRAWATTRIBUTE_H_