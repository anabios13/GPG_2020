#include "Task_Enemy.h"

#include  "MyPG.h"

namespace Enemy {
    Resource::WP  Resource::instance;
    //// Инициализация ресурса (картинка врага)
    bool Resource::Initialize() {
        this->img = DG::Image::Create("./data/Image/Chara00.png");
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

    // Создание врага
    Object::SP Object::Create(bool flagGameEnginePushBack_) {
        Object::SP ob = Object::SP(new  Object());
        if (ob) {
            if (flagGameEnginePushBack_) {
                ge->PushBack(ob);  // Добавляем в игровой процесс
            }
            if (!ob->Initialize()) {
                ob->Kill();  // Уничтожаем, если инициализация не удалась
            }
            return ob;
        }
        return nullptr;
    }

    // Инициализация врага
    bool Object::Initialize() {
        __super::Initialize(defGroupName, defName, true);
        this->res = Resource::Create();
        this->pos.x = 150;  // Враг появляется с правой стороны экрана
        this->pos.y = 150;  // Случайная высота
        this->speed = 1.0f;
        this->render2D_Priority[1] = 0.5f;
        return true;
    }

    // Завершение работы объекта (врага)
    bool Object::Finalize() {
        return true;
    }

    Object::~Object() { this->Finalize(); }

    //// Обновление позиции врага
    void Object::UpDate() {
        this->pos.x -= this->speed;  // Двигается влево

        //// Проверка столкновения с игроком
        //if (ML::Collision::CheckRect(this->pos, 32, 32, Player::Object::Create(true)->pos, 32, 32)) {
        //    // Столкновение с игроком, уничтожаем оба объекта
        //    this->Kill();
        //    Player::Object::Create(true)->Kill();
        //}

        if (this->pos.x < -100) {
            this->Kill();  // Уничтожаем врага, если он вышел за пределы экрана
        }
    }

    // Отрисовка врага
    void Object::Render2D_AF() {
        ML::Box2D draw(32, 32, 32, 32);  // Размеры врага
        draw.Offset(this->pos);
        ML::Box2D src(0, 0, 100, 100);  // Источник изображения
        this->res->img->Draw(draw, src);
    }
}
