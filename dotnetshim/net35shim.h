#ifdef NET35SHIM_EXPORTS
#define NET35SHIM_API __declspec(dllexport)
#else
#define NET35SHIM_API __declspec(dllimport)
#endif

class Net35Shim
{
public:
	Net35Shim(LPCWSTR runtimeVersion);
	~Net35Shim();

	HRESULT GetLastResult() const { return _hr; }
	int RunMethod(const WCHAR *file, const WCHAR *type, const WCHAR *method);
private:
	HRESULT _hr;
	CComPtr<ICLRMetaHost> pMetaHost;
	CComPtr<ICLRRuntimeHost> pRuntimeHost;
	CComPtr<ICLRRuntimeInfo> pRuntimeInfo;
};

extern "C"
{
	NET35SHIM_API HRESULT GetStatus(Net35Shim* shim);
	NET35SHIM_API Net35Shim* Create(LPCWSTR runtimeVersion);
	NET35SHIM_API HRESULT RunMethod(Net35Shim* shim, int &result, const LPWSTR file, const LPWSTR type, const LPWSTR method);
	NET35SHIM_API HRESULT Delete(Net35Shim** shim);
}
