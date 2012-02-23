#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LibraryExampleAppApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void LibraryExampleAppApp::setup()
{
}

void LibraryExampleAppApp::mouseDown( MouseEvent event )
{
}

void LibraryExampleAppApp::update()
{
}

void LibraryExampleAppApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( LibraryExampleAppApp, RendererGl )
