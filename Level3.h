
#ifndef __LEVEL_3_H__
#define __LEVEL_3_H__

#include "cocos2d.h"

class Level3 : public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Level3);

private:
    cocos2d::PhysicsWorld* sceneWorld;

    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
};

#endif // __GAME_OVER_SCENE_H__