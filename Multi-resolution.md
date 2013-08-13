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

But this article fucos on the Cocos2d-x multi-resolution technique from the perspective of engine user, which will give you a fully understanding of how to deal with multi-resolution 
with Cocos2d-x.

###From Retina resolution to 
