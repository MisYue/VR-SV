#ifndef	_RFM2G_WINDOWS_H_
#define	_RFM2G_WINDOWS_H_

	#if defined(_WIN32)

		/*****************************************************************
		*	VS 2005 & 2008 has a new security feature that complains on lots
		*	of stdio routines. Defining this constant will shut them up.
		******************************************************************/
		#if	(_MSC_VER == 1400)
			#pragma warning(disable:4996)
			#define	_CRT_SECURE_NO_DEPRECATE
		#endif
		#if	(_MSC_VER == 1500)
			#pragma warning(disable:4996)
			#define	_CRT_SECURE_NO_WARNINGS
		#endif

		#include <windows.h>

	#endif

#endif
