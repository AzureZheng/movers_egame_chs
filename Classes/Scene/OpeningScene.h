/****************************************
开场界面
2016-01-28 by Azure Zheng
*****************************************/

#ifndef __OPENING_SCENE_H__
#define __OPENING_SCENE_H__

#include "cocos2d.h"

class OpeningScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(OpeningScene);

	//显示开场动画
	void showOpeningAnim();

	//预加载资源
	void preloadRes();

	//关闭开场动画
	void closeOpeningAnim();

	//切换到下一场景
	void enterNextScene();

	//监控流程
	virtual void update(float dt);

	//流程计数加1
	void countProgressIndex();

	//单项预加载资源完成回调(method: 0.普通加载；1.最后一次加载)(plistPath：同时加载plist，或不加载)
	void preloadResCallback(cocos2d::Texture2D * tex,const std::string & plistPath);

	//预载音乐
	void preloadSound();

	//结束时移除资源
	virtual void onExit();

	//获取音效是否加载完毕
	static bool isEffectLoadFinished();

	//设置音效加载完毕
	static void effectLoadFinished();

protected:

	//开场动画层
	cocos2d::Layer * m_openingAnimLayer;

	//屏幕大小
	cocos2d::Size m_visibleSize;

	//流程计数
	int m_progressIndex;

	//流程等待
	bool m_progressWait;

	//资源加载计数
	int m_resPreloadCount;

	//资源总数
	int m_resPreloadTotalCount;

	//音效加载完毕
	static bool m_effectLoadFinished;
};

#endif
