//#pragma warning(disable:4996)
//#pragma once
//#include "GameEngine_Ver3_83.h"
//#include "Task_Player.h"  // Äëÿ ïðîâåðêè ñòîëêíîâåíèé ñ èãðîêîì
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
//		//¤L·éÏÍ±±ÉÇÁ·é
//		DG::Image::SP	img;
//	};
//	//-------------------------------------------------------------------
//	class  Object : public  BTask
//	{
//		//ÏXsÂ
//	public:
//		virtual  ~Object();
//		float speed;
//		typedef  shared_ptr<Object>		SP;
//		typedef  weak_ptr<Object>		WP;
//		//¶¬û øÍtrueÅ^XNVXeÖ©®o^
//		static  Object::SP  Create(bool flagGameEnginePushBack_);
//		Resource::SP	res;
//	private:
//		Object();
//		bool  B_Initialize();
//		bool  B_Finalize();
//		bool  Initialize();	//uú»v^XN¶¬ÉPñ¾¯s¤
//		void  UpDate()			override;	//uÀsvPt[És¤
//		void  Render2D_AF()		override;	//u2D`ævPt[És¤
//		bool  Finalize();	//uI¹v^XNÁÅÉPñ¾¯s¤
//		//ÏXÂ
//	public:
//		//ÇÁµ½¢ÏE\bhÍ±±ÉÇÁ·é
//		XI::GamePad::SP  controller;
//		ML::Point		pos;
//	};
//}
