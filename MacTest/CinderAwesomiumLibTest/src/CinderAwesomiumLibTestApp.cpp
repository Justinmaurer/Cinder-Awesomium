#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "AwesomiumManager.h"
#include "AwesomiumWebView.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CinderAwesomiumLibTestApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    AwesomiumManager mAwesomiumManager;
    AwesomiumWebView myWebView;
    
    
};

void CinderAwesomiumLibTestApp::setup()
{
   // mAwesomiumManager = AwesomiumManager( );
	/*true, 
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
		awe_string_empty() */

	mAwesomiumManager = AwesomiumManager(true,
										true,
										true,
										"",
										"",
										"",
										"",
										"",
										AWE_LL_NORMAL,
										false,
										"",
										"",
										"",
										"",
										"",
										"",
										"",
										"",
										true,
										6000,
										false,
										false,
										"");

    myWebView = AwesomiumWebView();
    
}

void CinderAwesomiumLibTestApp::mouseDown( MouseEvent event )
{
}

void CinderAwesomiumLibTestApp::update()
{
   // mAwesomiumManager.getAwesomiumWebView(0).update();
   // mAwesomiumManager.getAwesomiumWebView(0).update();
}

void CinderAwesomiumLibTestApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
 
    
}


CINDER_APP_BASIC( CinderAwesomiumLibTestApp, RendererGl )
