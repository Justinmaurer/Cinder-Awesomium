#pragma once
#include <string>
#include "cinder/Vector.h"
#include "cinder/Rect.h"
#include "cinder/Surface.h"
#include "cinder/app/app.h"
#include "cinder/app/AppBasic.h"
#include <Awesomium/awesomium_capi.h>
#include "AwesomiumManager.h"


using namespace ci;
using namespace ci::gl;
//custom web view class which contains the official webview pointer(awe_webview*) used by awesomium along with additional

class AwesomiumWebView {
	public:
		AwesomiumWebView	( );
		awe_webview*		getWebView();
		int					getId();
		ci::Vec2f			getSize();
		void				setSize( ci::Vec2f & _size );
		ci::Rectf			getRectf( );
		void				setRect( ci::Rectf & _rect );

		void				loadURL( const std::string & _url );
		void				createSurface( bool _createSurface );
		bool				isCreatingSurface( );
        Surface             getSurface( );
        void                update();
        void                draw();

	private:
		int                     mId;
		ci::Vec2f               mSize;
		ci::Rectf               mRect;
		ci::Surface             mSurface;
		awe_webview*            mViewPtr;
        const awe_renderbuffer* mRenderBuffer;
		bool                    mCreateSurface;



};