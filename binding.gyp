{
  "targets": [
    {
      "target_name": "WCMAccessor",
      "sources": [ "src/WCMAccessor.cpp", "src/Converter.cpp"],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
    }
  ]
}