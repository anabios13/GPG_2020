#pragma warning(disable:4996)
#pragma once
//-------------------------------------------------------------------
//�Q�[���{��
//-------------------------------------------------------------------
#include "GameEngine_Ver3_83.h"
#include  "Task_GameBG.h"
#include  "Task_Player.h"
#include  "Task_Ending.h"
#include  "Task_Enemy.h"
namespace  Game
{
	//�^�X�N�Ɋ��蓖�Ă�O���[�v���ƌŗL��
	const  string  defGroupName("�{��");	//�O���[�v��
	const  string  defName(		"����");	//�^�X�N��
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
		//���L����ϐ��͂����ɒǉ�����
		DG::Image::SP	img;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		//�ύX�s����������������������������������������������������
	public:
		virtual  ~Object();
		typedef  shared_ptr<Object>		SP;
		typedef  weak_ptr<Object>		WP;
		//�������� ������true�Ń^�X�N�V�X�e���֎����o�^
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;
	private:
		Object();
		bool  B_Initialize();
		bool  B_Finalize();
		bool  Initialize();	//�u�������v�^�X�N�������ɂP�񂾂��s������
		void  UpDate()			override;	//�u���s�v�P�t���[�����ɍs������
		void  Render2D_AF()		override;	//�u2D�`��v�P�t���[�����ɍs������
		bool  Finalize();	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
		Player::Object::SP PO;
		GameBG::Object::SP BG;
		// ��������� ������
		std::vector<Enemy::Object::SP> enemies;
		std::vector<Bullet::Object::SP> bullets;
	private:
		// �������� ��������
		void CheckCollisionPlayerEnemies();
		void CheckCollisionBulletEnemies();
		void DrawRec(const ML::Box2D& box, const  ML::Color color);
	};
}