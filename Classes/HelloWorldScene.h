#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "HttpClient.h"
#include <regex>

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void printRegexResult(std::string word,std::regex pattern);
    
    void getChineseAndPhoneticRequest(std::string word);
    void onHttpRequestCompleted1(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};

#endif // __HELLOWORLD_SCENE_H__
