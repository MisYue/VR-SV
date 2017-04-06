
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include "../../Public/VRSoft.h"
#include "ComManagerConfig.h"

namespace VR_Soft
{
	CComManagerConfig::CComManagerConfig(const VRString& strPath):m_strPath(strPath), m_strCurPath("")
	{
	}


	CComManagerConfig::~CComManagerConfig(void)
	{
		Sava();
	}

	// 添加当前已添加的模型
	void CComManagerConfig::AddComName(const VRString& strComName )
	{
		VR_MUTEX_AUTO;

		m_lstLoadedCom.push_back(strComName);

		// 保存
		Sava();
	}

	// 移除当前已添加的组件
	void CComManagerConfig::RemoveComName(const VRString& strComName)
	{
		VR_MUTEX_AUTO;

		LstLoadedCom::iterator itor = std::find(m_lstLoadedCom.begin(), m_lstLoadedCom.end(), strComName);
		if (m_lstLoadedCom.end() == itor)
		{
			return;
		}

		// 移除
		m_lstLoadedCom.erase(itor);

		// 保存
		Sava();
	}

	// 保存当前已经添加的名称
	void CComManagerConfig::Sava(void)
	{
		const VRString str = GetCurPath()  + "/Config/ComManager/commanager.cfg";

		// 打开配置文件
		// 打开配置文件
		FILE* pFile = NULL;
		pFile = fopen(str.c_str(), "w");
		if (NULL == pFile)
		{
			ILogManager::GetInstance().SetLogMessage("打开配置文件失败", ERROR_NOT_FIND);
			return;
		}

		// 写入文件
		LstLoadedCom::const_iterator cstItor = m_lstLoadedCom.begin();
		for (; m_lstLoadedCom.end() != cstItor; ++cstItor)
		{
			//out<<*cstItor<<std::endl;
			fwrite((*cstItor).c_str(), 1, (*cstItor).size(), pFile);
			fwrite("\n", 1, strlen("\n"), pFile);
		}

		fclose(pFile);

		// 读取完毕
		ILogManager::GetInstance().SetLogMessage("组件配置文件读取完毕");
	/*	std::ofstream out(str);
		if (!out.is_open())
		{
			return;
		}

		LstLoadedCom::const_iterator cstItor = m_lstLoadedCom.begin();
		for (; m_lstLoadedCom.end() != cstItor; ++cstItor)
		{
			out<<*cstItor<<std::endl;
		}

		out.close();
	*/
	}

	// 读取已添加的插件名称
	void CComManagerConfig::ReadCom(void)
	{
		const VRString str = GetCurPath()  + "/Config/ComManager/commanager.cfg";

		// 打开配置文件
		FILE* pFile = NULL;
		pFile = fopen(str.c_str(), "r");
		if (NULL == pFile)
		{
			ILogManager::GetInstance().SetLogMessage("打开配置文件失败", ERROR_NOT_FIND);
			return;
		}

		while (!feof(pFile))
		{
			// 读取行
			char szLine[256] = {0};
			fgets(szLine, sizeof(szLine) - 1, pFile); // 包含了\n  
			if (1 >= strlen(szLine))
			{
				continue;
			}
			Replace(szLine); // 去除\n
			IComManager::GetInstance().GetComManagerUI()->InstallPlugin(szLine);
		}

		// 关闭文件
		fclose(pFile);
		// 读取完毕
		ILogManager::GetInstance().SetLogMessage("组件配置文件读取完毕");		
	}

	// 初始化整个系统
	void CComManagerConfig::Init() 
	{
		VR_MUTEX_AUTO;

		ReadCom();
	}

	// 获得执行路径
	VRString CComManagerConfig::GetCurPath(void) const 
	{
		if (0 == m_strCurPath.compare(""))
		{
			GetExePath();
		}

		return (m_strCurPath);
	}

	// 获得全部路径
	VRString CComManagerConfig::GetExePath(void) const
	{
		if (m_strPath.empty())
		{
			IComManager::GetInstance().WriteLogMsg("当前路径获取失败");
			return (m_strPath);
		}

		// 查找最后一个 ‘/’
		const int nPos = m_strPath.find_last_of('\\');
		if (-1 == nPos)
		{
			return VRString("");
		}

		// 获得路径
		VRString str = m_strPath.substr(0, nPos);

		// 当前路径
		IComManager::GetInstance().WriteLogMsg("当前路径为:"+str);
		m_strCurPath = str;
		return (str);
	}

	void CComManagerConfig::Replace(char* szLine)
	{
		// 进行替换'\n'
		char* pLine = szLine;
		while ('\n' != *pLine)
		{
			++pLine;
		}

		*pLine = '\0';
	}

}

