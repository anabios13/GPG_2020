//#include "Task_Enemy.h"
//
//#include  "MyPG.h"
//
//namespace Enemy {
//    // ������������� ������� (�������� �����)
//    bool Resource::Initialize() {
//        this->img = DG::Image::Create("./data/Image/Chara00.png");
//        return true;
//    }
//
//    bool Resource::Finalize() {
//        this->img.reset();
//        return true;
//    }
//
//    Resource::Resource() {}
//    Resource::~Resource() { this->Finalize(); }
//
//    shared_ptr<Resource> Resource::Create() {
//        if (auto sp = instance.lock()) {
//            return sp;
//        }
//        else {
//            sp = make_shared<Resource>();
//            if (sp) {
//                sp->Initialize();
//                instance = sp;
//            }
//            return sp;
//        }
//    }
//
//    // �������� �����
//    Object::SP Object::Create(bool flagGameEnginePushBack_) {
//        Object::SP ob = make_shared<Object>();
//        if (ob) {
//            if (flagGameEnginePushBack_) {
//                ge->PushBack(ob);  // ��������� � ������� �������
//            }
//            //if (!ob->B_Initialize()) {
//            //    ob->Kill();  // ����������, ���� ������������� �� �������
//            //}
//            return ob;
//        }
//        return nullptr;
//    }
//
//    // ������������� �����
//    bool Object::Initialize() {
//        this->res = Resource::Create();
//        this->pos.x = 640;  // ���� ���������� � ������ ������� ������
//        this->pos.y = rand() % 480;  // ��������� ������
//        this->speed = 2.0f;
//        return true;
//    }
//
//    // ���������� ������ ������� (�����)
//    bool Object::Finalize() {
//        return true;
//    }
//
//    // ���������� ������� �����
//    void Object::UpDate() {
//        this->pos.x -= this->speed;  // ��������� �����
//
//        //// �������� ������������ � �������
//        //if (ML::Collision::CheckRect(this->pos, 32, 32, Player::Object::Create(true)->pos, 32, 32)) {
//        //    // ������������ � �������, ���������� ��� �������
//        //    this->Kill();
//        //    Player::Object::Create(true)->Kill();
//        //}
//
//        if (this->pos.x < 0) {
//            this->Kill();  // ���������� �����, ���� �� ����� �� ������� ������
//        }
//    }
//
//    // ��������� �����
//    void Object::Render2D_AF() {
//        ML::Box2D draw(32, 32, 32, 32);  // ������� �����
//        draw.Offset(this->pos);
//        ML::Box2D src(0, 0, 32, 32);  // �������� �����������
//     /*   this->res->img->Draw(draw, src);*/
//    }
//}
