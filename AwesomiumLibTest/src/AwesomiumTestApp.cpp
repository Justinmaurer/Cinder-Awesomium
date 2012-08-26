#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "boost/lexical_cast.hpp"

#include "AwesomiumManager.h"

using namespace ci;
using namespace ci::gl;
using namespace ci::app;
using namespace std;

class AwesomiumTestAppApp : public AppBasic {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();

	void initAwesomium();

	void mouseDown( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void mouseUp( MouseEvent event );

	void keyDown(  KeyEvent event );
	void injectChar( KeyEvent event );

	Font mDebuggingFont;


	AwesomiumWebView mAwesomiumWebView;
};

void AwesomiumTestAppApp::prepareSettings( Settings *settings )
{
	settings->setFrameRate( 400.0f );
}

void AwesomiumTestAppApp::setup()
{
	mDebuggingFont = Font( "Arial", 30.0f );


	initAwesomium();

	gl::disableVerticalSync();

	mAwesomiumWebView = AwesomiumWebView();
	mAwesomiumWebView.create();
	mAwesomiumWebView.loadURL( "http://www.google.com" );
}

void AwesomiumTestAppApp::keyDown( KeyEvent event )
{
	mAwesomiumWebView.injectChar( event );
}

void AwesomiumTestAppApp::mouseUp( MouseEvent event )
{
	mAwesomiumWebView.mouseUp( event );
}

void AwesomiumTestAppApp::mouseDrag( MouseEvent event )
{
	mAwesomiumWebView.mouseDrag( event );
}
void AwesomiumTestAppApp::update()
{
	mAwesomiumWebView.update();
	awe_webcore_update();
}

void AwesomiumTestAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 

	mAwesomiumWebView.draw();
	
	string _fps = boost::lexical_cast<string,float>( getAverageFps() );
	gl::drawString( "FPS: " + _fps,
					Vec2f( 0.0f, 0.0f ), 
					Color::white(),
					mDebuggingFont );
	
}


void AwesomiumTestAppApp::initAwesomium()
{
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
}

void AwesomiumTestAppApp::mouseDown( MouseEvent event )
{
	mAwesomiumWebView.mouseDown( event );
}

void AwesomiumTestAppApp::mouseMove( MouseEvent event )
{
	mAwesomiumWebView.mouseMove( event );
}






CINDER_APP_BASIC( AwesomiumTestAppApp, RendererGl )
