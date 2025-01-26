#include "Task_Bullet.h"

#include  "MyPG.h"
#include "myLib.h"
namespace Bullet {
    Resource::WP  Resource::instance;
    //// ������������� ������� (�������� �����)
    bool Resource::Initialize() {
        this->img = DG::Image::Create("./data/Image/shot.png");
        return true;
    }

    bool Resource::Finalize() {
        this->img.reset();
        return true;
    }
    Resource::~Resource() { this->Finalize(); }

    Resource::SP  Resource::Create() {
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

    // �������� �����
    Object::SP Object::Create(bool flagGameEnginePushBack_) {
        Object::SP ob = Object::SP(new  Object());
        if (ob) {
            if (flagGameEnginePushBack_) {
                ge->PushBack(ob);  // ��������� � ������� �������
            }
            if (!ob->Initialize()) {
                ob->Kill();  // ����������, ���� ������������� �� �������
            }
            return ob;
        }
        return nullptr;
    }

    // ������������� �����
    bool Object::Initialize() {
        __super::Initialize(defGroupName, defName, true);

        std::srand(std::time(nullptr));
        this->res = Resource::Create();
      //  this->pos.x = 150;  // ���� ���������� � ������ ������� ������
       // this->pos.y = (std::rand() % (270 - 32 + 1));  // ��������� ������
        this->speed = 1.0f;//1.0f
        this->render2D_Priority[1] = 0.5f;
        this->gamestate = GameState::Normal;
        return true;
    }

    // ���������� ������ ������� (�����)
    bool Object::Finalize() {
        return true;
    }

    Object::~Object() { this->Finalize(); }

    //// ���������� ������� �����
    void Object::UpDate() {
        this->pos.x += this->speed;  // ��������� ������

        //// �������� ������������ � �������
        //ML::Collsion::
        //if (ML::Collision::CheckRect(this->pos, 32, 32, Player::Object::Create(true)->pos, 32, 32)) {
        //    // ������������ � �������, ���������� ��� �������
        //    this->Kill();
        //    Player::Object::Create(true)->Kill();
        //}

        if (this->pos.x > 700) {
            gamestate = GameState::Non;
            this->Kill();  // ���������� �����, ���� �� ����� �� ������� ������a
        }
    }

    // ��������� �����
    void Object::Render2D_AF() {
        ML::Box2D draw(16, 16, 16, 16);  // ������� �����
        draw.Offset(this->pos);
        ML::Box2D src(0, 0, 8, 12);
        this->res->hitBase = draw;
        // �������� �����������
        this->res->img->Draw(draw, src);
    }
}
