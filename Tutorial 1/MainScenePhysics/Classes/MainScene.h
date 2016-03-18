#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio::timeline;
using namespace cocos2d::ui;
using namespace cocos2d;

class MainScene : public cocos2d::Layer
{
public:
    
    MainScene():
    _tag(0) {};
    
    virtual bool initWithPhysicsWorld(cocos2d::PhysicsWorld* pw);
    static MainScene* createWithPhysicsWorld(cocos2d::PhysicsWorld* w);
    cocos2d::PhysicsWorld *sceneWorld;
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    cocos2d::Vec2 trevorPosition;
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 visible;
    cocos2d::Vec2 origin;
    
    void update (float dt) override;
    void onExit() override;
    
    
private:
    
    
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    bool onContactPreSolve(PhysicsContact& contact, PhysicsContactPreSolve& solve);
    void onContactSeparate(cocos2d::PhysicsContact &contact);
    void onContactPostSolve(cocos2d::PhysicsContact& contact, const PhysicsContactPostSolve& solve);
    
    int _tag;
    
    cocos2d::Node *rootNode;
    
protected:
    
    cocostudio::timeline::ActionTimeline *mainSceneTimeline;
};

#endif // __MAIN_SCENE_H__