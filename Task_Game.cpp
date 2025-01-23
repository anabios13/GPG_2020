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
		EO = Enemy::Object::Create(true);
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
		auto inp = ge->in1->GetState( );
		//generation enemy unit
		/*for (int e = 0; e < 30; ++e) {
			if (enemys[e].state == State::Normal) {
				if (enemys[e].moveCnt < 100) { enemys[e].x += 1; }
				else { enemys[e].x -= 1; }
				enemys[e].moveCnt++;
				if (enemys[e].moveCnt >= 200) { enemys[e].moveCnt = 0; }
			}
			if (player.state == State::Normal) {
				ML::Box2D me = player.hitBase.OffsetCopy(player.x, player.y);
				if (enemys[e].state == State::Normal) {
					ML::Box2D you = enemys[e].hitBase.OffsetCopy(enemys[e].x, enemys[e].y);
					if (you.Hit(me) == true) {
						player.state = State::Non;
						enemys[e].state = State::Non;
					}
				}
			}
		}*/
		ML::Box2D me = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		if (EO->gamestate == Enemy::GameState::Normal) {
			ML::Box2D you = EO->res->hitBase.OffsetCopy(EO->pos.x, EO->pos.y);
			if (you.Hit(me)) {
				PO->gamestate = Player::GameState::Non;
				EO->gamestate = Enemy::GameState::Non;
				PO->Kill();
				EO->Kill();
				this->Kill();
			}
		}		
		if (inp.ST.down) {//s key
			//自身に消滅要請
			this->Kill();
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