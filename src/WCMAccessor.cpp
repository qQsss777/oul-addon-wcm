#include <node_api.h>
#include <windows.h>
#include <wincred.h>
#include <assert.h>
#include <wchar.h>
#include "Converter.h"
#include "WCMAccessor.h"

using namespace Converter;

namespace WCMAccessor
{

  napi_value GetCredentials(napi_env env, napi_callback_info info)
  {

    // variables
    char *buffer = nullptr;
    napi_status status;

    // get arguments
    size_t bufferSize = 1;
    napi_value args[1];
    status = napi_get_cb_info(env, info, &bufferSize, args, NULL, NULL);
    assert(status == napi_ok);
    if (bufferSize < 1)
    {
      napi_throw_type_error(env, NULL, "L'adresse n'est pas renseignée.");
      return nullptr;
    }

    LPWSTR host = (LPWSTR)convertNapiStringToWChar(env, args[0]);
    PCREDENTIALW pcred;
    BOOL ok = CredReadW(host, CRED_TYPE_GENERIC, 0, &pcred);
    delete[] host;
    if (!ok)
    {
      napi_throw_type_error(env, NULL, "L'adresse n'existe pas.");
      return nullptr;
    }

    // get username & password
    napi_value username = convertLPCWSTRToNapiString(env, pcred->UserName);
    napi_value password = convertLPBYTEToNapiString(env, pcred->CredentialBlob, pcred->CredentialBlobSize);

    // write result
    napi_value credentials;
    status = napi_create_object(env, &credentials);
    assert(status == napi_ok);
    status = napi_set_named_property(env, credentials, "username", username);
    status = napi_set_named_property(env, credentials, "password", password);
    assert(status == napi_ok);
    CredFree(pcred);
    return credentials;
  };

  napi_value SetCredentials(napi_env env, napi_callback_info info)
  {

    // variables
    char *buffer = nullptr;
    napi_status status;

    // get arguments
    size_t bufferSize = 3;
    napi_value args[3];
    status = napi_get_cb_info(env, info, &bufferSize, args, NULL, NULL);
    assert(status == napi_ok);
    if (bufferSize != 3)
    {
      napi_throw_type_error(env, NULL, "Paramètres incorrects");
      return nullptr;
    }

    CREDENTIALW cred = {0};
    wchar_t *host = convertNapiStringToWChar(env, args[0]);
    wchar_t *user = convertNapiStringToWChar(env, args[1]);
    wchar_t *password = convertNapiStringToWChar(env, args[2]);
    cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = (LPWSTR)host;
    cred.UserName = (LPWSTR)user;
    cred.CredentialBlob = (LPBYTE)password;
    cred.CredentialBlobSize = (wcslen(password) + 1) * sizeof(wchar_t);
    napi_value result;
    if (!::CredWriteW(&cred, 0))
    {
      napi_create_int32(env, 0, &result);
    }
    else
    {
      napi_create_int32(env, 1, &result);
    }
    delete[] user;
    delete[] password;
    delete[] host;
    delete[] buffer;
    return result;
  }

  napi_value init(napi_env env, napi_value exports)
  {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, nullptr, 0, GetCredentials, nullptr, &fn);
    if (status != napi_ok)
      return nullptr;

    status = napi_set_named_property(env, exports, "getCredentials", fn);
    if (status != napi_ok)
      return nullptr;

    status = napi_create_function(env, nullptr, 0, SetCredentials, nullptr, &fn);
    if (status != napi_ok)
      return nullptr;

    status = napi_set_named_property(env, exports, "setCredentials", fn);
    if (status != napi_ok)
      return nullptr;
    return exports;
  };

  NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
};
