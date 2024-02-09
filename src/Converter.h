#include <node_api.h>
#include <windows.h>
using namespace std;
namespace Converter
{
  wchar_t *
  convertNapiStringToWChar(napi_env env, napi_value value);
  napi_value
  convertLPCWSTRToNapiString(napi_env env, LPWSTR source);
  napi_value
  convertLPBYTEToNapiString(napi_env env, LPBYTE source, DWORD source_size);
}