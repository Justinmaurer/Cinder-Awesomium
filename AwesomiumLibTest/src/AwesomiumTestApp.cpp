#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"

#include "AwesomiumManager.h"



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
	void mouseUp( MouseEvent event );
	//void mouseMove( MouseEvent event );
	void keyDown(  KeyEvent event );
	void injectChar( KeyEvent event );
	void update();
	void draw();
	void initAwesomium();
	void initAwesomium2();
	void loadWebPage( const string & url );
	void loadWebPage2( const string & url );
	void updateWebPage();
	void updateWebPage2();
	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );

	bool mPage1OnTop;

	int mPageNum;
	int mPageNum2;

	const awe_renderbuffer *mRenderBuffer;
	const awe_renderbuffer *mRenderBuffer2;

	awe_webview* mWebView;
	awe_webview* mWebView2;

	Rectf mWebPageRect;
	Rectf mWebPageRect2;

	Vec2i mWebPageSize;
	Vec2i mWebPageSize2;

	bool mDragging;
	float percentageX;
	float percentageY;

	float Dx1px;
	float Dy1py;
	float Dx2px;
	float Dy2py;

	bool mWebPage1Dragged;
	bool mWebPage2Dragged;
};

void AwesomiumTestAppApp::setup()
{
	mPageNum = -1;
	mPageNum2 = 6;
	mWebPageSize = Vec2i( 800, 600 );
	mWebPageSize2 = Vec2i( 1025, 768 );
	mWebPageRect.set( 0, 0, mWebPageSize.x, mWebPageSize.y );
	mWebPageRect2.set( 1025, 0, mWebPageSize2.x + 1024, mWebPageSize2.y );

	mDragging = false;

	initAwesomium();
	loadWebPage("http://www.pinterest.com/");
	//loadWebPage( "http://flashlight-vnc.sourceforge.net/demo.html" );
	//loadWebPage("http://www.adobe.com/devnet/actionscript/samples/drawing_5.html");
	//loadWebPage("http://www.google.com");
	//loadWebPage("http://www.macromedia.com/support/documentation/en/flashplayer/help/settings_manager08.html");

	initAwesomium2();
	loadWebPage2( "http://www.yahoo.com" );

	mWebPage1Dragged = false;
	mWebPage2Dragged = false;
}

void AwesomiumTestAppApp::injectChar( KeyEvent event ) 
{
	console() << "inject key " << std::endl;
	
	// Key Down
	awe_webkeyboardevent p;
	p.is_system_key = false;
//	p.modifiers = modifiers;

	p.text[0] = event.getChar();
	p.text[1] = 0;
	p.text[2] = 0;
	p.text[3] = 0;
	p.unmodified_text[0] = event.getChar();
	p.unmodified_text[1] = 0;
	p.unmodified_text[2] = 0;
	p.unmodified_text[3] = 0;
	p.virtual_key_code = event.getChar();
	p.native_key_code = event.getChar();
	p.type = AWE_WKT_KEYDOWN;
	awe_webview_inject_keyboard_event(mWebView, p);

	// Key Char
	awe_webkeyboardevent e;
	e.is_system_key = false;
//	e.modifiers = modifiers;
	e.text[0] = event.getChar();
	e.text[1] = 0;
	e.text[2] = 0;
	e.text[3] = 0;
	e.unmodified_text[0] = 0;
	e.unmodified_text[1] = 0;
	e.unmodified_text[2] = 0;
	e.unmodified_text[3] = 0;
	e.virtual_key_code = 0;
	e.native_key_code = 0;
	e.type = AWE_WKT_CHAR;
	awe_webview_inject_keyboard_event(mWebView, e);

	// Key Up
	awe_webkeyboardevent j;
	j.is_system_key = false;
	//j.modifiers = modifiers;

	j.text[0] = event.getChar();
	j.text[1] = 0;
	j.text[2] = 0;
	j.text[3] = 0;
	j.unmodified_text[0] = event.getChar();
	j.unmodified_text[1] = 0;
	j.unmodified_text[2] = 0;
	j.unmodified_text[3] = 0;
	j.virtual_key_code = event.getChar();
	j.native_key_code = event.getChar();
	j.type = AWE_WKT_KEYUP;
	awe_webview_inject_keyboard_event(mWebView, j);
	awe_webcore_update();
}

void AwesomiumTestAppApp::keyDown( KeyEvent event )
{

	injectChar( event );
	/*mPageNum++;
	mPageNum2--;

	console() << "loading page number: " << mPageNum << ", " << mPageNum2 << std::endl;
	
	switch ( mPageNum ){
		case 0: loadWebPage("http://www.homestarrunner.com/sbemail132.html"); break;
		case 1: loadWebPage("https://lh6.googleusercontent.com/-yuv2MXiyTP4/TydzbXisj1I/AAAAAAAAR3I/tYV0zhL6lRQ/s991/Faux+Seals.jpg");	break;
		case 2: loadWebPage("http://www.msn.com");						break;
		case 3: loadWebPage("http://www.libcinder.org");				break;
		case 4: loadWebPage("http://forum.libcinder.org");  break;
		case 5: loadWebPage( "http://www.google.com"); mPageNum = -1; break;
	}

	switch ( mPageNum2 ){
    	case 0: loadWebPage2("http://www.youtube.com/watch?v=kfVsfOSbJY0");  mPageNum2 = 6; break;
		case 1: loadWebPage2("https://lh6.googleusercontent.com/-yuv2MXiyTP4/TydzbXisj1I/AAAAAAAAR3I/tYV0zhL6lRQ/s991/Faux+Seals.jpg");	break;
		case 2: loadWebPage2("http://www.msn.com");						break;
		case 3: loadWebPage2("http://www.libcinder.org");				break;
		case 4: loadWebPage2("http://forum.libcinder.org");  break;
		case 5: loadWebPage2( "http://www.homestarrunner.com/sbemail132.html"); break;
	}*/



}

void AwesomiumTestAppApp::mouseUp( MouseEvent event )
{
	mDragging = false;

	console() << "mouse up" << std::endl;
	awe_webview_inject_mouse_up(mWebView, AWE_MB_LEFT );
}

void AwesomiumTestAppApp::mouseDrag( MouseEvent event )
{

/*	if ( mWebPageRect2.contains( event.getPos() ) ){ 
			mWebPageRect2.set( event.getPos().x - mWebPageSize2.x/2, event.getPos().y - mWebPageSize2.y/2, event.getPos().x + mWebPageSize2.x/2, event.getPos().y + mWebPageSize2.y/2 );
			mWebPage2Dragged = true;
			mWebPage1Dragged = false;
	}
	else*/
	
	if ( mWebPageRect.contains( event.getPos() ) ){

			mWebPage1Dragged = true;
			mWebPage2Dragged = false;

			if ( !mDragging ){
				Dx1px = event.getPos().x - mWebPageRect.x1;
				Dy1py = event.getPos().y - mWebPageRect.y1;
				Dx2px = mWebPageRect.x2 - event.getPos().x;
				Dy2py = mWebPageRect.y2 - event.getPos().y;

				mDragging = true;
			}

			mWebPageRect.set( event.getPos().x - Dx1px, event.getPos().y - Dy1py, event.getPos().x + Dx2px, event.getPos().y + Dy2py);
		
	}
}
void AwesomiumTestAppApp::update()
{
	updateWebPage();
	updateWebPage2();
}

void AwesomiumTestAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	if(mRenderBuffer)
	{
		uint8_t *data = (uint8_t *) awe_renderbuffer_get_buffer(mRenderBuffer);

		Surface renderedSurface = Surface(data, mWebPageSize.x, mWebPageSize.y, 3, SurfaceChannelOrder::BGRA );
		Texture texture = Texture( renderedSurface );

			gl::draw(texture, mWebPageRect);

	}


/*	if(mRenderBuffer2)
	{
		uint8_t *data = (uint8_t *) awe_renderbuffer_get_buffer(mRenderBuffer2);

		Surface renderedSurface = Surface(data, mWebPageSize2.x, mWebPageSize2.y, 3, SurfaceChannelOrder::BGRA );
		Texture texture = Texture( renderedSurface );

		gl::draw(texture, mWebPageRect2);
	}*/
}

void AwesomiumTestAppApp::loadWebPage( const string & url )
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

	mRenderBuffer = awe_webview_render( mWebView );
	
}


void AwesomiumTestAppApp::loadWebPage2( const string & url )
{
	// Create our URL string
	awe_string* url_str = awe_string_create_from_ascii(url.c_str(),
		strlen(url.c_str() ) );

	// Load the URL into our WebView instance
	awe_webview_load_url(mWebView2,
		url_str,
		awe_string_empty(),
		awe_string_empty(),
		awe_string_empty());

	// Destroy our URL string
	awe_string_destroy(url_str);

	// Wait for WebView to finish loading the page
	while(awe_webview_is_loading_page(mWebView2))
		awe_webcore_update();

	mRenderBuffer2 = awe_webview_render( mWebView2 );

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
	mWebView = awe_webcore_create_webview(mWebPageSize.x, mWebPageSize.y,	false);
}

void AwesomiumTestAppApp::initAwesomium2()
{	
	// Create a new WebView to load our page
	mWebView2 = awe_webcore_create_webview(mWebPageSize2.x, mWebPageSize2.y,	false);
}

void AwesomiumTestAppApp::updateWebPage()
{
	awe_webcore_update();

	if ( mRenderBuffer )
		mRenderBuffer = awe_webview_render( mWebView );
}

void AwesomiumTestAppApp::updateWebPage2()
{
	//awe_webcore_update();

	if ( mRenderBuffer2 )
		mRenderBuffer2 = awe_webview_render( mWebView2 );
}

void AwesomiumTestAppApp::mouseDown( MouseEvent event )
{
	console() << "mouse down" << std::endl;
	awe_webview_inject_mouse_down(mWebView, AWE_MB_LEFT);
}

void AwesomiumTestAppApp::mouseMove( MouseEvent event )
{
	console() << "mouse move" << std::endl;
	awe_webview_inject_mouse_move (mWebView, event.getPos().x - mWebPageRect.x1, event.getPos().y - mWebPageRect.y1);
}






CINDER_APP_BASIC( AwesomiumTestAppApp, RendererGl )
