#pragma once
#include "Awesomium.h"
#include "cinder/gl/Texture.h"



class AwesomiumManager
{
	public:
	  AwesomiumManager();	//do init here with config
	  AwesomiumManager( int numOfViews );


	  int addView();
	  
	 // ci::gl::Texture* getTexture( int index );
	  int getViewCount();
	  Awesomium* getAwesomium( int index );

	  
	private:
	  int mViewCount;

};