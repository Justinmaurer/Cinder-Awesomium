#pragma once
#include <string>
#include "cinder/Vector.h"
#include "cinder/Rect.h"
#include "cinder/Surface.h"
#include <Awesomium/awesomium_capi.h>

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

	private:
		int				mId;
		ci::Vec2f		mSize;
		ci::Rectf		mRect;
		ci::Surface		mSurface;
		awe_webview*	mViewPtr;
		bool			mCreateSurface;



};