//-------------------------------------------------------------------
//ѓQЃ[ѓЂ–{•Т
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include <iostream>
#include <functional>
namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//ѓЉѓ\Ѓ[ѓX‚МЏ‰Љъ‰»
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//ѓЉѓ\Ѓ[ѓX‚М‰р•ъ
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//ЃuЏ‰Љъ‰»Ѓvѓ^ѓXѓNђ¶ђ¬Ћћ‚Й‚P‰с‚ѕ‚ЇЌs‚¤Џ€—ќ
	bool  Object::Initialize()
	{
		//ѓXЃ[ѓpЃ[ѓNѓ‰ѓXЏ‰Љъ‰»
		__super::Initialize(defGroupName, defName, true);
		//ѓЉѓ\Ѓ[ѓXѓNѓ‰ѓXђ¶ђ¬orѓЉѓ\Ѓ[ѓX‹¤—L
		this->res = Resource::Create();

		//ЃљѓfЃ[ѓ^Џ‰Љъ‰»
		
		//Ѓљѓ^ѓXѓN‚Мђ¶ђ¬
		//”wЊiѓ^ѓXѓN
		//auto  bg = GameBG::Object::Create(true);
		//ѓvѓЊѓCѓ„
		//auto  pl = Player::Object::Create(true);
		//auto en = Enemy::Object::Create(true);
		BG= GameBG::Object::Create(true);
		PO= Player::Object::Create(true);
		//EO = Enemy::Object::Create(true);
		return  true;
	}
	//-------------------------------------------------------------------
	//ЃuЏI—№Ѓvѓ^ѓXѓNЏБ–ЕЋћ‚Й‚P‰с‚ѕ‚ЇЌs‚¤Џ€—ќ
	bool  Object::Finalize()
	{
		//ЃљѓfЃ[ѓ^Ѓ•ѓ^ѓXѓN‰р•ъ
		ge->KillAll_G("–{•Т");
		ge->KillAll_G("ѓvѓЊѓCѓ„");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//Ѓљ€ш‚«Њp‚¬ѓ^ѓXѓN‚Мђ¶ђ¬
			auto next = Ending::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//ЃuЌXђVЃv‚PѓtѓЊЃ[ѓЂ–€‚ЙЌs‚¤Џ€—ќ
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState( );
		static int updateCounter = 0; // Ñ÷¸ò÷èê âûçîâîâ ìåòîäà Update()

		updateCounter++; // Óâåëè÷èâàåì ñ÷¸ò÷èê

		// Åñëè ïðîøëî 3 ñåêóíäû (3 âûçîâà Update)
		if (updateCounter >= 100) {
			updateCounter = 0; // Ñáðàñûâàåì ñ÷¸ò÷èê

			// Ãåíåðèðóåì ñëó÷àéíîå êîëè÷åñòâî âðàãîâ (îò 1 äî 3)
			int enemyCount = 1 + std::rand() % 3;

			for (int i = 0; i < enemyCount; i++) {
				auto en = Enemy::Object::Create(true);
				if (en) {
					// Óñòàíàâëèâàåì ïîçèöèþ âðàãà
					en->pos.x = 540.0f; // X-êîîðäèíàòà ôèêñèðîâàíà
					en->pos.y = std::rand() % (270 - 32); // Ñëó÷àéíàÿ ïîçèöèÿ ïî Y â ïðåäåëàõ èãðîâîãî ïîëÿ

					// Óñòàíàâëèâàåì ðàçìåðû õèòáîêñà
					en->res->hitBase.h = 32;
					en->res->hitBase.w = 32;

					// Äîáàâëÿåì âðàãà â ìàññèâ
					enemies.push_back(en);
				}
			}
		}
		//ge->GetTask<Bullet::Object::SP>();
		
		//ge->
		//[enemys]e
		//generation enemy unit
		/*for (int e = 0; e < 30; ++e) {
			if (.state == State::Normal) {
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
		ML::Box2D me = PO->res->hitBase;
		me.x = PO->pos.x;
		me.y = PO->pos.y;

		for (auto enemy : enemies)
		{
			if (enemy->gamestate == Enemy::GameState::Normal) {
			//	ML::Box2D you = enemy->res->hitBase.OffsetCopy(enemy->pos.x, enemy->pos.y);
				//ML::Box2D you = enemy->res->hitBase.OffsetCopy(enemy->pos);
				//you.x = enemy->pos.x;
				ML::Box2D you = enemy->res->hitBase;
				you.x = enemy->pos.x;
				you.y = enemy->pos.y;
				//you.h = enemy->res->hitBase.h;

				if (you.Hit(me)) {
					PO->gamestate = Player::GameState::Non;
					enemy->gamestate = Enemy::GameState::Non;
					PO->Kill();
					enemy->Kill();
					this->Kill();
				}
			}
		}

		std::vector<Enemy::Object::SP> enemiesToRemove;
		std::vector<Bullet::Object::SP> bulletsToRemove;
		//MessageBox(nullptr, std::to_string(PO->pos.x).data(), nullptr, MB_OK);
		//std::for_each(PO->shots.cbegin(),PO->shots.cend(),[](Bullet){})
		for(auto& enemy : enemies)
		{
			ML::Box2D me = enemy->res->hitBase;
			me.x = enemy->pos.x;
			me.y = enemy->pos.y;
			for (auto& bullet : PO->shots) {
				ML::Box2D you = bullet->res->hitBase;
				you.x= bullet->pos.x;
				you.y = bullet->pos.y;
				if (me.Hit(you)) {
					bullet->gamestate = Bullet::GameState::Non;
					enemy->gamestate = Enemy::GameState::Non;
					bullet->Kill();
					//PO->shots.erase(std::find(PO->shots.begin(), PO->shots.end(), bullet));
					enemy->Kill();
					//enemies.erase(std::find(enemies.begin(), enemies.end(), enemy)););
					bulletsToRemove.push_back(bullet);
					enemiesToRemove.push_back(enemy);

				}
			}
		}


		// Удаляем пули из основного списка
		PO->shots.erase(
			std::remove_if(PO->shots.begin(), PO->shots.end(),
				[&bulletsToRemove](const Bullet::Object::SP& bullet) {
					return std::find(bulletsToRemove.begin(), bulletsToRemove.end(), bullet) != bulletsToRemove.end();
				}),
			PO->shots.end()
		);

		// Удаляем врагов из основного списка
		enemies.erase(
			std::remove_if(enemies.begin(), enemies.end(),
				[&enemiesToRemove](const Enemy::Object::SP& enemy) {
					return std::find(enemiesToRemove.begin(), enemiesToRemove.end(), enemy) != enemiesToRemove.end();
				}),
			enemies.end()
		);



		/*for (size_t i = 0; i <; i++)
		{

		}*/
		/*for (size_t i = 0; i < PO->shots.size(); i++)
		{
			ML::Box2D shot = PO->shots[i]->res->hitBase.OffsetCopy(PO->shots[i]->pos.x, PO->shots[i]->pos.y);
			if (EO->gamestate == Enemy::GameState::Normal) {
				ML::Box2D you = EO->res->hitBase.OffsetCopy(EO->pos.x, EO->pos.y);
				if (you.Hit(shot)) {
					EO->gamestate = Enemy::GameState::Non;
					PO->shots[i]->gamestate = Bullet::GameState::Non;
					PO->shots[i]->Kill();
					EO->Kill();

				}
			}
		}*/
		/*ML::Box2D bull = PO->shot->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		if (EO->gamestate == Enemy::GameState::Normal) {
			ML::Box2D you = EO->res->hitBase.OffsetCopy(EO->pos.x, EO->pos.y);
			if (you.Hit(bull)) {
				//PO->gamestate = Player::GameState::Non;
				EO->gamestate = Enemy::GameState::Non;
				//PO->Kill();
				EO->Kill();
				this->Kill();
			}
		}*/
		if (PO->gamestate == Player::GameState::Non) {
			enemies.clear();
			ge->KillAll_G("Enemy");
		}
		if (inp.ST.down) {
			ge->KillAll_G("Enemy");
			this->Kill();
		}
		
	}

	void removeAndShift(std::vector<int>& vec, size_t index) {
		// Проверяем, что индекс в пределах вектора
		if (index < vec.size()) {
			// Сдвигаем элементы на одну позицию влево, начиная с удаляемого индекса
			for (size_t i = index; i < vec.size() - 1; ++i) {
				vec[i] = vec[i + 1];
			}
			// Удаляем последний элемент (он стал лишним после сдвига)
			vec.pop_back();
		}
	}
	//-------------------------------------------------------------------
	//Ѓu‚Q‚c•`‰жЃv‚PѓtѓЊЃ[ѓЂ–€‚ЙЌs‚¤Џ€—ќ
	void  Object::Render2D_AF()
	{
	}

	//ЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљ
	//€И‰є‚НЉо–{“I‚Й•ПЌX•s—v‚ИѓЃѓ\ѓbѓh
	//ЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљЃљ
	//-------------------------------------------------------------------
	//ѓ^ѓXѓNђ¶ђ¬‘‹Њы
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ѓQЃ[ѓЂѓGѓ“ѓWѓ“‚Й“o^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//ѓCѓjѓVѓѓѓ‰ѓCѓY‚ЙЋё”s‚µ‚Ѕ‚зKill
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
	//ѓЉѓ\Ѓ[ѓXѓNѓ‰ѓX‚Мђ¶ђ¬
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