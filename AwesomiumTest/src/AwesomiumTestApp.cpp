#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
};

void AwesomiumTestAppApp::setup()
{
	// Create our WebCore singleton with the default options
	awe_webcore_initialize_default();

	// Create a new WebView instance with a certain width and height, using the 
	// WebCore we just created
	awe_webview* webView = awe_webcore_create_webview(WIDTH, HEIGHT, false);

	// Create our URL string
	awe_string* url_str = awe_string_create_from_ascii(URL, strlen(URL));

	// Load a certain URL into our WebView instance
	awe_webview_load_url(webView, url_str, awe_string_empty(), 
		awe_string_empty(), awe_string_empty());

	// Destroy our URL string
	awe_string_destroy(url_str);

	console() <<  "Page is now loading..." << std::endl;;

	// Wait for our WebView to finish loading
	while(awe_webview_is_loading_page(webView))
	{
		Sleep(SLEEP_MS);
		// We must call WebCore::update in our update loop.
		awe_webcore_update();
	}

	console() << "Page has finished loading." << std::endl;

	// Get our rendered buffer from our WebView. All actual rendering takes 
	// place in our WebView sub-process which passes the rendered data to our 
	// main process during each call to WebCore::update.
	const awe_renderbuffer* renderBuffer = awe_webview_render(webView);

	// Make sure our render buffer is not NULL-- WebView::render will return
	// NULL if the WebView process has crashed.
	if(renderBuffer != NULL)
	{
		// Create our filename string
		awe_string* filename_str = awe_string_create_from_ascii("./result.jpg", 
			strlen("./result.jpg"));

		// Save our RenderBuffer directly to a JPEG image
		awe_renderbuffer_save_to_jpeg(renderBuffer, filename_str, 90);

		// Destroy our filename string
		awe_string_destroy(filename_str);

		std::cout << "Saved a render of the page to 'result.jpg'." << std::endl;

				// Open up the saved JPEG
		#if defined(__WIN32__) || defined(_WIN32)
				system("start result.jpg");
		#endif
	}

}

void AwesomiumTestAppApp::mouseDown( MouseEvent event )
{
}

void AwesomiumTestAppApp::update()
{
}

void AwesomiumTestAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( AwesomiumTestAppApp, RendererGl )
