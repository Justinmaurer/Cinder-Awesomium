#include "AwesomiumWebView.h"

bool AwesomiumWebView::mDragging = false;

ci::Surface AwesomiumWebView::getSurface()
{
	return mSurface;
}

AwesomiumWebView::AwesomiumWebView(  )
{
	//mWebView = awe_webcore_create_webview( 1024, 768, false );
	mSize = ci::Vec2i( 1024, 768 );
	mViewSource = false;
	mWebView = NULL;
	mRect = ci::Rectf( 0.0f, 0.0f, mSize.x, mSize.y );
	mDragging = false;
	mDragged = false;

	mDx1px = 0.0f;
	mDy1py = 0.0f;
	mDx2px = mSize.x;
	mDy2py = mSize.y;
}

AwesomiumWebView::AwesomiumWebView( int _width, int _height, bool _viewSource )
{
	//mWebView = awe_webcore_create_webview( _width, _height,	_viewSource );
	mSize = ci::Vec2i( _width, _height );
	mViewSource = _viewSource;
	mWebView = NULL;
	mRect = ci::Rectf( 0.0f, 0.0f, mSize.x, mSize.y );
	mDragging = false;
	mDragged = false;

	mDx1px = 0.0f;
	mDy1py = 0.0f;
	mDx2px = mSize.x;
	mDy2py = mSize.y;
}

void AwesomiumWebView::update()
{
	if ( mRenderBuffer )
		mRenderBuffer = awe_webview_render( mWebView );
}

void AwesomiumWebView::draw()
{
	if(mRenderBuffer)
	{
		uint8_t *data = (uint8_t *) awe_renderbuffer_get_buffer(mRenderBuffer);

		ci::Surface renderedSurface = ci::Surface(data, mSize.x, mSize.y,
											3, ci::SurfaceChannelOrder::BGRA );

		ci::gl::Texture texture = ci::gl::Texture( renderedSurface );

		ci::gl::draw(texture, mRect);

	}
}

void AwesomiumWebView::injectChar( ci::app::KeyEvent event )
{
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
}

void AwesomiumWebView::create()
{
	mWebView = awe_webcore_create_webview( mSize.x, mSize.y, mViewSource );
}

void AwesomiumWebView::loadURL( const std::string & _url )
{
	// Create our URL string
	awe_string* url_str = awe_string_create_from_ascii(_url.c_str(),
		strlen(_url.c_str() ) );

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

void AwesomiumWebView::mouseDrag( ci::app::MouseEvent event )
{
	if ( mRect.contains( event.getPos() ) ){

		mDragged = true;

		if ( !mDragging ){
			mDx1px = event.getPos().x - mRect.x1;
			mDy1py = event.getPos().y - mRect.y1;
			mDx2px = mRect.x2 - event.getPos().x;
			mDy2py = mRect.y2 - event.getPos().y;

			mDragging = true; //should be a static variable 
		}

		mRect.set( event.getPos().x - mDx1px, event.getPos().y - mDy1py, event.getPos().x + mDx2px, event.getPos().y + mDy2py);

	}
}

void AwesomiumWebView::mouseUp( ci::app::MouseEvent event )
{
	mDragging = false;

	ci::app::console() << "mouse up pos: " << event.getPos() << std::endl;
	awe_webview_inject_mouse_up(mWebView, AWE_MB_LEFT );
}

void AwesomiumWebView::mouseDown( ci::app::MouseEvent event )
{
	ci::app::console() << "mouse down pos: " << event.getPos() << std::endl;

	awe_webview_inject_mouse_down(mWebView, AWE_MB_LEFT);
}

void AwesomiumWebView::mouseMove( ci::app::MouseEvent event )
{

	ci::Vec2f _pos = ci::Vec2f( event.getPos().x - mRect.x1, event.getPos().y - mRect.y1);
	ci::app::console() << "mouse move pos: " << _pos << std::endl;
	awe_webview_inject_mouse_move (mWebView, event.getPos().x - mRect.x1, event.getPos().y - mRect.y1);
}


