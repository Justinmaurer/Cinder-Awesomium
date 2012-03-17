#pragma once

#include "AwesomiumWebView.h"
#include <vector>

using namespace std;

class AwesomiumManager {

	public:
		//const string test;

		AwesomiumManager();
		AwesomiumManager( int _numWebViews );
		AwesomiumManager( int _numWebViews, 
						  bool _enablePlugins,
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
			mWebViews.clear();
		}


		int					getNumberOfWebViews();
		int					addWebView( awe_webview* &_webView );
		int					addWebView( );
		AwesomiumWebView	getItem( int index );
		
	private:
		int mNumWebViews;
		std::vector<awe_webview*> mWebViews;
};