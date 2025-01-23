#pragma warning(disable:4996)
#pragma once
#include "GameEngine_Ver3_83.h"
#include "Task_Player.h"  // ��� �������� ������������ � �������
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
		////���L����ϐ��͂����ɒǉ�����
		DG::Image::SP	img;
		ML::Box2D hitBase;
	};
	//-------------------------------------------------------------------
	class  Object : public  BTask
	{
		//�ύX�s����������������������������������������������������
	public:
		virtual  ~Object();
		float speed;
		ML::Point		pos;
		typedef  shared_ptr<Object>		SP;
		//typedef  weak_ptr<Object>		WP;
		////�������� ������true�Ń^�X�N�V�X�e���֎����o�^
		static  Object::SP  Create(bool flagGameEnginePushBack_);
		Resource::SP	res;

		GameState gamestate;
	private:
		Object() = default;
		//bool  B_Initialize(); // �� �����
		//bool  B_Finalize(); // �� �����
		bool  Initialize();	//�u�������v�^�X�N�������ɂP�񂾂��s������
		void  UpDate()			override;	//�u���s�v�P�t���[�����ɍs������
		void  Render2D_AF()		override;	//�u2D�`��v�P�t���[�����ɍs������
		bool  Finalize();	//�u�I���v�^�X�N���Ŏ��ɂP�񂾂��s������
		
		//�ύX������������������������������������������������������
	};
}
