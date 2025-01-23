//-------------------------------------------------------------------
//ƒQ[ƒ€–{•Ò
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include <iostream>

namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//ƒŠƒ\[ƒX‚Ì‰Šú‰»
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//ƒŠƒ\[ƒX‚Ì‰ğ•ú
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//u‰Šú‰»vƒ^ƒXƒN¶¬‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
	bool  Object::Initialize()
	{
		//ƒX[ƒp[ƒNƒ‰ƒX‰Šú‰»
		__super::Initialize(defGroupName, defName, true);
		//ƒŠƒ\[ƒXƒNƒ‰ƒX¶¬orƒŠƒ\[ƒX‹¤—L
		this->res = Resource::Create();

		//šƒf[ƒ^‰Šú‰»
		
		//šƒ^ƒXƒN‚Ì¶¬
		//”wŒiƒ^ƒXƒN
		//auto  bg = GameBG::Object::Create(true);
		//ƒvƒŒƒCƒ„
		//auto  pl = Player::Object::Create(true);
		//auto en = Enemy::Object::Create(true);
		BG= GameBG::Object::Create(true);
		PO= Player::Object::Create(true);
		// Ñîçäà¸ì ìíîãî âğàãîâ (ïğèìåğ: 5 øòóê)
		for (int i = 0; i < 4; ++i)
		{
			auto en = Enemy::Object::Create(true);
			if (en) {
				// Ïğèìåğ óñòàíîâêè ïîçèöèè
				en->pos.x = 200.0f ;
				en->pos.y = i * 42.0f;
				enemies.push_back(en);

			}
	
		}

		return true;
		return  true;
	}
	//-------------------------------------------------------------------
	//uI—¹vƒ^ƒXƒNÁ–Å‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
	bool  Object::Finalize()
	{
		//šƒf[ƒ^•ƒ^ƒXƒN‰ğ•ú
		ge->KillAll_G("–{•Ò");
		ge->KillAll_G("ƒvƒŒƒCƒ„");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//šˆø‚«Œp‚¬ƒ^ƒXƒN‚Ì¶¬
			auto next = Ending::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
	void  Object::UpDate()
	{
		enemies[0] = nullptr;
		auto inp = ge->in1->GetState( );
	//	ML::Box2D me = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		CheckCollisionPlayerEnemies();

		if (inp.ST.down) {//s key
			//©g‚ÉÁ–Å—v¿
			this->Kill();
		}
		
	}

	void Object::CheckCollisionPlayerEnemies()
	{
		// Åñëè èãğîê óæå ì¸ğòâ, íå ïğîâåğÿåì
		if (!PO || PO->gamestate!=Player::GameState::Normal) return;

		// Õèòáîêñ èãğîêà
		ML::Box2D playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		// Ïåğåáèğàåì ÂÑÅÕ âğàãîâ
		for (int i=0; i<enemies.size();i++)
		{

			if (enemies[i]->gamestate != Enemy::GameState::Normal) continue;

			// Õèòáîêñ âğàãà
			ML::Box2D enemyBox = enemies[i]->res->hitBase.OffsetCopy(enemies[i]->pos.x, enemies[i]->pos.y);
			playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
			std::cout << enemies[i]->pos.x << " " << enemies[i]->pos.y;

			if (enemyBox.Hit(playerBox))
			{
				// Ïîìå÷àåì îáîèõ êàê ïîãèáøèõ
				PO->gamestate = Player::GameState::Non;
				enemies[i]->gamestate = Enemy::GameState::Non;

				// Âûçûâàåì Kill(), åñëè ıòî íóæíî
				PO->Kill();
				enemies[i]->Kill();

				// È, ê ïğèìåğó, çàâåğøàåì ñàì Task_Game
				this->Kill();

				// Ïğåğûâàåì öèêë, ÷òîáû íå ïğîâåğÿòü äàëüøå
				break;
			}
		}
	}

	//-------------------------------------------------------------------
	//u‚Q‚c•`‰æv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
	void  Object::Render2D_AF()
	{
	}

	//šššššššššššššššššššššššššššššššššššššššššš
	//ˆÈ‰º‚ÍŠî–{“I‚É•ÏX•s—v‚Èƒƒ\ƒbƒh
	//šššššššššššššššššššššššššššššššššššššššššš
	//-------------------------------------------------------------------
	//ƒ^ƒXƒN¶¬‘‹Œû
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ƒQ[ƒ€ƒGƒ“ƒWƒ“‚É“o˜^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//ƒCƒjƒVƒƒƒ‰ƒCƒY‚É¸”s‚µ‚½‚çKill
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
	//ƒŠƒ\[ƒXƒNƒ‰ƒX‚Ì¶¬
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