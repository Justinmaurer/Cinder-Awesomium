#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

#include <Awesomium/awesomium_capi.h>

// Various macro definitions
#define WIDTH   512
#define HEIGHT  512
#define URL "http://www.google.com"
#define SLEEP_MS    50

using namespace ci;
using namespace ci::app;
using namespace std;

class AwesomiumTestAppApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void initAwesomium();
	void loadWebPage( const string & url );

	int mPageNum;

	const unsigned char* rawBuffer;
	const awe_renderbuffer *renderBuffer;
	awe_webview* webView;
};

void AwesomiumTestAppApp::setup()
{
	initAwesomium();
	loadWebPage( "http://www.google.com" );

	mPageNum = 0;

}

void AwesomiumTestAppApp::mouseDown( MouseEvent event )
{
	console() << "loading page number: " << mPageNum << std::endl;

	switch ( mPageNum ){
		case 0: loadWebPage("http://www.yahoo.com");					break;
		case 1: loadWebPage("http://www.google.com");					break;
		case 2: loadWebPage("http://www.msn.com");						break;
		case 3: loadWebPage("http://www.libcinder.org");				break;
		case 4: loadWebPage("http://forum.libcinder.org"); mPageNum = 0; break;
	}

	mPageNum++;

}

void AwesomiumTestAppApp::update()
{
}

void AwesomiumTestAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if(renderBuffer)
	{
		// Draw pixels directly to screen from our image buffer
		
		glDrawPixels(1024, 
					 768, 
					 GL_BGRA, 
					 GL_UNSIGNED_BYTE, 
					 awe_renderbuffer_get_buffer(renderBuffer) );   

		// awe_renderbuffer_get_buffer(renderBuffer);

		// glDrawPixels(getWindowWidth(), getWindowHeight(), GL_RGB, GL_UNSIGNED_BYTE, awe_renderbuffer_get_buffer(renderBuffer) );  
		
	}
}

void AwesomiumTestAppApp::loadWebPage( const string & url )
{


	// Create our URL string
	awe_string* url_str = awe_string_create_from_ascii(url.c_str(),
		strlen(url.c_str() ) );

	// Load the URL into our WebView instance
	awe_webview_load_url(webView,
		url_str,
		awe_string_empty(),
		awe_string_empty(),
		awe_string_empty());

	// Destroy our URL string
	awe_string_destroy(url_str);

	// Wait for WebView to finish loading the page
	while(awe_webview_is_loading_page(webView))
		awe_webcore_update();

	renderBuffer = awe_webview_render( webView );
	
}

void AwesomiumTestAppApp::initAwesomium()
{
	// Create the WebCore with the default options
	awe_webcore_initialize_default();



	// Create a new WebView to load our page
	webView = awe_webcore_create_webview(1024, 768,	false);
}



CINDER_APP_BASIC( AwesomiumTestAppApp, RendererGl )
