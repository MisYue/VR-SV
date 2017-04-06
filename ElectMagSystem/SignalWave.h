#pragma once

namespace VR_Soft
{
	class CSignalWave : public osg::MatrixTransform , public ICommonWave
	{
	public:
		explicit CSignalWave(void);
		virtual ~CSignalWave(void);

		//radius ����Բ�εİ뾶��sampleVerticesCount Բ��ʹ�ö����ģ��Ĳ����������� delta_offset������ʼ��ĽǶ�ƫ������
		virtual bool createShape( double radius_start , double radius_end, eShapeType type, int sampleVerticesCount = 32 , double delta_offset = 0.0 );
		//colorMask�ɵ�λ���λ����Ӧ���䷽��bitΪ1ʱȡprimaryColor��Ϊ0ʱȡsecondaryColor��textureHeightΪ�����������������ϵ�����߶ȡ�

		virtual bool setTexture( osg::Vec4 color, int colorMask, double textureHeight );

		//�ܹ�һ����������ʱ�䣬��λ�롣
		//��ʼ���䣬���뵱ǰʱ�䣬������һ��ʹ�õ�ʱ�䡣
		virtual double startTrans(double loopTime_s);
		//ֹͣ���䣬���ص�ǰʱ�䡣
		virtual void stopTrans();

		//�ı���㡢�յ㣬ֱ������ϵ��
		virtual bool setPosition(osg::Vec3d start, osg::Vec3d end);

		virtual osg::Node* GetDrawObj(osgEarth::MapNode* pMapNode); // ��ȡ��Ⱦ�ڵ�
		virtual osg::Node* GetDrawObj(void); // ��ȡ��Ⱦ�ڵ�
		// �������
		virtual const VRString GetEntityType(void) const;
		// ��������
		virtual void SetName(const VRString& strName);

		//registerObserver/unregisterObserver
		//virtual osg::BoundingSphere computeBound() const;
		// ��ʼ��
		virtual void Init(void);
		// �������Զ���
		virtual IAttribute* CreateAttribute(void);

	public:
		// ��ʼ��״̬��
		virtual void InitStateMachine(IStateMachine* pIStateMachine);

	protected:
		// ��������������վ���
		virtual void GetMatrixInEarth(const osg::Vec3& vPositon)  { }

	private:

		int		_sampleVerCnt;			//Բ�Ĳ�������
		double	_objHeight;			//Բ׶��Բ���ĸ߶ȡ���������������㡣
		double	_TexHeight;			//���������߶ȣ����������ƶ���

		osg::ref_ptr<osg::Geode> _pGeode;

		eShapeType _eShapeType;

	private:
		class SignalCallBack : public osg::Drawable::UpdateCallback
		{
		public:
			SignalCallBack();
			virtual void update(osg::NodeVisitor * nv, osg::Drawable * drawable);

			double			_loopTime;
			osg::Timer		clock;
			osg::Timer_t	lastTime;
		};
	};

	// ע�Ṥ����
	REGISTER_BASEENTITY_FACTORY(CSignalWave, "commontType");
}

