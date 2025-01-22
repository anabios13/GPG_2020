//#include "Task_Enemy.h"
//
//#include  "MyPG.h"
//
//namespace Enemy {
//    // Инициализация ресурса (картинка врага)
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
//    // Создание врага
//    Object::SP Object::Create(bool flagGameEnginePushBack_) {
//        Object::SP ob = make_shared<Object>();
//        if (ob) {
//            if (flagGameEnginePushBack_) {
//                ge->PushBack(ob);  // Добавляем в игровой процесс
//            }
//            //if (!ob->B_Initialize()) {
//            //    ob->Kill();  // Уничтожаем, если инициализация не удалась
//            //}
//            return ob;
//        }
//        return nullptr;
//    }
//
//    // Инициализация врага
//    bool Object::Initialize() {
//        this->res = Resource::Create();
//        this->pos.x = 640;  // Враг появляется с правой стороны экрана
//        this->pos.y = rand() % 480;  // Случайная высота
//        this->speed = 2.0f;
//        return true;
//    }
//
//    // Завершение работы объекта (врага)
//    bool Object::Finalize() {
//        return true;
//    }
//
//    // Обновление позиции врага
//    void Object::UpDate() {
//        this->pos.x -= this->speed;  // Двигается влево
//
//        //// Проверка столкновения с игроком
//        //if (ML::Collision::CheckRect(this->pos, 32, 32, Player::Object::Create(true)->pos, 32, 32)) {
//        //    // Столкновение с игроком, уничтожаем оба объекта
//        //    this->Kill();
//        //    Player::Object::Create(true)->Kill();
//        //}
//
//        if (this->pos.x < 0) {
//            this->Kill();  // Уничтожаем врага, если он вышел за пределы экрана
//        }
//    }
//
//    // Отрисовка врага
//    void Object::Render2D_AF() {
//        ML::Box2D draw(32, 32, 32, 32);  // Размеры врага
//        draw.Offset(this->pos);
//        ML::Box2D src(0, 0, 32, 32);  // Источник изображения
//     /*   this->res->img->Draw(draw, src);*/
//    }
//}
