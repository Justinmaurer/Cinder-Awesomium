#include "AwesomiumWebView.h"


AwesomiumWebView::AwesomiumWebView( ){
    
    mSize = Vec2f(1024, 768);
    mRect.set( 0, 0, mSize.x, mSize.y );
    
    mViewPtr = awe_webcore_create_webview(mSize.x, mSize.y,	false);
    
}

void AwesomiumWebView::loadURL(const std::string &_url){
    // Create our URL string
	awe_string* url_str = awe_string_create_from_ascii(_url.c_str(),
                                                       strlen(_url.c_str() ) );
    
	// Load the URL into our WebView instance
	awe_webview_load_url(mViewPtr,
                         url_str,
                         awe_string_empty(),
                         awe_string_empty(),
                         awe_string_empty());
    
	// Destroy our URL string
	awe_string_destroy(url_str);
    
	// Wait for WebView to finish loading the page
	while(awe_webview_is_loading_page(mViewPtr))
		awe_webcore_update();
    
	mRenderBuffer = awe_webview_render( mViewPtr );
}

void AwesomiumWebView::update(){
    awe_webcore_update();
    
	if ( mRenderBuffer )
		mRenderBuffer = awe_webview_render( mViewPtr );
}

void AwesomiumWebView::draw(){
   	if(mRenderBuffer)
	{
		uint8_t *data = (uint8_t *) awe_renderbuffer_get_buffer(mRenderBuffer);
        
		mSurface = Surface(data, mSize.x, mSize.y, 3, SurfaceChannelOrder::BGRA );
		Texture texture = Texture( mSurface );
		gl::draw(texture, mRect);
	} 
}