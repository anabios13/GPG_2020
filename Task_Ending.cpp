//-------------------------------------------------------------------
//ƒGƒ“ƒfƒBƒ“ƒO
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Ending.h"
#include  "Task_Title.h"
#include <iostream>

namespace  Ending
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//ƒŠƒ\[ƒX‚Ì‰Šú‰»
	bool  Resource::Initialize()
	{
		this->img = DG::Image::Create("./data/image/Ending.bmp");
		this->font = DG::Font::Create("PixelifySans", 16, 16, 400U, ANSI_CHARSET); // 32 - ðàçìåð øðèôòà
		if (!this->font) {
			MessageBox(0, "Error: can't load font PixelifySans!", 0, MB_OK);
			//std::cerr << "Error: can't load font PixelifySans!" << std::endl;
		}
		return true;
	}
	//-------------------------------------------------------------------
	//ƒŠƒ\[ƒX‚Ì‰ð•ú
	bool  Resource::Finalize()
	{
		this->img.reset();
		this->font.reset();
		return true;
	}
	//-------------------------------------------------------------------
	//u‰Šú‰»vƒ^ƒXƒN¶¬Žž‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
	bool  Object::Initialize()
	{
		//ƒX[ƒp[ƒNƒ‰ƒX‰Šú‰»
		__super::Initialize(defGroupName, defName, true);
		//ƒŠƒ\[ƒXƒNƒ‰ƒX¶¬orƒŠƒ\[ƒX‹¤—L
		this->res = Resource::Create();

		//šƒf[ƒ^‰Šú‰»
		this->logoPosY = 0;
	//	auto message = std::string("you are winning, your score :");
	//	message.append(std::to_string(score));
	//	message.append(" press s to resart game");
	//	messageBox(0, message.data(), 0, MB_OK);
		//šƒ^ƒXƒN‚Ì¶¬

		return  true;
	}
	//-------------------------------------------------------------------
	//uI—¹vƒ^ƒXƒNÁ–ÅŽž‚É‚P‰ñ‚¾‚¯s‚¤ˆ—
	bool  Object::Finalize()
	{
		//šƒf[ƒ^•ƒ^ƒXƒN‰ð•ú


		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//šˆø‚«Œp‚¬ƒ^ƒXƒN‚Ì¶¬
			auto  nextTask = Title::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//uXVv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
	void  Object::UpDate()
	{
		auto inp = ge->in1->GetState();

		this->logoPosY -= 9;
		if (this->logoPosY <= 0) {
			this->logoPosY = 0;
		}

		if (this->logoPosY == 0) {
			if (inp.ST.down) {
				//Ž©g‚ÉÁ–Å—v¿
				this->Kill();
			}
		}
	}
	//-------------------------------------------------------------------
	//u‚Q‚c•`‰æv‚PƒtƒŒ[ƒ€–ˆ‚És‚¤ˆ—
	void  Object::Render2D_AF()
	{
		ML::Box2D  draw(0, 0, 480, 270);
		ML::Box2D  src(0, 0, 816, 480);
		if (!res || !res->font) return;

		// Ïðèìåð ñòðîêè òåêñòà
		std::string text("your score is ");
		
		text.append(std::to_string(score));

		ML::Box2D textBox((int)(ge->screen2DWidth - 290), 10, 240, 16); // Ïîçèöèÿ òåêñòà (x, y, øèðèíà, âûñîòà)
		ML::Color color(255, 1, 1, 1); // Áåëûé öâåò (RGBA)

		draw.Offset(0, this->logoPosY);
		this->res->img->Draw(draw, src);
		this->res->font->Draw(textBox, text, color);
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
				ob->Kill();//ƒCƒjƒVƒƒƒ‰ƒCƒY‚ÉŽ¸”s‚µ‚½‚çKill
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