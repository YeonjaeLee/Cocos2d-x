#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

// 그림 크기에 맞춰 깨지지 않게 화면 크기 지정
static cocos2d::Size designResolutionSize = cocos2d::Size(720, 1280);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// 아이폰 개발할 때 나왔던 마지막 화면 나갈때 처리 방식
bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview) {
		// 화면 크기 바꾸려면
		glview = GLViewImpl::createWithRect("ResolutionEx", Rect(0, 0, 320, 480));
		// 화면 맞춰서 실제 사용시
		//		glview = GLViewImpl::create("ResolutionEx");

		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(true);

	// 자연스러운 게임 위해 프레임 지정 필요
	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	// 실제 화면 사이즈 정해주기
	glview->setDesignResolutionSize(designResolutionSize.width,
		designResolutionSize.height,
		ResolutionPolicy::NO_BORDER);

	// create a scene. it's an autorelease object
	auto scene = HelloWorld::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be paused
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
