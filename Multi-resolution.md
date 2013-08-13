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
change your code and you can run yuor App on retina iPhone that used run on normal iPhone. Only the picture are vague, but once import the picture with @2x extension iOS will load high definition 
resources automatically to support retina display.

Using point coordinate can solve multi-resolution in some degree, however, as iPhone5 and New iPad released there are five set of resources you need to prepare if you want to fit every kind of iOS devive and it's very annoying.
But point coordinate can not solve the problem and the situation is worse in Android platform.

Design resoltion concept is supposed to evolve from point coordinate, which aims block the screen resolution. Locate the spires on design resolution and then implement it is not easy. Cocos2d-x provide a set of relative APIs and five
multi-resolution strategies but which kind of strategy is what we really need. Let's explore it together!

###Resource resolution, Design resolution and Screen resolution

Resources width refered to RW, Resources heitht refered to RH

Design width refered to DW, Design height refered to DW

Screen width refered to SW, Screen height refered to SH

In SKD samples there is a HelloCpp project. And it shows us how to use multi-resolution strategy.

Next we take a horizontal screen game as example, which has the same fundamental configuration, but exchange the width and the height.

Cocos2d-x has the following two logical processes to display picture.

From resource resolution to design resolution, then from design resolution to screen resolution.

As following picture:

![](resources/pc1.png)

API ```setContentScaleFactor()``` and ```setSearchPaths()``` control the first conversion process. However, ```setDesignResolutionSize()``` 
controls the second conversion process. The final display effect depended on these two processes.

###Switch from resource resolution to design resolution

```setSearchPaths()``` should make appropriate settings via the screen resolution, the HellowCpp show us a simple soltion but it may not the best.

```setContentScaleFactor()``` decide the factor of the picture that displays in screen. But this the parameters of this API is not according to the
wide ratio of recource and screen or height ratio of recource and screen. The design of Cocos2d-x engine is trying to prevent developers focus on screen 
directly, so the factor is wide ratio of resource and screen or height ratio of resource and screen.

```setContentScaleFactor()``` usually has two ways to set parameter. RH/DH or RW/DW different factor has different degree of nagtive effect.

Look the picture below:

![](resources/pc2.png)
