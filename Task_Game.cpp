//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include "myLib.h"
#include <iostream>

namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//リソースの初期化
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//リソースの解放
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//「初期化」タスク生成時に１回だけ行う処理
	bool  Object::Initialize()
	{
		//スーパークラス初期化
		__super::Initialize(defGroupName, defName, true);
		//リソースクラス生成orリソース共有
		this->res = Resource::Create();

		//★データ初期化
		
		//★タスクの生成
		//背景タスク
		//auto  bg = GameBG::Object::Create(true);
		//プレイヤ
		//auto  pl = Player::Object::Create(true);
		//auto en = Enemy::Object::Create(true);
		BG= GameBG::Object::Create(true);
		PO= Player::Object::Create(true);
		// ﾑ�鈕犧� ���胛 糅璢�� (��韲褞: 5 ����)
		//for (int i = 0; i < 3; i++)
		//{
		//	auto en = Enemy::Object::Create(true);
		//	if (en) {
		//		// ﾏ�韲褞 ���瑙�粲� ��鉅�韋
		//		en->pos.x = 240.0f ;
		//		en->pos.y = i *80.0f;
		//		en->res->hitBase.h = 32;
		//		en->res->hitBase.w = 32;
		//		enemies.push_back(en);

		//	}
	
		//}
		//enemies[0]->pos.x =  500.0f;
		//enemies[0]->pos.y = 500.0f;

		return true;
	}
	//-------------------------------------------------------------------
	//「終了」タスク消滅時に１回だけ行う処理
	bool  Object::Finalize()
	{
		//★データ＆タスク解放
		ge->KillAll_G("本編");
		ge->KillAll_G("プレイヤ");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//★引き継ぎタスクの生成
			auto next = Ending::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//「更新」１フレーム毎に行う処理
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState( );
		static int updateCounter = 0; // ﾑ�ｸ��韭 糺鉋粽� �褪�萵 Update()

		updateCounter++; // ﾓ粢�顆鞣瑯� ��ｸ��韭

		// ﾅ��� ������ 3 �裲��蕘 (3 糺鉋籵 Update)
		if (updateCounter >= 100) {
			updateCounter = 0; // ﾑ碣瑰�籵褌 ��ｸ��韭

			// ﾃ褊褞頏�褌 ����琺��� ���顆褥�粽 糅璢�� (�� 1 蒡 3)
			int enemyCount = 1 + std::rand() % 3;

			for (int i = 0; i < enemyCount; i++) {
				auto en = Enemy::Object::Create(true);
				if (en) {
					// ﾓ��瑙珞�鞣瑯� ��鉅��� 糅璢�
					en->pos.x = 540.0f; // X-����蒻�瑣� �韭�頏�籵��
					en->pos.y = std::rand() % (270 - 32); // ﾑ���琺��� ��鉅��� �� Y � ��裝褄瑾 鞳��粽胛 ����

					// ﾓ��瑙珞�鞣瑯� �珸�褞� �頸碚���
					en->res->hitBase.h = 32;
					en->res->hitBase.w = 32;

					// ﾄ�矜粱�褌 糅璢� � �瑰�鞣
					enemies.push_back(en);
				}
			}
		}

	//	ML::Box2D me = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		CheckCollisionPlayerEnemies();

		if (inp.B1.down) {//Z keyboard
			//auto  pl = Player::Object::Create(true);
			auto bl = Bullet::Object::Create(true);
			bullets.push_back(bl);
			bl->pos.x = PO->pos.x+50;
			bl->pos.y = PO->pos.y+26;
		}

		CheckCollisionBulletEnemies();

		if (inp.ST.down) {//s key
			//自身に消滅要請
			this->Kill();
			for (auto& bullet : bullets) {
				bullet->Kill();
				bullets.erase(bullets.begin());
			}
			bullets.clear();
			for (auto& enemy : enemies) {
				enemy->Kill();
				enemies.erase(enemies.begin());
			}
			enemies.clear();
		}
		
	}

	void Object::CheckCollisionBulletEnemies() {
		for (size_t i = 0; i < bullets.size(); ++i) {

			// ﾕ頸碚�� ����
			ML::Box2D bulletBox = bullets[i]->res->hitBase.OffsetCopy(bullets[i]->pos.x, bullets[i]->pos.y);
			bulletBox.h = 16;
			bulletBox.w = 16;
			bulletBox.x = bullets[i]->pos.x;
			bulletBox.y = bullets[i]->pos.y;

			// ﾏ褞裔頏瑯� 糂襄 糅璢��
			for (size_t j = 0; j < enemies.size(); ++j) {

				// ﾕ頸碚�� 糅璢�
				ML::Box2D enemyBox = enemies[j]->res->hitBase.OffsetCopy(enemies[j]->pos.x, enemies[j]->pos.y);
				enemyBox.x = enemies[i]->pos.x;
				enemyBox.y = enemies[i]->pos.y;

				// ﾏ��粢��褌 �������粢�韃
				if (bulletBox.Hit(enemyBox)) {
					// ﾅ��� �������粢�韃, ���褶瑯� �碚頷 �瑕 ��肛碾頷
					bullets[i]->Kill();
					enemies[j]->Kill();

					// ﾓ萵��褌 ���� 韈 �瑰�鞣�
					bullets.erase(bullets.begin() + i);
					--i; // ﾑ�襌瑯� 竟蒟��, ���磊 �� �������頸� ��裝����� ����

					// ﾓ萵��褌 糅璢� 韈 �瑰�鞣�
					enemies.erase(enemies.begin() + j);
					--j; // ﾑ�襌瑯� 竟蒟��, ���磊 �� �������頸� ��裝���裙� 糅璢�

					// ﾂ���蒻� 韈 粹���褊�裙� �韭��, �瑕 �瑕 �裲���� ���� �趺 ��顆��趺��
					break;
				}
			}
		}
	}

	void Object::CheckCollisionPlayerEnemies()
	{
		// ﾅ��� 鞳��� �趺 �ｸ���, �� ���粢��褌
		if (!PO || PO->gamestate!=Player::GameState::Normal) return;

		// ﾕ頸碚�� 鞳����
		ML::Box2D playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		// ﾏ褞裔頏瑯� ﾂﾑﾅﾕ 糅璢��
		for (int i=0; i<enemies.size();i++)
		{

			// ﾕ頸碚�� 糅璢�
			ML::Box2D enemyBox = enemies[i]->res->hitBase.OffsetCopy(enemies[i]->res->hitBase.x, enemies[i]->res->hitBase.y);
			enemyBox.x = enemies[i]->pos.x;
			enemyBox.y = enemies[i]->pos.y;
			playerBox = PO->res->hitBase.OffsetCopy(PO-> res->hitBase.x, PO->res->hitBase.y);
			playerBox.x = PO->pos.x;
			playerBox.y = PO->pos.y;

			if (enemyBox.Hit(playerBox))
			{
				// ﾏ��褶瑯� �碚頷 �瑕 ��肛碾頷
				PO->gamestate = Player::GameState::Non;
				enemies[i]->gamestate = Enemy::GameState::Non;
				auto en = enemies[i];
				
				// ﾂ�鍄籵褌 Kill(), 褥�� ��� ��跫�
				PO->Kill();

			

				// ﾈ, � ��韲褞�, 鈞粢��瑯� �瑟 Task_Game
				this->Kill();

				// ﾏ�褞�籵褌 �韭�, ���磊 �� ���粢���� 萵����
				if (i < enemies.size()) {
					enemies.erase(enemies.begin() + i);
					en->Kill();
				}

				break;
			}
		}
	}

	//-------------------------------------------------------------------
	//「２Ｄ描画」１フレーム毎に行う処理
	void  Object::Render2D_AF()
	{
	}

	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//以下は基本的に変更不要なメソッド
	//★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
	//-------------------------------------------------------------------
	//タスク生成窓口
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ゲームエンジンに登録
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//イニシャライズに失敗したらKill
			}
			return  ob;
		}
		return nullptr;
	}
	//-------------------------------------------------------------------
	bool  Object::B_Initialize()
	{
		return  this->Initialize();
	}
	//-------------------------------------------------------------------
	Object::~Object() { this->B_Finalize(); }
	bool  Object::B_Finalize()
	{
		auto  rtv = this->Finalize();
		return  rtv;
	}
	//-------------------------------------------------------------------
	Object::Object() {	}
	//-------------------------------------------------------------------
	//リソースクラスの生成
	Resource::SP  Resource::Create()
	{
		if (auto sp = instance.lock()) {
			return sp;
		}
		else {
			sp = Resource::SP(new  Resource());
			if (sp) {
				sp->Initialize();
				instance = sp;
			}
			return sp;
		}
	}
	//-------------------------------------------------------------------
	Resource::Resource() {}
	//-------------------------------------------------------------------
	Resource::~Resource() { this->Finalize(); }
}