//#pragma warning(disable:4996)
//#pragma once
//#include "GameEngine_Ver3_83.h"
//#include "Task_Player.h"  // Äëÿ ïğîâåğêè ñòîëêíîâåíèé ñ èãğîêîì
//#include  "MyPG.h"
//
//namespace Enemy {
//    const string defGroupName("Enemy");
//    const string defName("NoName");
//
//	class  Resource : public BResource
//	{
//		bool  Initialize()	override;
//		bool  Finalize()	override;
//		Resource();
//	public:
//		~Resource();
//		typedef  shared_ptr<Resource>	SP;
//		typedef  weak_ptr<Resource>		WP;
//		static   WP  instance;
//		static  Resource::SP  Create();
//		//‹¤—L‚·‚é•Ï”‚Í‚±‚±‚É’Ç‰Á‚·‚é
//		DG::Image::SP	img;
//	};
//	//-------------------------------------------------------------------
//	class  Object : public  BTask
//	{
//		//•ÏX•s‰ÂŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸŸ
//	public:
//		virtual  ~Object();
//		float speed;
//		typedef  shared_ptr<Object>		SP;
//		typedef  weak_ptr<Object>		WP;
//		//¶¬‘‹Œû ˆø”‚Ítrue‚Åƒ^ƒXƒNƒVƒXƒeƒ€‚Ö©“®“o˜^
//		static  Object::SP  Create(bool flagGameEnginePushBack_);
//		Resource::SP	res;
//	private:
//		Object();
//		bool  B_Initialize();
//		bool  B_Finalize();
//		bool  Initialize();	//u‰Šú‰»vƒ^ƒXƒN¶¬‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
//		void  UpDate()			override;	//uÀsv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
//		void  Render2D_AF()		override;	//u2D•`‰æv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
//		bool  Finalize();	//uI—¹vƒ^ƒXƒNÁ–Å‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
//		//•ÏX‰Â
//	public:
//		//’Ç‰Á‚µ‚½‚¢•Ï”Eƒƒ\ƒbƒh‚Í‚±‚±‚É’Ç‰Á‚·‚é
//		XI::GamePad::SP  controller;
//		ML::Point		pos;
//	};
//}
