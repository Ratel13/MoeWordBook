#include "HelloWorldScene.h"
#include "cocos-ext.h"
#include "PersonalApi.h"


USING_NS_CC;
using namespace cocos2d::extension;
using namespace std;
using namespace network;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    
    //正则例子 匹配出所有www开头com结尾的链接
    //例子一
    string originStr1("<Http>www.cocos.org</Http>");
    log("%s",originStr1.c_str());
    
    const regex pattern1("www.+com");//这个是匹配表达式。注意.+是匹配原字符 .代表任意自负 ＋代表匹配任意多次。不懂可以去看看正则表达式原字符
    
    printRegexResult(originStr1,pattern1);
    
    //例子二
    string originStr2("<Http>www.cocos.org</Http>\
                     <Http>www.baidu.com</Http>\
                     <image>pic.png</image>\
                     <Http>www.google.com</Http>\
                     <Music>MySond.mp3<Music>");
    log("%s",originStr2.c_str());
    
    const regex pattern2("www[^(www)]+?com");
    
    printRegexResult(originStr2,pattern2);
    

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    getChineseAndPhoneticRequest("apple");
}

void HelloWorld::printRegexResult(string word,regex pattern)
{
    std::smatch result;
    
    bool match = std::regex_search(word, result, pattern);
    
    if(match)
    {
        for(size_t i = 0; i < result.size(); i++)
        {
            string convertStr(result[i]);
            log("result=%s",convertStr.c_str());
        }
    }
}

void HelloWorld::getChineseAndPhoneticRequest(string word)
{
    HttpRequest* request = new HttpRequest();
    string worklink = "http://dict.youdao.com/search?q="+word+"&keyfrom=fanyi.smartResult";
    
    request->setUrl(worklink.c_str());//识别单词意思，英标
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(this, httpresponse_selector(HelloWorld::onHttpRequestCompleted1));
    request->setTag("GET test1");
    HttpClient::getInstance()->send(request);
    request->release();
}
void HelloWorld::onHttpRequestCompleted1(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }
    
    int statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("statusString: %s", statusString);
    log("response code: %d", statusCode);
    
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    
    // dump data
    
    vector<char> *buffer = response->getResponseData();
    string resultStr;
    printf("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        //printf("%c", (*buffer)[i]);
        resultStr = resultStr+(*buffer)[i];
    }
    log("%s",resultStr.c_str());

}
