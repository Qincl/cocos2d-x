
#include "cocos-ext.h"
#include "../ExtensionsTest.h"
#include "SceneEditorTest.h"

using namespace cocos2d;
using namespace cocos2d::extension;

SceneEditorTestLayer::~SceneEditorTestLayer()
{
	
}

SceneEditorTestLayer::SceneEditorTestLayer()
{
	_curNode = NULL;
}

Scene* SceneEditorTestLayer::scene()
{
	Scene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = Scene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		SceneEditorTestLayer *layer = SceneEditorTestLayer::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SceneEditorTestLayer::init()
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(! LayerColor::initWithColor(Color4B(0,0,0,255)));
        
        Node *root = createGameScene();
        CC_BREAK_IF(!root);
        this->addChild(root, 0, 1);

		bRet = true;
	} while (0);

	return bRet;
}

cocos2d::Node* SceneEditorTestLayer::createGameScene()
{
    Node *pNode = SceneReader::getInstance()->createNodeWithSceneFile("scenetest/FishJoy2.json");
	if (pNode == NULL)
	{
		return NULL;
	}
	_curNode = pNode;

	//fishes
	/*cocos2d::extension::armature::Armature *pBlowFish = getFish(10008, "blowFish");
	cocos2d::extension::armature::Armature *pButterFlyFish = getFish(10009, "butterFlyFish");
	pBlowFish->getAnimation()->playByIndex(0);
	pButterFlyFish->getAnimation()->playByIndex(0);*/
   
    MenuItemFont *itemBack = MenuItemFont::create("Back", CC_CALLBACK_1(SceneEditorTestLayer::toExtensionsMainLayer, this));
        itemBack->setColor(Color3B(255, 255, 255));
        itemBack->setPosition(Point(VisibleRect::rightBottom().x - 50, VisibleRect::rightBottom().y + 25));
        Menu *menuBack = Menu::create(itemBack, NULL);
        menuBack->setPosition(Point(0.0f, 0.0f));
		menuBack->setZOrder(4);

    pNode->addChild(menuBack);
    
	//ui action
	//cocos2d::extension::UIActionManager::shareManager()->PlayActionByName("startMenu_1.json","Animation1");

    return pNode;
}

void SceneEditorTestLayer::toExtensionsMainLayer(cocos2d::Object *sender)
{
    ComAudio *pBackMusic = (ComAudio*)(_curNode->getComponent("CCBackgroundAudio"));
    pBackMusic->stopBackgroundMusic();
	ExtensionsTestScene *pScene = new ExtensionsTestScene();
	pScene->runThisTest();
	pScene->release();
}  


cocos2d::extension::armature::Armature* SceneEditorTestLayer::getFish(int nTag, const char *pszName)
{
	if (_curNode == NULL)
	{
		return NULL;
	}
	ComRender *pFishRender = (ComRender*)(_curNode->getChildByTag(nTag)->getComponent(pszName));
	return (cocos2d::extension::armature::Armature *)(pFishRender->getNode());
}

void runSceneEditorTestLayer()
{
    Scene *pScene = SceneEditorTestLayer::scene();
    Director::getInstance()->replaceScene(pScene);
}
