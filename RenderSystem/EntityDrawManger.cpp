#define OSGRENDER_PLUGIN_EXPORT
#include "../../Public/VRSoft.h" 
#include "../../Public/RenderSystem/RenderSystem.h"
#include "EntityDrawManger.h"
#include "MeshManager.h"

#include <osg/BlendFunc>
#include <osg/Image>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <boost/filesystem.hpp>


namespace VR_Soft
{
	CEntityDrawManger::CEntityDrawManger(IEntityBase* pIEntityBase)
		:m_pIEntityBase(pIEntityBase), m_pRoot(new osg::MatrixTransform),\
		m_pMtRoot(new osg::MatrixTransform),m_pMtRoot2D(NULL),m_p3DRoot(NULL), \
		m_pMapNode3D(NULL), m_pMapNode2D(NULL)
	{
		// ע�������Ⱦ����
		IViewManager::GetInstance().AddEntityDrawManager(this);

		m_pRoot->addChild(m_pMtRoot);

		m_p3DRoot = new osg::MatrixTransform;

		m_pMtRoot2D = new osg::MatrixTransform;

		Init();
	}


	CEntityDrawManger::~CEntityDrawManger(void)
	{
		m_lstDrawAttribute.clear();

		// �Ƴ�����
		IViewManager::GetInstance().RemoveEntityDrawManager(this);

		// ������и��ڵ�
		typedef osg::Node::ParentList Parents;
		Parents listParent = m_pRoot->getParents();
		for (Parents::iterator itor = listParent.begin(); listParent.end() != itor; ++itor)
		{
			(*itor)->removeChild(m_pRoot);
		}

		// �Ƴ�2D�ڵ�
		Parents list2dParent = m_pMtRoot2D->getParents();
		for (Parents::iterator itor = list2dParent.begin(); list2dParent.end() != itor; ++itor)
		{
			(*itor)->removeChild(m_pMtRoot2D);
		}
		//}


	}

	// ���ʵ��
	IEntityBase* CEntityDrawManger::GetEntity(void) const
	{
		return (m_pIEntityBase);
	}

	// ���õ�����
	void CEntityDrawManger::SetMapNode3D(osgEarth::MapNode* pMapNode)
	{
		m_pMapNode3D = pMapNode;

		//	Init();*/
	}

	// ���õ�����
	void CEntityDrawManger::SetMapNode2D(osgEarth::MapNode* pMapNode)
	{
		m_pMapNode2D = pMapNode;

		//	Init();*/
	}

	// �����Ⱦ��
	DrawObj* CEntityDrawManger::GetDrawObj(void)
	{
		return (m_pRoot);
	}

	// ��ø���Ⱦ��
	DrawObj* CEntityDrawManger::GetRootDrawObj(void)
	{
		return (m_pMtRoot);
	}


	// �����Ⱦ��2D 
	DrawObj* CEntityDrawManger::GetDrawObj2D( void )
	{
		return (m_pMtRoot2D);
	}


	// �����Ⱦ��
	void CEntityDrawManger::Add(IDrawAttribute* pIDrawAttribute)
	{
		// �̰߳�ȫ
		VR_MUTEX_AUTO;

		if (NULL == pIDrawAttribute)
		{
			return;
		}

		// �����Ⱦ��
		if (!IsHand(pIDrawAttribute))
		{
			return;
		}

		// ��ӵ���Ⱦ����
		DrawObj* pDrawObj = pIDrawAttribute->GetDrawObj();

		// ��ӵ���Ⱦ����
		 m_pMtRoot->addChild(pDrawObj);

		m_lstDrawAttribute.push_back(pIDrawAttribute);

		// ��ӳɹ�
		IComManager::GetInstance().WriteLogMsg("��ӵ�ǰ��Ⱦ���Գɹ�", ERROR_NOT_FIND);
	}

	// �Ƴ���Ⱦ����
	void CEntityDrawManger::Remove(IDrawAttribute* pIDrawAttribute)
	{
		// ��ѯ���Ե�λ��
		ListDrawAttribtes::iterator itor = std::find(m_lstDrawAttribute.begin(), m_lstDrawAttribute.end(), pIDrawAttribute);
		if (m_lstDrawAttribute.end() == itor)
		{
			return;
		}

		// ��ӵ���Ⱦ����
		int index = GetIndexDrawAttribute(pIDrawAttribute);
		if (pIDrawAttribute->IsMove())
		{
			m_p3DRoot->removeChild(index);
		}
		else
		{
			m_pMtRoot->removeChild(index);
		}

		m_lstDrawAttribute.erase(itor);
		IComManager::GetInstance().WriteLogMsg("ɾ����ǰ���Գɹ�");
	}

	// �Ƴ���Ⱦ����
	void CEntityDrawManger::Remove( const VRString& strName )
	{
		//std::find(m_lstDrawAttribute.begin(), m_lstDrawAttribute.end(), pIDrawAttribute);
		for (ListDrawAttribtes::iterator itor = m_lstDrawAttribute.begin(); \
			m_lstDrawAttribute.end() != itor; ++itor)
		{
			if (0 == strName.compare((*itor)->GetName()))
			{
				// �Ƴ�����
				IDrawAttribute* pIDrawAttribute = *itor;
				osg::Node* pNode = pIDrawAttribute->GetDrawObj();

				// ���ʹ�ø���
				if (NULL == pNode)
				{
					m_lstDrawAttribute.erase(itor);
				}

				if (0 < pNode->referenceCount())
				{
					// ��ø���
					if (pIDrawAttribute->IsMove())
					{
						m_pMtRoot->removeChild(pNode);
					}
					else
					{
						m_pRoot->removeChild(pNode);
					}
				}

				m_lstDrawAttribute.erase(itor);
				return;
			}
		}

	}

	// �޸�ʵ����Ⱦ
	void CEntityDrawManger::ChangerMeshDrawAttribute(IDrawAttribute* pIDrawAttribute, const VRString& strName)
	{
		// ��ѯ���Ե�λ��
		ListDrawAttribtes::iterator itor = std::find(m_lstDrawAttribute.begin(), m_lstDrawAttribute.end(), pIDrawAttribute);
		if (m_lstDrawAttribute.end() == itor)
		{
			return;
		}

		IMeshDrawAttribute* pIMeshDrawAttribute = dynamic_cast<IMeshDrawAttribute*>(pIDrawAttribute);
		if (NULL == pIMeshDrawAttribute)
		{
			return ;
		}

		// ����µ���Ⱦ��
		DrawObj* pNewNode = CMeshManager::GetInstance().GetDrawObj(strName);
		if (NULL == pNewNode)
		{
			return;
		}

		// �����Ⱦ��
		DrawObj* pNode = pIMeshDrawAttribute->GetDrawObj();
		// �Ƴ���ǰ��Ⱦ��
		if (NULL != pNode)
		{
			// ������и��ڵ�
			typedef osg::Node::ParentList Parents;
			Parents listParent = pNode->getParents();
			for (Parents::iterator itor = listParent.begin(); listParent.end() != itor; ++itor)
			{
				(*itor)->removeChild(pNode);
			}
		}
		
		m_p3DRoot->addChild(pNewNode);
		pIMeshDrawAttribute->SetDrawObj(pNewNode);		
	}

	// �����Ⱦ����
	IDrawAttribute* CEntityDrawManger::GetAttribute(const VRString& strName) const
	{
		ListDrawAttribtes::const_iterator itor = m_lstDrawAttribute.begin();
		for (; m_lstDrawAttribute.end() != itor; ++itor)
		{
			if ( 0 == (*itor)->GetName().compare(strName))
			{
				return (*itor);
			}
		}

		return (NULL);
	}

	// ��������
	void CEntityDrawManger::Update(void)
	{
		// �ж��Ƿ���Ҫ����
		if (!m_pIEntityBase->IsUpdate())
		{
			// ����Ҫ����
			return;
		}

		// ��û�������
		IEntityDrawAttribute* pIEntityDrawAttribute = m_pIEntityBase->GetEntityDrawAttribute();
		IEntityBaseAttribute* pIEntityBaseAttribute = m_pIEntityBase->GetBaseAttribute();
		
		if ((NULL == pIEntityBaseAttribute) || (NULL == pIEntityDrawAttribute))
		{
			return;
		}

		osg::Vec3d vPositiond = pIEntityDrawAttribute->GetPosition();
		osg::Vec3d vRotate = pIEntityDrawAttribute->GetRotate();
		osg::Vec3d vScal = pIEntityDrawAttribute->GetScale();


		// �������е���ʾ��Ⱦ����
		int nSize = (int)m_lstDrawAttribute.size();
		for (int index = 0; index < nSize; ++index)
		{
			m_lstDrawAttribute[index]->Update();
		}

		osg::Quat vQuat(vRotate.x(), osg::X_AXIS, vRotate.y(), osg::Y_AXIS, vRotate.z(), osg::Z_AXIS);

		osg::Matrix mt = osg::Matrix::rotate(vQuat) * osg::Matrix::scale(vScal);

		// �ж��Ƿ�ı��˶�άͼƬ
		if (pIEntityDrawAttribute->ChangeEntity2D())
		{
			ChangeEntity2D(pIEntityDrawAttribute->GetEntity2D());
		}

		// ���ʵ������ϵ
		IEntityBaseAttribute::EntityCoordinate ec = pIEntityBaseAttribute->GetEntityCoordinate();
		if (IEntityBaseAttribute::MODEL == ec)
		{
			m_pMtRoot->setMatrix(mt * osg::Matrix::translate(vPositiond));
		}
		else if (IEntityBaseAttribute::EARTH == ec)
		{
			// �����Ⱦģʽ
			const IEntityDrawAttribute::DrawModel dm = pIEntityDrawAttribute->GetDrawModel();
			if (IEntityDrawAttribute::DM_2D == dm)
			{
				m_pMtRoot->setNodeMask(0x00);
				m_pMtRoot2D->setNodeMask(0x01);
				const osgEarth::SpatialReference* mapSRS = m_pMapNode2D->getMapSRS();
				osgEarth::GeoPoint localPosition(mapSRS->getGeographicSRS(), vPositiond.x(), vPositiond.y(), 0.0/*, osgEarth::ALTMODE_ABSOLUTE*/);
				osg::Matrix local2World;
				const osgEarth::GeoPoint mapPos = localPosition.transform(mapSRS);
				mapPos.createLocalToWorld(local2World);
				m_pMtRoot2D->setMatrix(mt * local2World);
			}
			else if (IEntityDrawAttribute::DM_3D == dm)
			{
				m_pMtRoot2D->setNodeMask(0x00);
				m_pMtRoot->setNodeMask(0x01);
				const osgEarth::SpatialReference* mapSRS = m_pMapNode3D->getMapSRS();
				osgEarth::GeoPoint localPosition(mapSRS->getGeographicSRS(), vPositiond.x(), vPositiond.y(), vPositiond.z()/*, osgEarth::ALTMODE_ABSOLUTE*/);
				osg::Matrix local2World;
				const osgEarth::GeoPoint mapPos = localPosition.transform(mapSRS);
				mapPos.createLocalToWorld(local2World);
				m_pMtRoot->setMatrix(mt * local2World);
			}
			else if (IEntityDrawAttribute::DM_2D_3D)
			{
				m_pMtRoot->setNodeMask(0x01);
				m_pMtRoot2D->setNodeMask(0x01);
				// 2Dλ��
				if (NULL != m_pMapNode2D)
				{
					const osgEarth::SpatialReference* mapSRS2D = m_pMapNode2D->getMapSRS();
					osgEarth::GeoPoint localPosition2D(mapSRS2D->getGeographicSRS(), vPositiond.x(), vPositiond.y(), 0.0/*, osgEarth::ALTMODE_ABSOLUTE*/);
					osg::Matrix local2World2D;
					const osgEarth::GeoPoint mapPos2D = localPosition2D.transform(mapSRS2D);
					mapPos2D.createLocalToWorld(local2World2D);
					m_pMtRoot2D->setMatrix(mt * local2World2D);
				}

				// 3Dλ��
				if (NULL != m_pMapNode3D)
				{
					const osgEarth::SpatialReference* mapSRS3D = m_pMapNode3D->getMapSRS();
					osgEarth::GeoPoint localPosition3D(mapSRS3D->getGeographicSRS(), vPositiond.x(), vPositiond.y(), vPositiond.z()/*, osgEarth::ALTMODE_ABSOLUTE*/);
					osg::Matrix local2World3D;
					const osgEarth::GeoPoint mapPos3D = localPosition3D.transform(mapSRS3D);
					mapPos3D.createLocalToWorld(local2World3D);
					m_pMtRoot->setMatrix(mt * local2World3D);
				}

			}
		}
		else
		{
			m_pMtRoot->setMatrix(mt * osg::Matrix::translate(vPositiond));
		}
	}

	// ��ʼ��
	void CEntityDrawManger::Init(void)
	{
		m_p2DImage = new osg::Geode;
		m_p2DImage->setCullingActive(true);
		// ������Ⱦ˳��
		m_p2DImage->getOrCreateStateSet()->setRenderBinDetails(9000, "RenderBin");

		osg::Geometry *galaxy = new osg::Geometry();
		osg::Vec3Array *vertices = new osg::Vec3Array();
		osg::Vec4Array *colors = new osg::Vec4Array();

		int nWidth = 16;
		vertices->push_back(osg::Vec3(-nWidth, -nWidth, 0));
		vertices->push_back(osg::Vec3(-nWidth, nWidth, 0));
		vertices->push_back(osg::Vec3(nWidth, nWidth, 0));
		vertices->push_back(osg::Vec3(nWidth, -nWidth, 0));
		colors->push_back(osg::Vec4(1, 1, 1, 1));

		osg::Vec2Array* texcoords = new osg::Vec2Array(4);
		(*texcoords)[0].set(0.0f,1.0f);
		(*texcoords)[1].set(0.0f,0.0f);
		(*texcoords)[2].set(1.0f,0.0f);
		(*texcoords)[3].set(1.0f,1.0f);
		galaxy->setTexCoordArray(0,texcoords);

		osg::Vec3Array* normals = new osg::Vec3Array(1);
		(*normals)[0].set(0.0f,0.0f,1.0f);
		galaxy->setNormalArray(normals, osg::Array::BIND_OVERALL);

		galaxy->setVertexArray(vertices);
		galaxy->setColorArray(colors, osg::Array::BIND_OVERALL);
		galaxy->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
		m_p2DImage->addDrawable(galaxy);

		osg::StateSet* pStateSet = m_p2DImage->getOrCreateStateSet();
		/// Setup cool blending
		pStateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		osg::BlendFunc *fn = new osg::BlendFunc();
		fn->setFunction(osg::BlendFunc::SRC_ALPHA, osg::BlendFunc::DST_ALPHA);
		pStateSet->setAttributeAndModes(fn, osg::StateAttribute::ON);

		/// Disable depth test to avoid sort problems and Lighting
		pStateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		/// The texture for the sprites
		osg::Texture2D* texture = new osg::Texture2D;
		texture->setDataVariance(osg::Object::STATIC); 

		// ���ʵ��
		const VRString& str = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Data/2D/"+ "ddc.png";
		osg::Image* pImage = osgDB::readImageFile(str);
		pImage->flipVertical();
		texture->setImage(pImage);

		texture->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
		texture->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);

		pStateSet->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
				

		osg::AutoTransform* pAutoTransform = new osg::AutoTransform;
		pAutoTransform->addChild(m_p2DImage);

		//pAutoTransform->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_CAMERA);
		pAutoTransform->setAutoScaleToScreen(true);
		m_pLod = new osg::LOD;

		pAutoTransform->getOrCreateStateSet()->setRenderingHint(1000);
//		pAutoTransform->getOrCreateStateSet()->setRenderBinMode(osg::StateSet::OVERRIDE_PROTECTED_RENDERBIN_DETAILS);

		pAutoTransform->setAutoScaleTransitionWidthRatio(0.05);
		pAutoTransform->setPosition(osg::Vec3d(0, 0, 0));

		m_pLod->addChild(pAutoTransform, 700.0f, INT_MAX);
		m_pLod->addChild(m_p3DRoot, 0.0f,  700.0f);
		m_pMtRoot2D->addChild(pAutoTransform);

		// ��ά�ر�test ����
		m_pMtRoot2D->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
		m_pMtRoot2D->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

		m_pMtRoot->addChild(m_pLod);

	}

	// �����Ƿ���ڵ�ǰ������
	bool CEntityDrawManger::IsHand(IDrawAttribute* pIDrawAttribte)
	{
		ListDrawAttribtes::const_iterator cstItor = std::find(m_lstDrawAttribute.begin(), m_lstDrawAttribute.end(), pIDrawAttribte);
		return (m_lstDrawAttribute.end() == cstItor);
	}

	// �������
	int CEntityDrawManger::GetIndexDrawAttribute(IDrawAttribute* pIDrawAttribute)
	{
		// �������е���Ⱦ����
		ListDrawAttribtes::const_iterator cstItor = m_lstDrawAttribute.begin();
		for (int index = 0; cstItor != m_lstDrawAttribute.end(); ++index, ++cstItor)
		{
			if ((*cstItor) == pIDrawAttribute)
			{
				return (index);
			}
		}

		return (-1);
	}

	// �Ƴ�������Ⱦ����
	void CEntityDrawManger::RemoveAll()
	{
		m_lstDrawAttribute.clear();
	}

	// �ı��άͼƬ
	void CEntityDrawManger::ChangeEntity2D( const VRString& strEntity2D )
	{
		const VRString& str = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Data/2D/"+ strEntity2D;
		
		namespace bf = boost::filesystem;
		bf::path path(str.c_str());

		// �ж��ļ��Ƿ����
		if (!bf::exists(path))
		{
			return;
		}
		
		osg::StateAttribute* pStateAttribute = m_p2DImage->getOrCreateStateSet()->getTextureAttribute(0, osg::StateAttribute::TEXTURE);
		if (NULL == pStateAttribute)
		{
			return;
		}

		// �������
		osg::Texture2D* pTexture2D = dynamic_cast<osg::Texture2D*>(pStateAttribute);
		if (NULL == pTexture2D)
		{
			pTexture2D = new osg::Texture2D;
			pTexture2D->setDataVariance(osg::Object::STATIC); 

			m_p2DImage->getOrCreateStateSet()->setTextureAttributeAndModes(0, pTexture2D, osg::StateAttribute::ON);
		}

		// ���¶�ȡͼƬ
		osg::Image* pImage = osgDB::readImageFile(str);
		// ������������
		pImage->flipVertical();
		pTexture2D->setImage(pImage);

		pTexture2D->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::LINEAR);
		pTexture2D->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::LINEAR);		
	}

}
