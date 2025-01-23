//-------------------------------------------------------------------
//ゲーム本編
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
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
		for (int i = 0; i < 4; ++i)
		{
			auto en = Enemy::Object::Create(true);
			if (en) {
				// ﾏ�韲褞 ���瑙�粲� ��鉅�韋
				en->pos.x = 200.0f ;
				en->pos.y = i * 42.0f;
				enemies.push_back(en);

			}
	
		}

		return true;
		return  true;
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
		enemies[0] = nullptr;
		auto inp = ge->in1->GetState( );
	//	ML::Box2D me = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		CheckCollisionPlayerEnemies();

		if (inp.ST.down) {//s key
			//自身に消滅要請
			this->Kill();
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

			if (enemies[i]->gamestate != Enemy::GameState::Normal) continue;

			// ﾕ頸碚�� 糅璢�
			ML::Box2D enemyBox = enemies[i]->res->hitBase.OffsetCopy(enemies[i]->pos.x, enemies[i]->pos.y);
			playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
			std::cout << enemies[i]->pos.x << " " << enemies[i]->pos.y;

			if (enemyBox.Hit(playerBox))
			{
				// ﾏ��褶瑯� �碚頷 �瑕 ��肛碾頷
				PO->gamestate = Player::GameState::Non;
				enemies[i]->gamestate = Enemy::GameState::Non;

				// ﾂ�鍄籵褌 Kill(), 褥�� ��� ��跫�
				PO->Kill();
				enemies[i]->Kill();

				// ﾈ, � ��韲褞�, 鈞粢��瑯� �瑟 Task_Game
				this->Kill();

				// ﾏ�褞�籵褌 �韭�, ���磊 �� ���粢���� 萵����
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