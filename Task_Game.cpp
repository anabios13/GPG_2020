//-------------------------------------------------------------------
//�Q�[���{��
//-------------------------------------------------------------------
#include  "MyPG.h"
#include  "Task_Game.h"
#include <iostream>

namespace  Game
{
	Resource::WP  Resource::instance;
	//-------------------------------------------------------------------
	//���\�[�X�̏�����
	bool  Resource::Initialize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//���\�[�X�̉��
	bool  Resource::Finalize()
	{
		return true;
	}
	//-------------------------------------------------------------------
	//�u�������v�^�X�N�������ɂP�񂾂��s������
	bool  Object::Initialize()
	{
		//�X�[�p�[�N���X������
		__super::Initialize(defGroupName, defName, true);
		//���\�[�X�N���X����or���\�[�X���L
		this->res = Resource::Create();

		//���f�[�^������
		
		//���^�X�N�̐���
		//�w�i�^�X�N
		//auto  bg = GameBG::Object::Create(true);
		//�v���C��
		//auto  pl = Player::Object::Create(true);
		//auto en = Enemy::Object::Create(true);
		BG= GameBG::Object::Create(true);
		PO= Player::Object::Create(true);
		// ������ ����� ������ (������: 5 ����)
		for (int i = 0; i < 4; ++i)
		{
			auto en = Enemy::Object::Create(true);
			if (en) {
				// ������ ��������� �������
				en->pos.x = 200.0f ;
				en->pos.y = i * 42.0f;
				enemies.push_back(en);

			}
	
		}

		return true;
		return  true;
	}
	//-------------------------------------------------------------------
	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
	bool  Object::Finalize()
	{
		//���f�[�^���^�X�N���
		ge->KillAll_G("�{��");
		ge->KillAll_G("�v���C��");

		if (!ge->QuitFlag() && this->nextTaskCreate) {
			//�������p���^�X�N�̐���
			auto next = Ending::Object::Create(true);
		}

		return  true;
	}
	//-------------------------------------------------------------------
	//�u�X�V�v�P�t���[�����ɍs������
	void  Object::UpDate()
	{
		enemies[0] = nullptr;
		auto inp = ge->in1->GetState( );
	//	ML::Box2D me = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		CheckCollisionPlayerEnemies();

		if (inp.ST.down) {//s key
			//���g�ɏ��ŗv��
			this->Kill();
		}
		
	}

	void Object::CheckCollisionPlayerEnemies()
	{
		// ���� ����� ��� ����, �� ���������
		if (!PO || PO->gamestate!=Player::GameState::Normal) return;

		// ������� ������
		ML::Box2D playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
		
		// ���������� ���� ������
		for (int i=0; i<enemies.size();i++)
		{

			if (enemies[i]->gamestate != Enemy::GameState::Normal) continue;

			// ������� �����
			ML::Box2D enemyBox = enemies[i]->res->hitBase.OffsetCopy(enemies[i]->pos.x, enemies[i]->pos.y);
			playerBox = PO->res->hitBase.OffsetCopy(PO->pos.x, PO->pos.y);
			std::cout << enemies[i]->pos.x << " " << enemies[i]->pos.y;

			if (enemyBox.Hit(playerBox))
			{
				// �������� ����� ��� ��������
				PO->gamestate = Player::GameState::Non;
				enemies[i]->gamestate = Enemy::GameState::Non;

				// �������� Kill(), ���� ��� �����
				PO->Kill();
				enemies[i]->Kill();

				// �, � �������, ��������� ��� Task_Game
				this->Kill();

				// ��������� ����, ����� �� ��������� ������
				break;
			}
		}
	}

	//-------------------------------------------------------------------
	//�u�Q�c�`��v�P�t���[�����ɍs������
	void  Object::Render2D_AF()
	{
	}

	//������������������������������������������������������������������������������������
	//�ȉ��͊�{�I�ɕύX�s�v�ȃ��\�b�h
	//������������������������������������������������������������������������������������
	//-------------------------------------------------------------------
	//�^�X�N��������
	Object::SP  Object::Create(bool  flagGameEnginePushBack_)
	{
		Object::SP  ob = Object::SP(new  Object());
		if (ob) {
			ob->me = ob;
			if (flagGameEnginePushBack_) {
				ge->PushBack(ob);//�Q�[���G���W���ɓo�^
			}
			if (!ob->B_Initialize()) {
				ob->Kill();//�C�j�V�����C�Y�Ɏ��s������Kill
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
	//���\�[�X�N���X�̐���
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