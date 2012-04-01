#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

#include <Awesomium/awesomium_capi.h>

// Various macro definitions
#define WIDTH   512
#define HEIGHT  512
#define URL "http://www.google.com"
#define SLEEP_MS    50

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderAwesomiumLibTestApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void initAwesomium();
    void loadWebPage( const string & url );
    void updateWebPage();
    
    const awe_renderbuffer *mRenderBuffer;
    awe_webview* mWebView;
    Rectf mWebPageRect;
    Vec2i mWebPageSize;
};

void CinderAwesomiumLibTestApp::setup()
{
    mWebPageSize = Vec2i( 1024, 768 );
    mWebPageRect.set( 0, 0, mWebPageSize.x, mWebPageSize.y );
    initAwesomium();
    loadWebPage( "http://www.google.com" );
}

void CinderAwesomiumLibTestApp::mouseDown( MouseEvent event )
{
}

void CinderAwesomiumLibTestApp::initAwesomium()
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
	mWebView = awe_webcore_create_webview(mWebPageSize.x, mWebPageSize.y,	false);
}


void CinderAwesomiumLibTestApp::loadWebPage( const string & url )
{
	// Create our URL string
	awe_string* url_str = awe_string_create_from_ascii(url.c_str(),
                                                       strlen(url.c_str() ) );
    
	// Load the URL into our WebView instance
	awe_webview_load_url(
                         mWebView,
                         url_str,
                         awe_string_empty(),
                         awe_string_empty(),
                         awe_string_empty() );
    
	// Destroy our URL string
	awe_string_destroy(url_str);
    
	// Wait for WebView to finish loading the page
	while(awe_webview_is_loading_page(mWebView))
		awe_webcore_update();
    
    console() << "web page has loaded" << std::endl;
    
	mRenderBuffer = awe_webview_render( mWebView );
	
}

void CinderAwesomiumLibTestApp::updateWebPage()
{
	awe_webcore_update();
    
	if ( mRenderBuffer )
		mRenderBuffer = awe_webview_render( mWebView );
}

void CinderAwesomiumLibTestApp::update()
{
    updateWebPage();
}

void CinderAwesomiumLibTestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
    
	if(mRenderBuffer)
	{
		uint8_t *data = (uint8_t *) awe_renderbuffer_get_buffer(mRenderBuffer);
        
		Surface renderedSurface = Surface(data, mWebPageSize.x, mWebPageSize.y, 3, SurfaceChannelOrder::BGRA );
        gl::Texture texture = gl::Texture( renderedSurface );
		gl::draw(texture, mWebPageRect);
        
	}
}


CINDER_APP_BASIC( CinderAwesomiumLibTestApp, RendererGl )
