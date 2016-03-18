#include "SpriteButton.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define SPRITE_BUTTON_ACTIVE_ACTION_TAG -68256
#define SPRITE_BUTTON_SCALE_ACTION_TAG -68255
#define PLAY_EFFECT( _effect_ ) CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( _effect_ )

//���û���״̬
bool SpriteButton::m_mutexStatus = false;

//Ĭ�ϰ�ť����
std::string SpriteButton::m_defaultSound = "";

//�����Ƴ�����֡�������
SpriteButton::~SpriteButton()
{
	if (m_normalSpriteFrame)
	{
		m_normalSpriteFrame->release();
	}

	if (m_pressSpriteFrame)
	{
		m_pressSpriteFrame->release();
	}

	if (m_disabledSpriteFrame)
	{
		m_disabledSpriteFrame->release();
	}

	if (m_normalSelectedSpriteFrame)
	{
		m_normalSelectedSpriteFrame->release();
	}

	if (m_pressSelectedSpriteFrame)
	{
		m_pressSelectedSpriteFrame->release();
	}

	if (m_disabledSelectedSpriteFrame)
	{
		m_disabledSelectedSpriteFrame->release();
	}

	if (m_touchListener)
	{
		m_touchListener->release();
	}
}


//������ʼ
bool SpriteButton::onTouchBegan(Touch * t, Event * e)
{
	if (!getParent()) return false;

	if (m_isEnabled == true && m_mutexStatus == false && (m_status == 0 || m_status == 3) && _isAncensterEnabled(this))
	{
		if ((!t) ||
			(t && getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation()))))
		{
			switchToPress();
			if (!m_sound.empty() && !m_isMute) PLAY_EFFECT(m_sound.c_str());
			m_touchBeganCallback(this);
			m_startToBeTouched = true;
			m_mutexStatus = true;
			return true;
		}
	}
	else if (m_isEnabled == false && _isAncensterEnabled(this))
	{
		if ((!t) ||
			(t && getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation()))))
		{
			m_disabledCallback(this);
		}
	}

	return false;
}


//�����ƶ�
void SpriteButton::onTouchMoved(Touch * t, Event * e)
{
	if (!getParent()) return;

	if (m_status == 0)
	{
		if (getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
		{
			switchToPress();
		}
	}
	else if (m_status == 1)
	{
		if (!getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation())))
		{
			switchToNormal();
		}
	}
}


//��������
void SpriteButton::onTouchEnded(Touch * t, Event * e)
{
	if (!getParent()) return;

	if (m_status == 3)
	{
		m_status = 0;
	}
	else if (m_status == 0 || m_status == 1)
	{
		if ((!t) ||
			(t && getBoundingBox().containsPoint(getParent()->convertToNodeSpace(t->getLocation()))))
		{
			m_callback(this);
		}
		switchToNormal();
	}

	m_startToBeTouched = false;
	m_mutexStatus = false;
}


//����ȡ��
void SpriteButton::onTouchCanceled(Touch * t, Event * e)
{
	onTouchEnded(t, e);
}



//��������������
void SpriteButton::_setupTouchListener()
{
	m_touchListener = EventListenerTouchOneByOne::create();
	m_touchListener->retain();

	m_touchListener->setSwallowTouches(true);
	m_touchListener->onTouchBegan = std::bind(&SpriteButton::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);

	m_touchListener->onTouchMoved = std::bind(&SpriteButton::onTouchMoved, this, std::placeholders::_1, std::placeholders::_2);

	m_touchListener->onTouchEnded = std::bind(&SpriteButton::onTouchEnded, this, std::placeholders::_1, std::placeholders::_2);

	m_touchListener->onTouchCancelled = std::bind(&SpriteButton::onTouchCanceled, this, std::placeholders::_1, std::placeholders::_2);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(m_touchListener, this);
}


//���ô�������
void SpriteButton::setSwallowTouches(bool needSwallow)
{
	m_touchListener->setSwallowTouches(needSwallow);
}

//��ʼ��
bool SpriteButton::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	m_normalSpriteFrame = nullptr;

	m_pressSpriteFrame = nullptr;

	m_disabledSpriteFrame = nullptr;

	m_normalSelectedSpriteFrame = nullptr;

	m_pressSelectedSpriteFrame = nullptr;

	m_disabledSelectedSpriteFrame = nullptr;

	m_status = 0;

	m_isEnabled = false;

	m_scaledRateX = 0;

	m_scaledRateY = 0;

	m_startToBeTouched = false;

	m_isSelected = false;

	m_isBright = true;

	m_isMute = false;

	m_scaleDiff = 0.1f;

	m_callback = [](Ref*){};
	m_touchBeganCallback = [](Ref*){};
	m_disabledCallback = [](Ref*){};

	_setupTouchListener();

	setEnabled(true);

	//���ð�ť����
	m_sound = m_defaultSound;

	return true;
}



//����������ʵ��
SpriteButton * SpriteButton::create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName, const std::string & disabledSpriteFrameName)
{
	auto spb = create();

	auto sfc = SpriteFrameCache::getInstance();

	spb->setNormalSpriteFrame(sfc->getSpriteFrameByName(normalSpriteFrameName));
	spb->setPressSpriteFrame(sfc->getSpriteFrameByName(pressSpriteFrameName));
	spb->setDisabledSpriteFrame(sfc->getSpriteFrameByName(disabledSpriteFrameName));

	spb->setNormalSpriteFrame(sfc->getSpriteFrameByName(normalSpriteFrameName), true);
	spb->setPressSpriteFrame(sfc->getSpriteFrameByName(pressSpriteFrameName), true);
	spb->setDisabledSpriteFrame(sfc->getSpriteFrameByName(disabledSpriteFrameName), true);

	return spb;
}


SpriteButton * SpriteButton::create(cocos2d::SpriteFrame * normalSpriteFrame, cocos2d::SpriteFrame * pressSpriteFrame, cocos2d::SpriteFrame * disabledSpriteFrame)
{
	auto spb = create();

	spb->setNormalSpriteFrame(normalSpriteFrame);
	spb->setPressSpriteFrame(pressSpriteFrame);
	spb->setDisabledSpriteFrame(disabledSpriteFrame);

	spb->setNormalSpriteFrame(normalSpriteFrame, true);
	spb->setPressSpriteFrame(pressSpriteFrame, true);
	spb->setDisabledSpriteFrame(disabledSpriteFrame, true);

	return spb;
}


//ת��������״̬
void SpriteButton::switchToNormal()
{
	m_status = 0;

	if (m_isSelected ? m_normalSelectedSpriteFrame : m_normalSpriteFrame)
	{
		setSpriteFrame(m_isSelected ? m_normalSelectedSpriteFrame : m_normalSpriteFrame);
	}
	else
	{
		setTexture(nullptr);
	}

	if (m_scaledRateX != 0 && m_scaledRateY != 0)
	{
		setScale(m_scaledRateX, m_scaledRateY);
	}
}



//ת��������״̬
void SpriteButton::switchToPress()
{
	m_status = 1;

	if (m_isSelected ? m_pressSelectedSpriteFrame : m_pressSpriteFrame)
	{
		setSpriteFrame(m_isSelected ? m_pressSelectedSpriteFrame : m_pressSpriteFrame);
	}
	else
	{
		m_scaledRateX = getScaleX();
		m_scaledRateY = getScaleY();

		setScale(m_scaledRateX + m_scaleDiff, m_scaledRateY + m_scaleDiff);
	}
}


//ת��������״̬
void SpriteButton::switchToDisabled()
{
	m_status = 2;
	if (!m_isBright && (m_isSelected ? m_disabledSelectedSpriteFrame : m_disabledSpriteFrame))
	{
		setSpriteFrame(m_isSelected ? m_disabledSelectedSpriteFrame : m_disabledSpriteFrame);
	}
}



//���ÿ���״̬
void SpriteButton::setEnabled(bool enabled)
{
	if (enabled)
	{
		if (m_isEnabled) return;
		m_isEnabled = true;
		switchToNormal();
	}
	else
	{
		if (!m_isEnabled) return;
		m_isEnabled = false;
		switchToDisabled();
	}
}



//���ؿ���״̬
bool SpriteButton::isEnabled()
{
	return m_isEnabled;
}



//���ûص�����
void SpriteButton::setCallback(const std::function<void(cocos2d::Ref*)> callback)
{
	m_callback = callback;
}



//���ػص�����
const std::function<void(cocos2d::Ref*)> & SpriteButton::getCallback() const
{
	return m_callback;
}



//��������״̬����֡
void SpriteButton::setNormalSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus)
{
	auto & sfs = isSelectStatus ? m_normalSelectedSpriteFrame : m_normalSpriteFrame;

	if (sfs)
	{
		sfs->release();
		sfs = nullptr;
	}

	if (sf)
	{
		sfs = sf;
		sfs->retain();
	}

	if (m_status == 0)
	{
		switchToNormal();
	}
}



//���ð���״̬����֡
void SpriteButton::setPressSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus)
{
	auto & sfs = isSelectStatus ? m_pressSelectedSpriteFrame : m_pressSpriteFrame;

	if (sfs)
	{
		sfs->release();
		sfs = nullptr;
	}

	if (sf)
	{
		sfs = sf;
		sfs->retain();
	}

	if (m_status == 1)
	{
		switchToPress();
	}
}



//���ý���״̬����֡
void SpriteButton::setDisabledSpriteFrame(cocos2d::SpriteFrame * sf, bool isSelectStatus)
{
	auto & sfs = isSelectStatus ? m_disabledSelectedSpriteFrame : m_disabledSpriteFrame;

	if (sfs)
	{
		sfs->release();
		sfs = nullptr;
	}

	if (sf)
	{
		sfs = sf;
		sfs->retain();
	}

	if (m_status == 2)
	{
		switchToDisabled();
	}
}


//��������״̬����֡(�ڶ����������Ƿ����õ�ѡ��״̬��)
void SpriteButton::setNormalSpriteFrame(const std::string & sfName, bool isSelectStatus)
{
	setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName), isSelectStatus);
}


//���ð���״̬����֡
void SpriteButton::setPressSpriteFrame(const std::string & sfName, bool isSelectStatus)
{
	setPressSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName), isSelectStatus);
}


//���ý���״̬����֡
void SpriteButton::setDisabledSpriteFrame(const std::string & sfName, bool isSelectStatus)
{
	setDisabledSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sfName), isSelectStatus);
}


//�˳�ʱ�Ƴ�������
void SpriteButton::onExit()
{
	Sprite::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_touchListener);
}



//����ȡ��
void SpriteButton::touchCancel()
{
	if (m_startToBeTouched)
	{
		if (m_status == 1)
		{
			switchToNormal();
		}
		m_status = 3;
	}
}


//�������а�ť����״̬
void SpriteButton::setAllButtonsMutexStatus(bool isEnabled)
{
	m_mutexStatus = !isEnabled;
}


//���øհ���ʱ�ص�����
void SpriteButton::setCallbackTouchBegan(const std::function<void(cocos2d::Ref*)> callback)
{
	m_touchBeganCallback = callback;
}


//���ý���ʱ�Ļص�����
void SpriteButton::setCallbackDisabled(const std::function<void(cocos2d::Ref*)> callback)
{
	m_disabledCallback = callback;
}


//����Ƿ񸸽ڵ�ɼ�
bool SpriteButton::_isAncensterEnabled(Node * node)
{
	if (node == nullptr)
	{
		return true;
	}

	if (!node->isVisible())
	{
		return false;
	}

	return _isAncensterEnabled(node->getParent());
}


//���ð�ť��������
void SpriteButton::setSound(const std::string & soundFile)
{
	m_sound = soundFile;
}


//����Ĭ�ϰ�ť���µ�����
void SpriteButton::setAllButtonsDefaultSound(const std::string & soundFile)
{
	m_defaultSound = soundFile;
}


//�л�ѡ��״̬
void SpriteButton::setSelectedStatus(bool selected)
{
	if (m_isSelected == selected)
	{
		return;
	}

	m_isSelected = selected;

	if (m_status == 0)
	{
		switchToNormal();
	}
	else if (m_status == 1)
	{
		switchToPress();
	}
	else if (m_status == 2)
	{
		switchToDisabled();
	}
}


//���ø���״̬
void SpriteButton::setBright(bool bright)
{
	if (bright == m_isBright)
	{
		return;
	}

	m_isBright = bright;

	if (m_isBright && m_status == 2)
	{
		switchToDisabled();
	}
	else if (!m_isBright && m_status == 2)
	{
		switchToNormal();
		switchToDisabled();
	}
}


//���ظ���״̬
bool SpriteButton::isBright()
{
	return m_isBright;
}


//���þ���״̬
void SpriteButton::setMute(bool isMute)
{
	m_isMute = isMute;
}


//��ȡ����״̬
bool SpriteButton::isMute()
{
	return m_isMute;
}


//����һ�ΰ�ť(�������ӳٶ�ô����������ʱ��Ქ�Ŷ���)
void SpriteButton::activeButton(float delayedAnimTime)
{
	if (delayedAnimTime == 0)
	{
		m_callback(this);
	}
	else
	{
		if (onTouchBegan(nullptr, nullptr))
		{
			auto act1 = DelayTime::create(delayedAnimTime);
			auto act2 = CallFunc::create(std::bind(&SpriteButton::onTouchEnded, this, nullptr, nullptr));
			runAction(Sequence::create(act1, act2, nullptr))->setTag(SPRITE_BUTTON_ACTIVE_ACTION_TAG);
		}
	}
}


//�������Ų�
void SpriteButton::setScaleDiff(float diff)
{
	m_scaleDiff = diff;
}


//��һϵ�а�ť���ҵ�һ����������ð�ť����İ�ť(��ť�б������Ƿ���β����)
SpriteButton * SpriteButton::getNearestButtonWithDirection(const cocos2d::Vector<SpriteButton*> & buttons, SpriteButton::Direction dire, bool isLooped)
{
	SpriteButton * nearest = nullptr;
	SpriteButton * farthest = nullptr;

	for (auto & i : buttons)
	{
		if (i == this) continue;

		if (dire == SpriteButton::Direction::LEFT)
		{
			if (i->m_logicPosition.x < this->m_logicPosition.x)
			{
				if (!nearest || (abs(i->m_logicPosition.y - m_logicPosition.y) < abs(nearest->m_logicPosition.y - m_logicPosition.y)) ||
					(abs(nearest->m_logicPosition.y - m_logicPosition.y) == abs(i->m_logicPosition.y - m_logicPosition.y) && i->m_logicPosition.x > nearest->m_logicPosition.x))
				{
					nearest = i;
				}
			}
			else if (isLooped && i->m_logicPosition.x > this->m_logicPosition.x)
			{
				if (!farthest || (abs(i->m_logicPosition.y - m_logicPosition.y) < abs(farthest->m_logicPosition.y - m_logicPosition.y)) ||
					(abs(farthest->m_logicPosition.y - m_logicPosition.y) == abs(i->m_logicPosition.y - m_logicPosition.y) && i->m_logicPosition.x > farthest->m_logicPosition.x))
				{
					farthest = i;
				}
			}
		}
		else if (dire == SpriteButton::Direction::RIGHT)
		{
			if (i->m_logicPosition.x > this->m_logicPosition.x)
			{
				if (!nearest || (abs(i->m_logicPosition.y - m_logicPosition.y) < abs(nearest->m_logicPosition.y - m_logicPosition.y)) ||
					(abs(nearest->m_logicPosition.y - m_logicPosition.y) == abs(i->m_logicPosition.y - m_logicPosition.y) && i->m_logicPosition.x < nearest->m_logicPosition.x))
				{
					nearest = i;
				}
			}
			else if (isLooped && i->m_logicPosition.x < this->m_logicPosition.x)
			{
				if (!farthest || (abs(i->m_logicPosition.y - m_logicPosition.y) < abs(farthest->m_logicPosition.y - m_logicPosition.y)) ||
					(abs(farthest->m_logicPosition.y - m_logicPosition.y) == abs(i->m_logicPosition.y - m_logicPosition.y) && i->m_logicPosition.x < farthest->m_logicPosition.x))
				{
					farthest = i;
				}
			}
		}
		else if (dire == SpriteButton::Direction::UP)
		{
			if (i->m_logicPosition.y > this->m_logicPosition.y)
			{
				if (!nearest || (abs(i->m_logicPosition.x - m_logicPosition.x) < abs(nearest->m_logicPosition.x - m_logicPosition.x)) ||
					(abs(nearest->m_logicPosition.x - m_logicPosition.x) == abs(i->m_logicPosition.x - m_logicPosition.x) && i->m_logicPosition.y < nearest->m_logicPosition.y))
				{
					nearest = i;
				}
			}
			else if (isLooped && i->m_logicPosition.y < this->m_logicPosition.y)
			{
				if (!farthest || (abs(i->m_logicPosition.x - m_logicPosition.x) < abs(farthest->m_logicPosition.x - m_logicPosition.x)) ||
					(abs(farthest->m_logicPosition.x - m_logicPosition.x) == abs(i->m_logicPosition.x - m_logicPosition.x) && i->m_logicPosition.y < farthest->m_logicPosition.y))
				{
					farthest = i;
				}
			}
		}
		else if (dire == SpriteButton::Direction::DOWN)
		{
			if (i->m_logicPosition.y < this->m_logicPosition.y)
			{
				if (!nearest || (abs(i->m_logicPosition.x - m_logicPosition.x) < abs(nearest->m_logicPosition.x - m_logicPosition.x)) ||
					(abs(nearest->m_logicPosition.x - m_logicPosition.x) == abs(i->m_logicPosition.x - m_logicPosition.x) && i->m_logicPosition.y > nearest->m_logicPosition.y))
				{
					nearest = i;
				}
			}
			else if (isLooped && i->m_logicPosition.y > this->m_logicPosition.y)
			{
				if (!farthest || (abs(i->m_logicPosition.x - m_logicPosition.x) < abs(farthest->m_logicPosition.x - m_logicPosition.x)) ||
					(abs(farthest->m_logicPosition.x - m_logicPosition.x) == abs(i->m_logicPosition.x - m_logicPosition.x) && i->m_logicPosition.y > farthest->m_logicPosition.y))
				{
					farthest = i;
				}
			}
		}
	}

	if (!nearest)
	{
		nearest = farthest;
	}

	if (!nearest)
	{
		nearest = this;
	}

	return nearest;
}


//��ȡ�߼�λ��
const SpriteButton::LogicPosition & SpriteButton::getLogicPosition()
{
	return m_logicPosition;
}


//�����߼�λ��
void SpriteButton::setLogicPosition(int x, int y)
{
	m_logicPosition.set(x, y);
}



//--------------------------------------------------------------------------------------

SpriteButtonZooming * SpriteButtonZooming::create(const std::string & normalSpriteFrameName, const std::string & pressSpriteFrameName, const std::string & disabledSpriteFrameName)
{
	auto spb = create();

	auto sfc = SpriteFrameCache::getInstance();

	spb->setNormalSpriteFrame(sfc->getSpriteFrameByName(normalSpriteFrameName));
	spb->setPressSpriteFrame(sfc->getSpriteFrameByName(pressSpriteFrameName));
	spb->setDisabledSpriteFrame(sfc->getSpriteFrameByName(disabledSpriteFrameName));

	spb->setNormalSpriteFrame(sfc->getSpriteFrameByName(normalSpriteFrameName), true);
	spb->setPressSpriteFrame(sfc->getSpriteFrameByName(pressSpriteFrameName), true);
	spb->setDisabledSpriteFrame(sfc->getSpriteFrameByName(disabledSpriteFrameName), true);

	return spb;
}

//ת��������״̬
void SpriteButtonZooming::switchToNormal()
{
	m_status = 0;
	if (m_isSelected ? m_normalSelectedSpriteFrame : m_normalSpriteFrame)
	{
		setSpriteFrame(m_isSelected ? m_normalSelectedSpriteFrame : m_normalSpriteFrame);
	}
	else
	{
		setTexture(nullptr);
	}

	if (!getActionByTag(SPRITE_BUTTON_SCALE_ACTION_TAG))
	{
		if (!m_eraseNormalScaleOnce)
		{
			stopActionByTag(SPRITE_BUTTON_SCALE_ACTION_TAG + 1);
			runAction(RepeatForever::create(Sequence::create(
				EaseSineOut::create(ScaleTo::create(0.4f, 0.9f)),
				EaseSineIn::create(ScaleTo::create(0.4f, 1.0f)),
				nullptr)))->setTag(SPRITE_BUTTON_SCALE_ACTION_TAG);
		}
		else
		{
			m_eraseNormalScaleOnce = false;
		}
	}
}



//ת��������״̬
void SpriteButtonZooming::switchToPress()
{
	m_status = 1;

	if (m_isSelected ? m_pressSelectedSpriteFrame : m_pressSpriteFrame)
	{
		setSpriteFrame(m_isSelected ? m_pressSelectedSpriteFrame : m_pressSpriteFrame);
	}
	else
	{
		stopActionByTag(SPRITE_BUTTON_SCALE_ACTION_TAG);
		stopActionByTag(SPRITE_BUTTON_SCALE_ACTION_TAG+1);
		runAction(EaseSineIn::create(ScaleTo::create(0.1f, 1.1f)))->setTag(SPRITE_BUTTON_SCALE_ACTION_TAG+1);
	}
}


//ת��������״̬
void SpriteButtonZooming::switchToDisabled()
{
	m_status = 2;
	if (!m_isBright && (m_isSelected ? m_disabledSelectedSpriteFrame : m_disabledSpriteFrame))
	{
		setSpriteFrame(m_isSelected ? m_disabledSelectedSpriteFrame : m_disabledSpriteFrame);
	}
	stopActionByTag(SPRITE_BUTTON_SCALE_ACTION_TAG);
	stopActionByTag(SPRITE_BUTTON_SCALE_ACTION_TAG+1);
	setScale(1);
}


//��ʼ��
bool SpriteButtonZooming::init()
{
	if (!SpriteButton::init())
	{
		return false;
	}

	m_eraseNormalScaleOnce = false;

	return true;
}


//����һ��ת��������״̬�����������
void SpriteButtonZooming::eraseNormalScaleOnce()
{
	m_eraseNormalScaleOnce = true;
}
