#include "../../Public/VRSoft.h"

namespace VR_Soft
{
	CVRVariant::CVRVariant(void)
		:m_pValue(NULL)  
	{
	}

	CVRVariant::CVRVariant(CVRVariant& ma)  
		:m_pValue(ma.IsEmpty()?NULL:ma.m_pValue->Clone())  
	{  

	}  

	

	// 交换函数
	CVRVariant& CVRVariant::Swap( CVRVariant& ma )
	{
		//交换两个对象的地址，避免了重新申请释放内存，提高效率  
		std::swap( ma.m_pValue, m_pValue);  
		return *this; 
	}

	// 是否为空
	bool CVRVariant::IsEmpty()
	{
		return !m_pValue;
	}
}

