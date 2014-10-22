#pragma once
#ifndef __I_RESOURCE_
#define __I_RESOURCE_

namespace Util
{
	class IResource
	{
	public:
		IResource(void);
		virtual ~IResource(void);

		virtual HRESULT Load(const char *filename) = 0;
	};


}
#endif
