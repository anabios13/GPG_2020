#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//ƒQ[ƒ€–{•Ò
//-------------------------------------------------------------------
#include "GameEngine_Ver3_83.h"
#include  "Task_GameBG.h"
#include  "Task_Player.h"
#include  "Task_Ending.h"
#include  "Task_Enemy.h"
namespace  Game
{
	//ƒ^ƒXƒN‚ÉŠ„‚è“–‚Ä‚éƒOƒ‹[ƒv–¼‚ÆŒÅ—L–¼
	const  string  defGroupName("–{•Ò");	//ƒOƒ‹[ƒv–¼
	const  string  defName(		"“Š‡");	//ƒ^ƒXƒN–¼
	//-------------------------------------------------------------------
	class  Resource : public BResource
	{
		bool  Initialize()	override;
		bool  Finalize()	override;
		Resource();
	public:
		~Resource();
		typedef  shared_ptr<Resource>	SP;
		typedef  weak_ptr<Resource>		WP;
		static   WP  instance;
		static  Resource::SP  Create();
		//‹¤—L‚·‚é•Ï”‚Í‚±‚±‚É’Ç‰Á‚·‚é
		DG::Image::SP	img;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		//•ÏX•s‰ÂŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸ
	public:
		virtual  ~Object();
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//¶¬‘‹Œû ˆø”‚Ítrue‚Åƒ^ƒXƒNƒVƒXƒeƒ€‚Ö©“®“o˜^
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;
	private:
		Object();
		bool  B_Initialize();
		bool  B_Finalize();
		bool  Initialize();	//u‰Šú‰»vƒ^ƒXƒN¶¬‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
		void  UpDate()			override;	//uÀsv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
		void  Render2D_AF()		override;	//u2D•`‰æv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
		bool  Finalize();	//uI—¹vƒ^ƒXƒNÁ–Å‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
		Player::Object::SP PO;
		GameBG::Object::SP BG;
		// ÌÍÎÆÅÑÒÂÎ âğàãîâ
		std::vector<Enemy::Object::SP> enemies;
		std::vector<Bullet::Object::SP> bullets;
	private:
		// Ïğîâåğêà êîëëèçèé
		void CheckCollisionPlayerEnemies();
		void CheckCollisionBulletEnemies();
		void DrawRec(const ML::Box2D& box, const  ML::Color color);
	};
}