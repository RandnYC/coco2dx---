#include "SchedulerTest.h"

Scene *SchedulerTest::createScene() {
	auto scene = SchedulerTest::create();
	return scene;
}
bool SchedulerTest::init() {
	if (!Scene::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	//��ǰ���Ա�ǩ����
	auto test_label = Label::createWithSystemFont("About Node's Update Test", "", 30);
	test_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - test_label->getContentSize().height));
	this->addChild(test_label);

	/***************************************************************
	****						�ڵ�һ
	****************************************************************/
	LayerColor *block1 = LayerColor::create(Color4B::RED, 70, 70);
	this->addChild(block1);
	block1->ignoreAnchorPointForPosition(false);
	block1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	block1->setPosition(visibleSize.width / 4, visibleSize.height * 3 / 4 - 50);
	//���������Ա��ȡ
	block1->setName("block1");
	//�����ڽڵ�һ�ϵ����ֱ�ǩ
	auto label1 = Label::createWithSystemFont("block1", "", 22);
	block1->addChild(label1);
	label1->setPosition(block1->getContentSize() / 2);

	//�ڵ�һ״̬��ǩ,����״̬����Ҫ��̬�ı�����������Ҫ�������ø�����
	auto state_label1 = Label::createWithSystemFont("Block1 State:", "", 25);
	state_label1->setPosition(Vec2(
		state_label1->getContentSize().width / 2,
		block1->getPositionY() + block1->getContentSize().height)
	);
	this->addChild(state_label1);
	auto state1 = Label::createWithSystemFont("Stop", "", 25);
	state1->setPosition(Vec2(
		visibleSize.width / 2,
		state_label1->getPositionY())
	);
	this->addChild(state1);
	//���������Ա��ȡ
	state1->setName("state1");

	/***************************************************************
	****						�ڵ��
	****************************************************************/
	LayerColor *block2 = LayerColor::create(Color4B::RED, 70, 70);
	this->addChild(block2);
	block2->ignoreAnchorPointForPosition(false);
	block2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	block2->setPosition(Vec2(block1->getPositionX(), block1->getPositionY() - 160));
	//���������Ա��ȡ
	block2->setName("block2");
	//�����ڽڵ���ϵ����ֱ�ǩ
	auto label2 = Label::createWithSystemFont("block2", "", 22);
	block2->addChild(label2);
	label2->setPosition(block2->getContentSize() / 2);


	//�ڵ��״̬��ǩ
	auto state_label2 = Label::createWithSystemFont("Block2 State:", "", 25);
	state_label2->setPosition(Vec2(
		state_label2->getContentSize().width / 2,
		block2->getPositionY() + block2->getContentSize().height)
	);
	this->addChild(state_label2);
	auto state2 = Label::createWithSystemFont("Stop", "", 25);
	state2->setPosition(Vec2(
		visibleSize.width / 2,
		state_label2->getPositionY())
	);
	this->addChild(state2);

	state2->setName("state2");
	/***************************************************************
	****						�˵���Ŀ
	****************************************************************/

	/*****
	**�ڵ��Start�˵���Ŀ�����ڽڵ㿪��������
	******/
	MenuItemLabel* Start_menuItem1 = MenuItemLabel::create(Label::createWithSystemFont("Start", "", 25), [&](Ref* sender) {

		//�޸�Block1״̬
		auto state = dynamic_cast<Label*>(this->getChildByName("state1"));
		state->setString("Running...");
		//������ǰ�ڵ��update
		this->scheduleUpdate();
		//���õ�ǰ���Ŀ�겻����
		auto start_item = dynamic_cast<MenuItemLabel*>(sender);
		start_item->setEnabled(false);
		//��ȡRemove������Ϊ���õ��
		auto menu = dynamic_cast<Menu*>(this->getChildByName("menu"));
		auto remove_item = dynamic_cast<MenuItemLabel*>(menu->getChildByName("remove_item1"));
		remove_item->setEnabled(true);
	});
	Start_menuItem1->setPosition(Vec2(
		Start_menuItem1->getContentSize().width / 2 - visibleSize.width / 2,
		Start_menuItem1->getContentSize().height - 10)
	);
	Start_menuItem1->setName("start_item1");

	auto Start_menuItem2 = MenuItemLabel::create(Label::createWithSystemFont("Start", "", 25), [&](Ref *sender) {
		if (!isScheduled(CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update))) {

			//���õ�ǰ���Ŀ�겻����
			auto start_item = dynamic_cast<MenuItemLabel*>(sender);
			start_item->setEnabled(false);
			/*****************************************
			**�����Զ���ڵ��update����3��֮������ÿ1�����һ�Σ�һֱ����
			**������أ�
			**param1  CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update)�����������ص��ĺ���
			**param2  1.0f:ÿ��һ�����һ��
			**param3  �ظ�����
			**param4  ��һ�ο����������ӳ�ʱ�䣬����Ϊ4��
			******************************************/
			this->schedule(CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update), 1.0f, CC_REPEAT_FOREVER, 4.0f);
			//������һ����������׼������
			this->schedule(CC_SCHEDULE_SELECTOR(SchedulerTest::ReadyFunc), 1.0f, 3, 0);
		}

	});
	Start_menuItem2->setPosition(Vec2(Start_menuItem2->getContentSize().width / 2 - visibleSize.width / 2, -150));
	Start_menuItem2->setName("start_item2");

	/*****
	**�ڵ��Remove�˵���Ŀ�������Ƴ��ڵ������
	******/
	MenuItemLabel *Remove_menuItem1 = MenuItemLabel::create(Label::createWithSystemFont("Remove", "", 25), [&](Ref *sender) {
		//�޸�Block1״̬
		auto state = dynamic_cast<Label*>(this->getChildByName("state1"));
		state->setString("Removed");
		//�ر�update
		this->unscheduleUpdate();
		//���õ�ǰĿ�겻����
		auto pause_item = dynamic_cast<MenuItemLabel*>(sender);
		pause_item->setEnabled(false);
		//��ȡStart������Ϊ�ɵ��
		auto menu = dynamic_cast<Menu*>(this->getChildByName("menu"));
		auto start_item = dynamic_cast<MenuItemLabel*>(menu->getChildByName("start_item1"));
		start_item->setEnabled(true);
	});

	Remove_menuItem1->setPosition(Vec2(
		Start_menuItem1->getPositionX() + Start_menuItem1->getContentSize().width * 2,
		Start_menuItem1->getPositionY()));
	Remove_menuItem1->setEnabled(false);
	Remove_menuItem1->setName("remove_item1");

	auto Remove_menuItem2 = MenuItemLabel::create(Label::createWithSystemFont("Remove", "", 25), [&](Ref* sender) {

		if (isScheduled(CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update))) {
			//�޸�Block2״̬
			auto state = dynamic_cast<Label*>(this->getChildByName("state2"));
			state->setString("Removed");

			this->unschedule(CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update));

			//���õ�ǰĿ�겻����
			auto remove_item = dynamic_cast<MenuItemLabel*>(sender);
			remove_item->setEnabled(false);
			//��ȡStart������Ϊ�ɵ��
			auto menu = dynamic_cast<Menu*>(this->getChildByName("menu"));
			auto start_item = dynamic_cast<MenuItemLabel*>(menu->getChildByName("start_item2"));
			start_item->setEnabled(true);
		}

	});
	Remove_menuItem2->setPosition(Vec2(
		Start_menuItem2->getPositionX() + Start_menuItem2->getContentSize().width * 2,
		Start_menuItem2->getPositionY()));
	Remove_menuItem2->setEnabled(false);
	Remove_menuItem2->setName("remove_item2");

	/*****
	**�ڵ��Pause�˵���Ŀ��������ͣ��ǰ�ڵ�����е�����
	******/
	auto Pause_menuItem = MenuItemLabel::create(Label::createWithSystemFont("PauseCurrentTarget", "", 25), [&](Ref* sender) {
		//��ͣ��ǰ�ڵ��е����е�����
		this->getScheduler()->pauseTarget(this);

		//���õ�ǰĿ�겻����
		auto remove_item = dynamic_cast<MenuItemLabel*>(sender);
		remove_item->setEnabled(false);

		//��ȡResume������Ϊ�ɵ��
		auto menu = dynamic_cast<Menu*>(this->getChildByName("menu"));
		auto resume_item = dynamic_cast<MenuItemLabel*>(menu->getChildByName("resume_item"));
		resume_item->setEnabled(true);

		//�޸�Block1״̬
		auto state1 = dynamic_cast<Label*>(this->getChildByName("state1"));
		if (state1->getString() == "Running...") {
			state1->setString("Pause");
		}

		//�޸�Block2״̬
		auto state2 = dynamic_cast<Label*>(this->getChildByName("state2"));
		if (isScheduled(CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update)) || isScheduled(CC_SCHEDULE_SELECTOR(SchedulerTest::ReadyFunc))) {
			state2->setString("Pause");
		}


	});
	Pause_menuItem->setPosition(Vec2(0, Pause_menuItem->getContentSize().height * 3 - visibleSize.height / 2));
	Pause_menuItem->setName("pause_item");

	/*****
	**�ڵ��Resume�˵���Ŀ�����ڻָ���ǰ�ڵ�����е�����
	******/
	auto Resume_menuItem = MenuItemLabel::create(Label::createWithSystemFont("ResumeCurrentTarget", "", 25), [&](Ref* sender) {
		//�ָ���ǰ�ڵ�����е�����
		this->getScheduler()->resumeTarget(this);

		//���õ�ǰĿ�겻����
		auto remove_item = dynamic_cast<MenuItemLabel*>(sender);
		remove_item->setEnabled(false);

		//��ȡPause������Ϊ�ɵ��
		auto menu = dynamic_cast<Menu*>(this->getChildByName("menu"));
		auto pause_item = dynamic_cast<MenuItemLabel*>(menu->getChildByName("pause_item"));
		pause_item->setEnabled(true);

		//�޸�Block1״̬
		auto state1 = dynamic_cast<Label*>(this->getChildByName("state1"));
		if (state1->getString() == "Pause") {
			state1->setString("Running...");
		}

		//�޸�Block2״̬
		auto state2 = dynamic_cast<Label*>(this->getChildByName("state2"));
		if (isScheduled(CC_SCHEDULE_SELECTOR(SchedulerTest::Own_Update))) {
			state2->setString("Running...");
		}


	});
	Resume_menuItem->setPosition(Vec2(
		Pause_menuItem->getPositionX(),
		Pause_menuItem->getPositionY() - Resume_menuItem->getContentSize().height * 2));
	Resume_menuItem->setEnabled(false);
	Resume_menuItem->setName("resume_item");

	//�˵�
	auto menu = Menu::create(Start_menuItem1, Start_menuItem2, Remove_menuItem1, Remove_menuItem2, Pause_menuItem, Resume_menuItem, NULL);
	menu->setName("menu");

	this->addChild(menu);



	return true;
}
//�ڵ�����Ҹ��º���
void SchedulerTest::update(float dt) {

	//CCLOG("THE NODE'S UPDATE : %f...",dt);
	//�жϽڵ�ķ���
	static int dir1 = 1;

	//ͨ�����ֻ�ȡ��ǰ�ڵ���ӽڵ�
	auto block1 = dynamic_cast<LayerColor*>(this->getChildByName("block1"));
	Vec2 pos = Vec2(block1->getPositionX() + 3 * dir1, block1->getPositionY());
	if (pos.x > visibleSize.width - block1->getContentSize().width / 2 || pos.x < block1->getContentSize().width / 2) {
		dir1 = -dir1;
	}

	block1->setPosition(pos);
}

//�Լ������Ҹ��º���
void SchedulerTest::Own_Update(float dt) {
	//log("This is My Own Update : %f...",dt);
	static int dir2 = 1;

	//ͨ�����ֻ�ȡ��ǰ�ڵ���ӽڵ�
	auto block2 = dynamic_cast<LayerColor*>(this->getChildByName("block2"));
	Vec2 pos = Vec2(block2->getPositionX() + 3 * dir2, block2->getPositionY());
	if (pos.x > visibleSize.width - block2->getContentSize().width / 2 || pos.x < block2->getContentSize().width / 2) {
		dir2 = -dir2;
	}

	block2->setPosition(pos);

}

//׼��״̬�ĺ���
void SchedulerTest::ReadyFunc(float dt) {
	static int i = 4;
	i--;
	//�޸�Block2״̬
	auto state = dynamic_cast<Label*>(this->getChildByName("state2"));
	state->setString(String::createWithFormat("Ready to Start:%d second", i)->getCString());

	if (i == 0) {
		i = 4;
		//�޸�Block2״̬
		auto state = dynamic_cast<Label*>(this->getChildByName("state2"));
		state->setString("Running...");
		//��ȡRemove.
		auto menu = dynamic_cast<Menu*>(this->getChildByName("menu"));
		auto remove_item = dynamic_cast<MenuItemLabel*>(menu->getChildByName("remove_item2"));
		remove_item->setEnabled(true);

	}
}