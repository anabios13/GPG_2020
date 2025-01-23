#pragma warning(disable:4996)
#pragma once
#include "GameEngine_Ver3_83.h"
#include "Task_Player.h"  // Äëÿ ïğîâåğêè ñòîëêíîâåíèé ñ èãğîêîì
#include  "MyPG.h"

namespace Enemy {
    const string defGroupName("Enemy");
    const string defName("NoName");
	enum class GameState { Normal, Hit, Non };

	class  Resource : public BResource
	{
	public:

		bool  Initialize()	override;
		bool  Finalize()	override;
		Resource() = default;
		~Resource();
		typedef  shared_ptr<Resource>	SP;
		typedef  weak_ptr<Resource>		WP;
		static   WP  instance;
		static  Resource::SP  Create();
		////‹¤—L‚·‚é•Ï”‚Í‚±‚±‚É’Ç‰Á‚·‚é
		DG::Image::SP	img;
		ML::Box2D hitBase;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		//•ÏX•s‰ÂŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸ
	public:
		virtual  ~Object();
		float speed;
		ML::Point		pos;
		typedef  shared_ptr<Object>		SP;
		//typedef  weak_ptr<Object>		WP;
		////¶¬‘‹Œû ˆø”‚Ítrue‚Åƒ^ƒXƒNƒVƒXƒeƒ€‚Ö©“®“o˜^
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;

		GameState gamestate;
	private:
		Object() = default;
		//bool  B_Initialize(); // íå íóæåí
		//bool  B_Finalize(); // íå íóæåí
		bool  Initialize();	//u‰Šú‰»vƒ^ƒXƒN¶¬‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
		void  UpDate()			override;	//uÀsv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
		void  Render2D_AF()		override;	//u2D•`‰æv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
		bool  Finalize();	//uI—¹vƒ^ƒXƒNÁ–Å‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
		
		//•ÏX‰Â
	};
}
