#include "Task_Bullet.h"

#include  "MyPG.h"
#include "myLib.h"
namespace Bullet {
    Resource::WP  Resource::instance;
    //// Инициализация ресурса (картинка врага)
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

        std::srand(std::time(nullptr));
        this->res = Resource::Create();
        this->speed = 1.0f;//1.0f
        this->render2D_Priority[1] = 0.5f;
        this->gamestate = GameState::Normal;
        return true;
    }

    // Завершение работы объекта (врага)
    bool Object::Finalize() {
        return true;
    }

    Object::~Object() { this->Finalize(); }

    //// Обновление позиции врага
    void Object::UpDate() {
        this->pos.x += this->speed;  // Двигается вправо

        if (this->pos.x > 570) {
            this->Kill();
        }
    }

    // Отрисовка врага
    void Object::Render2D_AF() {
        ML::Box2D draw(16, 16, 16, 16);  
        draw.Offset(this->pos);
        ML::Box2D src(0, 0, 8, 12);
        this->res->hitBase = draw;
        // Источник изображения
        this->res->img->Draw(draw, src);
    }
}
