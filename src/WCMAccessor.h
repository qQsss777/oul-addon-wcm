#include <node_api.h>
namespace WCMAccessor
{

  napi_value GetCredentials(napi_env env, napi_callback_info info);
  napi_value SetCredentials(napi_env env, napi_callback_info info);
  napi_value init(napi_env env, napi_value exports);
};
