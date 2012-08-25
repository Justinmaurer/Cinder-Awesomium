#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "boost/lexical_cast.hpp"


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
	void prepareSettings( Settings *settings );
	void setup();
	void mouseDrag( MouseEvent event );
	void mouseUp( MouseEvent event );
	//void mouseMove( MouseEvent event );
	void keyDown(  KeyEvent event );
	void injectChar( KeyEvent event );
	void update();
	void draw();
	void initAwesomium();
	void loadWebPage( const string & url );
	void updateWebPage();
	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );

	bool mPage1OnTop;

	int mPageNum;
	int mPageNum2;

	const awe_renderbuffer *mRenderBuffer;

	awe_webview* mWebView;

	Rectf mWebPageRect;

	Vec2i mWebPageSize;

	bool mDragging;
	float percentageX;
	float percentageY;

	float Dx1px;
	float Dy1py;
	float Dx2px;
	float Dy2py;

	bool mWebPage1Dragged;

	Font mDebuggingFont;
};

void AwesomiumTestAppApp::setup()
{
	mDebuggingFont = Font( "Arial", 30.0f );


	mWebPageSize = Vec2i( 800, 600 );
	mWebPageRect.set( 0, 0, mWebPageSize.x, mWebPageSize.y );

	mDragging = false;

	initAwesomium();
	loadWebPage("http://www.youtube.com");

	mWebPage1Dragged = false;
	gl::disableVerticalSync();
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
	
	string _fps = boost::lexical_cast<string,float>( getAverageFps() );
	gl::drawString( "FPS: " + _fps,
					Vec2f( 0.0f, 0.0f ), 
					Color::white(),
					mDebuggingFont );
	
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


void AwesomiumTestAppApp::updateWebPage()
{
	awe_webcore_update();

	if ( mRenderBuffer )
		mRenderBuffer = awe_webview_render( mWebView );
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

void AwesomiumTestAppApp::prepareSettings( Settings *settings )
{
	settings->setFrameRate( 400.0f );
}






CINDER_APP_BASIC( AwesomiumTestAppApp, RendererGl )
