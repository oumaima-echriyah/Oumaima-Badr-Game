/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include"Level1.h"
#include"HelloWorldScene.h"
#include"Level2.h"
#include"Levels.h"
USING_NS_CC;

Scene* Level1::createScene()
{
  auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    // 'layer' is an autorelease object
    auto layer = Level1::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool Level1::init()
{
    if (!Scene::init()) {
        return false;
    }
    Size visiblesize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //partie background

    auto mysprite = Sprite::create("level1bac.png");
   mysprite->setPosition(Point((visiblesize.width / 2) + origin.x, (visiblesize.height / 2 + origin.y)));
    mysprite->setScale(0.8, 0.8);
    this->addChild(mysprite);

//-------------------------------------------------------------------
    //partie player

    auto character = Sprite::create("character.png");
    auto action = Place::create(Point(100, 100));
    character->runAction(action);
    // physic aspect 
    auto characterBody = PhysicsBody::createBox(character->getContentSize(), PhysicsMaterial(0, 2, 0));
    character->setPhysicsBody(characterBody);
    characterBody->setDynamic(false);
    this->addChild(character);
    // for the collision part 
    character->setTag(1);
    characterBody->setCollisionBitmask(1);
    characterBody->setCategoryBitmask(1);
    characterBody->setContactTestBitmask(1);
    
//--------------------------------------------------------------------------
// the door object
    auto door = Sprite::create("door.png");    
    auto action1 = Place::create(Point(1150, 110));
    door->runAction(action1);
    // physic aspect 
    auto doorBody = PhysicsBody::createBox(door->getContentSize(), PhysicsMaterial(0, 2, 0));
    door->setPhysicsBody(doorBody);
    doorBody->setDynamic(false);
    this->addChild(door);
    // for thr collision part 3
    door->setTag(3);
    doorBody->setCollisionBitmask(3);
    doorBody->setCategoryBitmask(3);
    doorBody->setContactTestBitmask(3);


   //---------------------------------------------------------------------------
    // obstacle1 
    auto obstacle1 = Sprite::create("obstacle11.png");
    auto action2 = Place::create(Point(600, 110));
    obstacle1->runAction(action2);
    // physic aspect 
    auto obstacle1Body = PhysicsBody::createBox(obstacle1->getContentSize(), PhysicsMaterial(0, 2, 0));
    obstacle1->setPhysicsBody(obstacle1Body);
    obstacle1Body->setDynamic(false);
    this->addChild(obstacle1);
    // for thr collision part 3
    obstacle1->setTag(4);
    obstacle1Body->setCollisionBitmask(4);
    obstacle1Body->setCategoryBitmask(4);
    obstacle1Body->setContactTestBitmask(4);

//----------------------------------------------------------------
    //keyborad movement
    auto eventListener = EventListenerKeyboard::create();
   
    eventListener->onKeyReleased = [character](EventKeyboard::KeyCode keyCode, Event* event) {

        if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            // sequence d'actions 
            auto jump = JumpBy::create(0.7f, Vec2(80, 50), 60.0f, 1);
           
            auto moveBy = MoveBy::create(0.8, Vec2(0, -50));
            auto seq = Sequence::create(jump,moveBy, nullptr);

            // run it
            character->runAction(seq);

        }
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            // Move sprite to position to right in 2 seconds.
            auto moveBy = MoveBy::create(2, Vec2(30,0));
                character->runAction(moveBy);
           
        }
        if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            // Move sprite to position left in 2 seconds.
            auto moveBy = MoveBy::create(2, Vec2(-20, 0));
            character->runAction(moveBy);
          

        }
    };
   
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    

    // add an event listener for contcat events 
  
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [character](PhysicsContact& contact) {


        PhysicsBody* x = contact.getShapeA()->getBody();
        PhysicsBody* y = contact.getShapeB()->getBody();
       

        if (1 == x->getCollisionBitmask() && 3 == y->getCollisionBitmask() || 3 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

            auto scene = Level2::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, scene));
            
        }

        if (1 == x->getCollisionBitmask() &&4== y->getCollisionBitmask() ||4 == x->getCollisionBitmask() && 1 == y->getCollisionBitmask()) {

            auto scene = Level2::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, scene));

        }
     


        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}


 

