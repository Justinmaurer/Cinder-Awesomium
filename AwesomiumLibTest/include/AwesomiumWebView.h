#pragma once

#include "cinder/Vector.h"
#include "cinder/Rect.h"
#include "cinder/Surface.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"

#include <Awesomium/awesomium_capi.h>

class AwesomiumWebView {
	public:
		AwesomiumWebView	( );
		AwesomiumWebView	( int _width, int _height, bool _viewSource );
		awe_webview*		getWebView();
		int					getId();
		ci::Vec2f			getSize();
		void				setWidth( float _width );
		void				setHeight( float _height );
		ci::Rectf			getRectf( );
		void				setRect( ci::Rectf & _rect );
		ci::Surface			getSurface();

		void				loadURL( const std::string & _url );
		void				createSurface( bool _createSurface );
		bool				isCreatingSurface( );

		void				injectChar( ci::app::KeyEvent event );
		void				mouseDown( ci::app::MouseEvent event );
		void				mouseUp( ci::app::MouseEvent event );
		void				mouseDrag( ci::app::MouseEvent event );
		void				mouseMove( ci::app::MouseEvent event );
		
		void				renderSurface();
		void				create();	//creates the webview aka setup

		void				update();
		void				draw();
		
		bool static mDragging;

	private:
		bool						mViewSource;
		bool						mDragged;
		int							mId;
		ci::Vec2f					mSize;
		ci::Rectf					mRect;
		ci::Surface					mSurface;
		awe_webview*				mWebView;
		const awe_renderbuffer*		mRenderBuffer;
		bool						mCreateSurface;

		float						mDx1px;
		float						mDy1py;
		float						mDx2px;
		float						mDy2py;
};