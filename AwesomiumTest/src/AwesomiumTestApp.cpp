#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"

#include <Awesomium/awesomium_capi.h>

// Various macro definitions
#define WIDTH   512
#define HEIGHT  512
#define URL "http://www.google.com"
#define SLEEP_MS    50

using namespace ci;
using namespace ci::gl;
using namespace ci::app;
using namespace std;

class AwesomiumTestAppApp : public AppBasic {
  public:
	void setup();
	void mouseDrag( MouseEvent event );	
	void keyDown(  KeyEvent event );
	void update();
	void draw();
	void initAwesomium();
	void loadWebPage( const string & url );


	bool mIsMouseDown;
	int mPageNum;

	const unsigned char* rawBuffer;
	const awe_renderbuffer *renderBuffer;
	awe_webview* webView;

	Rectf webPageRect;
};

void AwesomiumTestAppApp::setup()
{
	initAwesomium();
	loadWebPage( "http://www.google.com" );

	mPageNum = -1;
	webPageRect.set( 0, 0, 1024, 768 );

}

void AwesomiumTestAppApp::keyDown( KeyEvent event )
{
	

	mPageNum++;
	console() << "loading page number: " << mPageNum << std::endl;
	switch ( mPageNum ){
	case 0: loadWebPage("http://www.homestarrunner.com/sbemail132.html"); break;
	//case 0: loadWebPage("http://www.yahoo.com");					break;
	case 1: loadWebPage("https://lh6.googleusercontent.com/-yuv2MXiyTP4/TydzbXisj1I/AAAAAAAAR3I/tYV0zhL6lRQ/s991/Faux+Seals.jpg");	break;
	case 2: loadWebPage("http://www.msn.com");						break;
	case 3: loadWebPage("http://www.libcinder.org");				break;
	case 4: loadWebPage("http://forum.libcinder.org");  break;
	case 5: loadWebPage( "http://supertouch-05.interference.local/dev/supertouch/demos/widgets/"); mPageNum = -1; break;

	}

}

void AwesomiumTestAppApp::mouseDrag( MouseEvent event )
{
	//if ( 
	//if ( webPageRect.contains( event.getPos() ) ){
		webPageRect.set( event.getPos().x, event.getPos().y, event.getPos().x + 1024, event.getPos().y + 768 );

	//}


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
		
		/*glDrawPixels(1024, 
					 768, 
					 GL_BGRA, 
					 GL_UNSIGNED_BYTE, 
					 awe_renderbuffer_get_buffer(renderBuffer) );  */

		uint8_t *mData = (uint8_t *) awe_renderbuffer_get_buffer(renderBuffer);

		Surface renderedSurface = Surface(mData, 1024, 768, 3, SurfaceChannelOrder::BGRA );
		Texture texture = Texture( renderedSurface );
		gl::draw(texture, webPageRect);


		//glRasterPos2i(0, 0);
		//glPixelZoom(1.0, -1.0);
		//awe_renderbuffer_get_buffer(renderBuffer);

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
	//awe_webcore_initialize_default();
	awe_webcore_initialize(true, 
						   true, 
						   true, 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   AWE_LL_NORMAL,
						   false, 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(), 
						   awe_string_empty(),
						   awe_string_empty(), 
						   true, 
						   6000, 
						   false, 
						   false, 
						   awe_string_empty() );



	// Create a new WebView to load our page
	webView = awe_webcore_create_webview(1024, 768,	false);
}



CINDER_APP_BASIC( AwesomiumTestAppApp, RendererGl )
