#Multi-resolution adaptation fully resolution

###Overview

Since Cocos2d-x 2.04 released, Cocos2d-x introduced a set of resolutions for multi-resolution. It also deprecated some APIs about Retina and proposed a concept - design resolution.

There are some APIs as below:
```
CCEGLView::sharedOpenGLView()->setDesignResolutionSize()      //design resolution size and mode
CCDirector::sharedDirector()->setContentScaleFactor()         //content scale factor
CCFileUtils::sharedFileUtils()->setResourceDirectory()        //deprecated
CCFileUtils::sharedFileUtils()->setSearchPaths()              //resource search path
CCEGLView::sharedOpenGLView()->getFrameSize()                 //screen resolution
CCDirector::sharedDirector()->getWinSize()                    //design resolution
CCDirector::sharedDirector()->getVisibleSize()                //design resolution’s visable area size
CCDirector::sharedDirector()->getVisibleOrigin()              //origin of the visable area of design resolution
```
Since cocos2d-2.1beta3-x-2.1.1, ```CCFileUtils::sharedFileUtils()->setResourceDirectory() ``` has been replaced by ```CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath)```.



From Cocos2d-x 2.13 two new resolution policy - kResolutionFixedHeight and kResolutionFixedWidth, added to the engine. So there are five policy for multi-resolution now.

Two articles - [Multi_resolution_support](http://www.cocos2d-x.org/projects/Cocos2d-x/wiki/Multi_resolution_support) and [Mechanism_of_loading_resources](http://www.cocos2d-x.org/projects/Cocos2d-x/wiki/Mechanism_of_loading_resources), 
in official site give presentation about multi-resolution.

But this article focus on the Cocos2d-x multi-resolution technique from the perspective of engine user, which will give you a fully understanding of how to deal with multi-resolution 
with Cocos2d-x.

###Switch from Retina resolution to design resolution

Before Cocos2d-x 2.04, Retina is a resolution concept comes from Cocos2d-iPhone. To support Retina iPhone, Cocos2d-iPhone use -hd extension to distinct normal iPhone resources and Retina 
iPhone resources. When desinging the game, we actually use point coordinate instead of pixel coordinate. This kind of point as same as the concept of the native - that is you don't have to 
change your code and you can run yuor App on retina iPhone that used run on normal iPhone. Only the picture are vague, but once import the picture with @2x extension
