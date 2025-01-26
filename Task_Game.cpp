//-------------------------------------------------------------------
//ѓQЃ[ѓЂ–{•Т
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include <iostream>
#include <functional>
#include <random>
namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//ѓЉѓ\Ѓ[ѓX‚МЏ‰Љъ‰»
	bool  Resource::Initialize()
	{
		
		 this->font = DG::Font::Create("PixelifySans", 16, 16, 400U, ANSI_CHARSET); // 32 - размер шрифта
		 if (!this->font) {
			 std::cerr << "Ошибка: не удалось создать шрифт PixelifySans!" << std::endl;
		 }

		 // Загрузка звукового эффекта
		 this->soundEffect = DM::Sound::CreateSE("./data/sounds/explosion.wav");
		 if (!soundEffect) {
			 std::cerr << "Ошибка: не удалось загрузить звуковой файл!" << std::endl;
			 return -1;
		 }

		 // Загрузка звукового эффекта
		 this->soundCoin = DM::Sound::CreateSE("./data/sounds/coin.wav");
		 if (!soundCoin) {
			 std::cerr << "Ошибка: не удалось загрузить звуковой файл!" << std::endl;
			 return -1;
		 }

		 // Загрузка звукового эффекта
		 this->soundBackground = DM::Sound::CreateSE("./data/sounds/music.wav");
		 if (!soundEffect) {
			 std::cerr << "Ошибка: не удалось загрузить звуковой файл!" << std::endl;
			 return -1;
		 }
		 

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
		this->res->soundBackground->Play_Normal(true);
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
			next->score = score;
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//ЃuЌXђVЃv‚PѓtѓЊЃ[ѓЂ–€‚ЙЌs‚¤Џ€—ќ
	void  Object::UpDate()
	{
		
		
		auto inp = ge->in1->GetState( );
		std::random_device rd;  // Может использоваться для получения случайного значения из аппаратного генератора
		std::mt19937 gen(rd()); // Инициализация Mersenne Twister генератора случайных чисел
		std::uniform_int_distribution<> ydis(0, 205);
		std::uniform_int_distribution<> ecount(0, 3);
		std::uniform_int_distribution<> dis(0, 2); // Случайные числа от 0 до 10 включительно
		std::uniform_int_distribution<> dis1(0, 5);
		std::vector<Enemy::Object::SP> enemiesToRemove;
		std::vector<Bullet::Object::SP> bulletsToRemove;
		std::vector<Coin::Object::SP> coinsToRemove;
		static int updateCounter = 0; // Ñ÷¸ò÷èê âûçîâîâ ìåòîäà Update()
		//int val1=rand
		updateCounter++; // Óâåëè÷èâàåì ñ÷¸ò÷èê

		// Åñëè ïðîøëî 3 ñåêóíäû (3 âûçîâà Update)
		if (updateCounter >= 100) 
{
			
			if (dis(gen) == dis1(gen))
			{
				auto co = Coin::Object::Create(true);
				if (co) {
					// Óñòàíàâëèâàåì ïîçèöèþ âðàãà
					co->pos.x = 540.0f; // X-êîîðäèíàòà ôèêñèðîâàíà
					co->pos.y = ydis(gen);
					// Óñòàíàâëèâàåì ðàçìåðû õèòáîêñà
					co->res->hitBase.h = 10;
					co->res->hitBase.w = 32;

					// Äîáàâëÿåì âðàãà â ìàññèâ
					coins.push_back(co);
				}
			}
			//deb++;
			updateCounter = 0; // Ñáðàñûâàåì ñ÷¸ò÷èê

			// Ãåíåðèðóåì ñëó÷àéíîå êîëè÷åñòâî âðàãîâ (îò 1 äî 3)
			int enemyCount = ecount(gen); //1 + std::rand() % 3;


			for (int i = 0; i < enemyCount; i++) {
				auto en = Enemy::Object::Create(true);
				if (en) {
					// Óñòàíàâëèâàåì ïîçèöèþ âðàãà
					en->pos.x = 540.0f; // X-êîîðäèíàòà ôèêñèðîâàíà
					en->pos.y = std::rand() % (238 - 32); // Ñëó÷àéíàÿ ïîçèöèÿ ïî Y â ïðåäåëàõ èãðîâîãî ïîëÿ
					//en->pos.y = ydis(gen);
					// Óñòàíàâëèâàåì ðàçìåðû õèòáîêñà
					en->res->hitBase.h = 32;
					en->res->hitBase.w = 32;

					// Äîáàâëÿåì âðàãà â ìàññèâ
					enemies.push_back(en);
				}
			}
		}

		ML::Box2D me = PO->res->hitBase;
		me.x = PO->pos.x;
		me.y = PO->pos.y;
		me.h += 10;
		me.w += 10;
		for (auto enemy : enemies)
		{
			if (enemy->gamestate == Enemy::GameState::Normal) {
				ML::Box2D you = enemy->res->hitBase;
				you.x = enemy->pos.x;
				you.y = enemy->pos.y;
				if (you.Hit(me)) {
					PO->gamestate = Player::GameState::Non;
					enemy->gamestate = Enemy::GameState::Non;
					PO->Kill();
					enemy->Kill();
					this->Kill();

				}
			}
		}
		for (auto coin : coins)
		{
			if (coin->gamestate == Coin::GameState::Normal) {
				ML::Box2D you = coin->res->hitBase;
				you.x = coin->pos.x - 10;
				you.y = coin->pos.y - 16;
				you.h = 32;
				you.w = 32;

				if (you.Hit(me)) {
					coin->gamestate = Coin::GameState::Non;
					coin->Kill();
					coinsToRemove.push_back(coin);
					score += 5;
					this->res->soundCoin->Play_Normal(false);
				}
			}
		}

		for(auto& enemy : enemies)
		{
			ML::Box2D me = enemy->res->hitBase;
			me.x = enemy->pos.x+20;
			me.y = enemy->pos.y+25;
			me.h -= 10;
			for (auto& bullet : PO->shots) {
				ML::Box2D you = bullet->res->hitBase;
				you.x= bullet->pos.x;
				you.y = bullet->pos.y;
				if (me.Hit(you)&& enemy->gamestate== Enemy::GameState::Normal) {
					bullet->gamestate = Bullet::GameState::Non;
					enemy->gamestate = Enemy::GameState::Non;
					ML::Color color(1, 1, 1, 1); // Белый цвет (RGBA)

					this->res->font->Draw(you, "AAAAAAAAAAAAAAAAAAA", color);
					bullet->Kill();
					enemy->Kill();
					if (bullet != previousBullet) {
						score++;  
						this->res->soundEffect->Play_Normal(false);
						previousBullet = bullet;
					}
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
		coins.erase(
			std::remove_if(coins.begin(), coins.end(),
				[&coinsToRemove](const Coin::Object::SP& coin) {
					return std::find(coinsToRemove.begin(), coinsToRemove.end(), coin) != coinsToRemove.end();
				}),
			coins.end()
		);

		if (PO->gamestate == Player::GameState::Non) {
			enemies.clear();
			ge->KillAll_G("Enemy");
			ge->KillAll_G("Bullet");
			ge->KillAll_G("Coin");
			this->Kill();
		}
		if (inp.ST.down) {
			ge->KillAll_G("Enemy");
			ge->KillAll_G("Bullet");
			ge->KillAll_G("Coin");
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
	void Object::Render2D_AF() {
		if (!res || !res->font) return; // Проверяем, что шрифт загружен

		// Пример строки текста
		std::string text = "score ";
		text += std::to_string(score);
		ML::Box2D textBox(ge->screen2DWidth - 150, 10, 200, 16); // Позиция текста (x, y, ширина, высота)
		ML::Color color(1, 1, 1, 1); // Белый цвет (RGBA)

		// Вывод текста
		res->font->Draw(textBox, text, color);
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