#include "AwesomiumManager.h"

AwesomiumManager::AwesomiumManager()
{
	mWebViews.clear();
	mNumWebViews = -1;
	awe_webcore_initialize_default();
}

AwesomiumManager::AwesomiumManager( int _numWebViews )
{
	mNumWebViews = _numWebViews;
	awe_webcore_initialize_default();
}

AwesomiumManager::AwesomiumManager( int _numWebViews,
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
									const string & _customCSS )
{
	mNumWebViews = _numWebViews;

	awe_string* _localePath_awe = awe_string_create_from_ascii(_localePath.c_str(),
		strlen(_localePath.c_str() ) );

	awe_string* _userDataPath_awe = awe_string_create_from_ascii(_userDataPath.c_str(),
		strlen(_userDataPath.c_str() ) );

	awe_string* _pluginPath_awe = awe_string_create_from_ascii(_pluginPath.c_str(),
		strlen(_pluginPath.c_str() ) );

	awe_string* _package_path_awe = awe_string_create_from_ascii(_packagePath.c_str(),
		strlen(_packagePath.c_str() ) );

	awe_string* _logPath_awe = awe_string_create_from_ascii(_logPath.c_str(),
		strlen(_logPath.c_str() ) );

	awe_string* _childProcessPath_awe = awe_string_create_from_ascii(_childProcessPath.c_str(),
		strlen(_childProcessPath.c_str() ) );

	awe_string* _acceptLanguageOverride_awe = awe_string_create_from_ascii(_acceptLanguageOverride.c_str(),
		strlen(_acceptLanguageOverride.c_str() ) );

	awe_string* _defaultCharsetOverride_awe = awe_string_create_from_ascii(_defaultCharsetOverride.c_str(),
		strlen(_defaultCharsetOverride.c_str() ) );

	awe_string* _userAgentOverride_awe = awe_string_create_from_ascii(_userAgentOverride.c_str(),
		strlen(_userAgentOverride.c_str() ) );

	awe_string* _proxyServer_awe = awe_string_create_from_ascii(_proxyServer.c_str(),
		strlen(_proxyServer.c_str() ) );

	awe_string* _proxyConfigScript_awe = awe_string_create_from_ascii(_proxyConfigScript.c_str(),
		strlen(_proxyConfigScript.c_str() ) );

	awe_string* _authServerWhitelist_awe = awe_string_create_from_ascii(_authServerWhitelist.c_str(),
		strlen(_authServerWhitelist.c_str() ) );

	awe_string* _customCSS_awe = awe_string_create_from_ascii(_customCSS.c_str(),
		strlen(_customCSS.c_str() ) );

	awe_webcore_initialize(
		_enablePlugins, 
		_enableJavascript, 
		_enableDatabases, 
		_package_path_awe,
		_localePath_awe, 
		_userDataPath_awe, 
		_pluginPath_awe, 
		_logPath_awe, 
		_logLevel, 
		_forceSingleProcess, 
		_childProcessPath_awe, 
		_enableAutoDetectEncoding, 
		_acceptLanguageOverride_awe, 
		_defaultCharsetOverride_awe, 
		_userAgentOverride_awe, 
		_proxyServer_awe, 
		_proxyConfigScript_awe, 
		_authServerWhitelist_awe, 
		_saveCacheAndCookies, 
		_maxCacheSize, 
		_disableSameOriginPolicy, 
		_disableWinMessagePump, 
		_customCSS_awe 
	);

	awe_string_destroy( _localePath_awe );
	awe_string_destroy( _userDataPath_awe );
	awe_string_destroy( _pluginPath_awe );
	awe_string_destroy( _package_path_awe );
	awe_string_destroy( _logPath_awe );
	awe_string_destroy( _childProcessPath_awe );
	awe_string_destroy( _acceptLanguageOverride_awe );
	awe_string_destroy( _defaultCharsetOverride_awe );
	awe_string_destroy( _userAgentOverride_awe );
	awe_string_destroy( _proxyServer_awe );
	awe_string_destroy( _proxyConfigScript_awe );
	awe_string_destroy( _authServerWhitelist_awe );
	awe_string_destroy( _customCSS_awe );
}

int AwesomiumManager::getNumberOfWebViews()
{
	return mNumWebViews;
}

int AwesomiumManager::addWebView( awe_webview* &_webView )
{
	mNumWebViews++;
	return mNumWebViews;
}

int AwesomiumManager::addWebView( )
{
	mNumWebViews++;
	return mNumWebViews;
}

AwesomiumWebView AwesomiumManager::getItem( int index )
{

}
