#pragma once
#include <string>
#include "cinder/Vector.h"
#include "cinder/Rect.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include <Awesomium/awesomium_capi.h>
#include <vector>

using namespace std;

class AwesomiumManager {

	public:

		AwesomiumManager();
		AwesomiumManager( bool _enablePlugins,
						  bool _enableJavascript,
						  bool _enableDatabases,
						  const string & _packagePath,
						  const string & _localePath,
						  const string & _userDataPath,
						  const string & _pluginPath,
						  const string & _logPath,
						  awe_loglevel _logLevel,
						  bool _forceSingleProcess,
						  const string & _childProcessPath,
						  bool _enableAutoDetectEncoding,
						  const string & _acceptLanguageOverride,
						  const string & _defaultCharsetOverride,
						  const string & _userAgentOverride,
						  const string & _proxyServer,
						  const string & _proxyConfigScript,
						  const string & _authServerWhitelist,
						  bool _saveCacheAndCookies,
						  int _maxCacheSize,
						  bool _disableSameOriginPolicy,
						  bool _disableWinMessagePump,
						  const string & _customCSS );

	
		~AwesomiumManager(){

		}
        
        

};