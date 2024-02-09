#include "Converter.h"
#include <windows.h>
namespace Converter
{

  napi_value
  convertLPBYTEToNapiString(napi_env env, LPBYTE source, DWORD source_size)
  {
    size_t size = (source_size / 2) + 1;
    char *tmp_char = new char[size];
    WideCharToMultiByte(CP_ACP, 0, (LPCWCH)source, -1, tmp_char, size, NULL, NULL);
    napi_value result;
    napi_create_string_utf8(env, tmp_char, NAPI_AUTO_LENGTH, &result);
    delete[] tmp_char;
    return result;
  }

  /*
  Convert windows LPCWSTR to napi string
  */
  napi_value
  convertLPCWSTRToNapiString(napi_env env, LPWSTR source)
  {
    int length = WideCharToMultiByte(CP_ACP, 0, source, -1, 0, 0, NULL, NULL);
    char *tmp_char = new char[length];
    WideCharToMultiByte(CP_ACP, 0, source, -1, tmp_char, length, NULL, NULL);
    napi_value result;
    napi_create_string_utf8(env, tmp_char, NAPI_AUTO_LENGTH, &result);
    delete[] tmp_char;
    return result;
  }

  /*
    napi string to wchar_t
  */
  wchar_t *
  convertNapiStringToWChar(napi_env env, napi_value value)
  {
    size_t bufferSize = 1;
    napi_get_value_string_utf8(env, value, NULL, 0, &bufferSize);
    char *buffer = new char[bufferSize + 1];
    napi_get_value_string_utf8(env, value, buffer, bufferSize + 1, &bufferSize);
    const size_t cSize = strlen(buffer) + 1;
    wchar_t *target_buffer = new wchar_t[cSize];
    MultiByteToWideChar(CP_ACP, 0, buffer, -1, target_buffer, cSize);
    delete[] buffer;
    return target_buffer;
  }
}
