// net35shim.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "net35shim.h"

NET35SHIM_API Net35Shim* Create(LPCWSTR version)
{
	return new Net35Shim(version);
}

NET35SHIM_API HRESULT GetStatus(Net35Shim* shim)
{
	if (shim == nullptr)
	{
		return E_HANDLE;
	}

	return shim->GetLastResult();
}

NET35SHIM_API HRESULT RunMethod(Net35Shim* shim, int &result, const LPWSTR file, const LPWSTR type, const LPWSTR method)
{
	if (shim == nullptr)
	{
		return E_HANDLE;
	}

	if (!SUCCEEDED(shim->GetLastResult()))
	{
		return shim->GetLastResult();
	}

	result = shim->RunMethod(file, type, method);

	return shim->GetLastResult();
}

NET35SHIM_API HRESULT Delete(Net35Shim** shim)
{
	if (*shim == nullptr)
	{
		return S_OK;
	}

	delete *shim;

	*shim = nullptr;

	return S_OK;
}

int Net35Shim::RunMethod(const WCHAR *file, const WCHAR *type, const WCHAR *method)
{
	DWORD returnValue = 0;
	_hr = pRuntimeHost->ExecuteInDefaultAppDomain(file, type, method, L"test1", &returnValue);

	return returnValue;
}

Net35Shim::~Net35Shim()
{
	if (pRuntimeHost)
	{
		HRESULT hr = pRuntimeHost->Stop();
	}
}

Net35Shim::Net35Shim(LPCWSTR runtimeVersion)
{
	HRESULT hr;

	hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pMetaHost);

	if (SUCCEEDED(hr))
	{
		hr = pMetaHost->GetRuntime(runtimeVersion, IID_PPV_ARGS(&pRuntimeInfo));

		if (SUCCEEDED(hr))
		{
			hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, IID_PPV_ARGS(&pRuntimeHost));

			if (SUCCEEDED(hr))
			{
				hr = pRuntimeHost->Start();
			}
		}
	}

	_hr = hr;
}