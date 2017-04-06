#define OSGRENDER_PLUGIN_EXPORT

#include "../../Public/VRSoft.h"
#include "../../Public/RenderSystem/RenderSystem.h"
#include "MeshManager.h"

#include <osg/CopyOp>
#include <osg/Node>
#include <osgDB/ReadFile>


namespace VR_Soft
{
	CMeshManager::CMeshManager(void)
	{
		m_listNameMeshObj.clear();
		Init();
	}


	CMeshManager::~CMeshManager(void)
	{
	}

	// �����Ⱦ��
	DrawObj* CMeshManager::GetDrawObj(const VRString& strName)
	{
		ListNameMeshObj::iterator itor = m_listNameMeshObj.find(strName);
		if (m_listNameMeshObj.end() == itor)
		{
			return (NULL);
		}

		MeshObj& mshObj = itor->second;

		// �жϵ�ǰ�ڵ��Ƿ�Ϊ��
		if (!mshObj.Valid())
		{
			DrawObj* drawObj = osgDB::readNodeFile(mshObj.m_strName);
			mshObj.SetDrawObj(drawObj);
		}
		
		// ����ָ�����
		return (mshObj.m_drawObj);
	}

	// ������е���Ⱦ��
	const IMeshManager::ListMeshObjs CMeshManager::GetAllMeshObj(void) const
	{
		ListMeshObjs listMeshObjs;
		ListNameMeshObj::const_iterator cstItor = m_listNameMeshObj.begin();
		for (; m_listNameMeshObj.end() != cstItor; ++cstItor)
		{
			listMeshObjs.push_back(cstItor->second);
		}

		return (listMeshObjs);
	}

	// ��ʼ��
	void CMeshManager::Init(void)
	{
		// ��ȡ�����ļ�
		const VRString& strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Config/RenderSystem/RenderSystem.cfg";
		IConfigFile *pIConfigFile = CreateConfigFileInstance(strPath);
		pIConfigFile->ReadConfig();
		const IConfigFile::LstItemValue& lstItemValus = pIConfigFile->GetItemValus("3DModel");
		IConfigFile::LstItemValue::const_iterator cstItor = lstItemValus.begin();
		for (; lstItemValus.end() != cstItor; ++cstItor)
		{
			VRString strName = (*cstItor).strItem;
			DrawObj* drawObj = osgDB::readNodeFile((*cstItor).strValue);
			MeshObj meshObj(strName, drawObj);
			m_listNameMeshObj.insert(ListNameMeshObj::value_type(strName, meshObj));
		}

		VRSOFT_DELETE(pIConfigFile);


	}

	// ��ȡ��������ֵ
	VRString CMeshManager::GetValue( const VRString& strName )
	{
		// ��ȡ�����ļ�
		const VRString& strPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Config/RenderSystem/RenderSystem.cfg";
		IConfigFile *pIConfigFile = CreateConfigFileInstance(strPath);
		pIConfigFile->ReadConfig();
		const IConfigFile::LstItemValue& lstItemValus = pIConfigFile->GetItemValus("3DModel");
		IConfigFile::LstItemValue::const_iterator cstItor = lstItemValus.begin();
		for (; lstItemValus.end() != cstItor; ++cstItor)
		{
			VRString strValueName = (*cstItor).strItem;
			if (0 == strValueName.compare(strName))
			{
				return ((*cstItor).strValue);
			}
		}

		VRSOFT_DELETE(pIConfigFile);

		return ("");
	}

}
