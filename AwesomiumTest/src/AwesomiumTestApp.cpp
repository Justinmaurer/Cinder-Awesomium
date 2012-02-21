#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
