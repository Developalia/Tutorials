#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    scene->getPhysicsWorld()->setGravity(Vect(0,-98));
    scene->getPhysicsWorld()->setSubsteps(24);
    
    // 'layer' is an autorelease object
    auto layer = MainScene::createWithPhysicsWorld(scene->getPhysicsWorld());
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
MainScene* MainScene::createWithPhysicsWorld(cocos2d::PhysicsWorld* w)
{
    auto hw = new MainScene();
    if(hw && hw->initWithPhysicsWorld(w))
    {
        hw->autorelease();
    }
    else
    {
        delete hw;
        hw = 0;
    }
    return hw;
}

// on "init" you need to initialize your instance
bool MainScene::initWithPhysicsWorld(cocos2d::PhysicsWorld *sceneWorld)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    // We need to set GameLayer position according to left-top point
    this->setAnchorPoint(Vec2(0, 0));
    
    
    CSLoader* instance = CSLoader::getInstance();
    
    rootNode = CSLoader::createNode("MainScene.csb");
    
    mainSceneTimeline = CSLoader::createTimeline("res/MainScene.csb");
    mainSceneTimeline->retain(); //released later on
    
    auto edgeBody = PhysicsBody::createEdgeBox( rootNode->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( rootNode->getContentSize().width / 2 + origin.x, rootNode->getContentSize().height / 2 + origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    rootNode->addChild( edgeNode );
    
    addChild(rootNode);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_2(MainScene::onContactPreSolve, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(MainScene::onContactSeparate, this);
    contactListener->onContactPostSolve = CC_CALLBACK_2(MainScene::onContactPostSolve, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    
    this->scheduleUpdate();
    
    return true;
}




bool MainScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    //Normally nodeA always should be Hero
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    //CCLOG("NODE A %s",nodeA->getName().c_str());
    //CCLOG("NODE B %s",nodeB->getName().c_str());
    
    
    return true;
}
bool MainScene::onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve){
    
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    
    return true;
}


void MainScene::onContactPostSolve(cocos2d::PhysicsContact& contact, const PhysicsContactPostSolve& solve){
    
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
}
void MainScene::onContactSeparate(cocos2d::PhysicsContact &contact){
    
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
}

void MainScene::update(float dt){}

void MainScene::onExit()
{
    // release the retain we called in init
    
    mainSceneTimeline->release();
    
    Layer::onExit();
}