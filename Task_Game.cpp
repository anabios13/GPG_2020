//-------------------------------------------------------------------
//ГQБ[ГАЦ{Х“
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include "myLib.h"
#include <iostream>

namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//ГКГ\Б[ГXВћПЙКъЙї
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//ГКГ\Б[ГXВћЙрХъ
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//БuПЙКъЙїБvГ^ГXГNРґРђОЮВ…ВPЙсВЊВѓНsВ§ПИЧЭ
	bool  Object::Initialize()
	{
		//ГXБ[ГpБ[ГNГЙГXПЙКъЙї
		__super::Initialize(defGroupName, defName, true);
		//ГКГ\Б[ГXГNГЙГXРґРђorГКГ\Б[ГXЛ§ЧL
		this->res = Resource::Create();

		//БЪГfБ[Г^ПЙКъЙї
		
		//БЪГ^ГXГNВћРґРђ
		//ФwМiГ^ГXГN
		//auto  bg = GameBG::Object::Create(true);
		//ГvГМГCГД
		//auto  pl = Player::Object::Create(true);
		//auto en = Enemy::Object::Create(true);
		BG= GameBG::Object::Create(true);
		PO= Player::Object::Create(true);
		// —оздаЄм много врагов (пример: 5 штук)
		//for (int i = 0; i < 3; i++)
		//{
		//	auto en = Enemy::Object::Create(true);
		//	if (en) {
		//		// ѕример установки позиции
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
	//БuПIЧєБvГ^ГXГNПЅЦ≈ОЮВ…ВPЙсВЊВѓНsВ§ПИЧЭ
	bool  Object::Finalize()
	{
		//БЪГfБ[Г^БХГ^ГXГNЙрХъ
		ge->KillAll_G("Ц{Х“");
		ge->KillAll_G("ГvГМГCГД");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//БЪИшВЂМpВђГ^ГXГNВћРґРђ
			auto next = Ending::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//БuНXРVБvВPГtГМБ[ГАЦИВ…НsВ§ПИЧЭ
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState( );
		static int updateCounter = 0; // —чЄтчик вызовов метода Update()

		updateCounter++; // ”величиваем счЄтчик

		// ≈сли прошло 3 секунды (3 вызова Update)
		if (updateCounter >= 100) {
			updateCounter = 0; // —брасываем счЄтчик

			// √енерируем случайное количество врагов (от 1 до 3)
			int enemyCount = 1 + std::rand() % 3;

			for (int i = 0; i < enemyCount; i++) {
				auto en = Enemy::Object::Create(true);
				if (en) {
					// ”станавливаем позицию врага
					en->pos.x = 540.0f; // X-координата фиксирована
					en->pos.y = std::rand() % (270 - 32); // —лучайна€ позици€ по Y в пределах игрового пол€

					// ”станавливаем размеры хитбокса
					en->res->hitBase.h = 32;
					en->res->hitBase.w = 32;

					// ƒобавл€ем врага в массив
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
			//О©РgВ…ПЅЦ≈ЧvРњ
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

			// ’итбокс пули
			ML::Box2D bulletBox = bullets[i]->res->hitBase.OffsetCopy(bullets[i]->pos.x, bullets[i]->pos.y);
			bulletBox.h = 16;
			bulletBox.w = 16;
			bulletBox.x = bullets[i]->pos.x;
			bulletBox.y = bullets[i]->pos.y;

			// ѕеребираем всех врагов
			for (size_t j = 0; j < enemies.size(); ++j) {

				// ’итбокс врага
				ML::Box2D enemyBox = enemies[j]->res->hitBase.OffsetCopy(enemies[j]->pos.x, enemies[j]->pos.y);
				enemyBox.x = enemies[i]->pos.x;
				enemyBox.y = enemies[i]->pos.y;

				// ѕровер€ем столкновение
				if (bulletBox.Hit(enemyBox)) {
					// ≈сли столкновение, помечаем обоих как погибших
					bullets[i]->Kill();
					enemies[j]->Kill();

					// ”дал€ем пулю из массива
					bullets.erase(bullets.begin() + i);
					--i; // —мещаем индекс, чтобы не пропустить следующую пулю

					// ”дал€ем врага из массива
					enemies.erase(enemies.begin() + j);
					--j; // —мещаем индекс, чтобы не пропустить следующего врага

					// ¬ыходим из внутреннего цикла, так как текуща€ пул€ уже уничтожена
					break;
				}
			}
		}
	}

	void Object::CheckCollisionPlayerEnemies()
	{
		// ≈сли игрок уже мЄртв, не провер€ем
		if (!PO || PO->gamestate!=Player::GameState::Normal) return;

		// ’итбокс игрока
		ML::Box2D playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		// ѕеребираем ¬—≈’ врагов
		for (int i=0; i<enemies.size();i++)
		{

			// ’итбокс врага
			ML::Box2D enemyBox = enemies[i]->res->hitBase.OffsetCopy(enemies[i]->res->hitBase.x, enemies[i]->res->hitBase.y);
			enemyBox.x = enemies[i]->pos.x;
			enemyBox.y = enemies[i]->pos.y;
			playerBox = PO->res->hitBase.OffsetCopy(PO-> res->hitBase.x, PO->res->hitBase.y);
			playerBox.x = PO->pos.x;
			playerBox.y = PO->pos.y;

			if (enemyBox.Hit(playerBox))
			{
				// ѕомечаем обоих как погибших
				PO->gamestate = Player::GameState::Non;
				enemies[i]->gamestate = Enemy::GameState::Non;
				auto en = enemies[i];
				
				// ¬ызываем Kill(), если это нужно
				PO->Kill();

			

				// », к примеру, завершаем сам Task_Game
				this->Kill();

				// ѕрерываем цикл, чтобы не провер€ть дальше
				if (i < enemies.size()) {
					enemies.erase(enemies.begin() + i);
					en->Kill();
				}

				break;
			}
		}
	}

	//-------------------------------------------------------------------
	//БuВQВcХ`ЙжБvВPГtГМБ[ГАЦИВ…НsВ§ПИЧЭ
	void  Object::Render2D_AF()
	{
	}

	//БЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪ
	//И»ЙЇВЌКоЦ{УIВ…ХѕНXХsЧvВ»ГБГ\ГbГh
	//БЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪБЪ
	//-------------------------------------------------------------------
	//Г^ГXГNРґРђСЛМы
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//ГQБ[ГАГGГУГWГУВ…УoШ^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//ГCГjГVГГГЙГCГYВ…ОЄФsВµВљВзKill
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
	//ГКГ\Б[ГXГNГЙГXВћРґРђ
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