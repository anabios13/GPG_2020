#include "Task_Coin.h"

#include  "MyPG.h"
#include "myLib.h"
namespace Coin {
    Resource::WP  Resource::instance;
    //// Инициализация ресурса (картинка  монетки)
    bool Resource::Initialize() {
        this->img = DG::Image::Create("./data/Image/coin_yellow.png");
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
        this->pos.x = 150;  // Враг появляется с правой стороны экрана
        this->pos.y = (std::rand() % (270 - 32 + 1));  // Случайная высота
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
        this->pos.x -= this->speed;  // Двигается вправо
        static int updateCounter = 0; // Ñ÷¸ò÷èê âûçîâîâ ìåòîäà Update()
        //int val1=rand
        updateCounter++; // Óâåëè÷èâàåì ñ÷¸ò÷èê
       
        if (this->pos.x <-100) {
            this->Kill();  // Уничтожаем врага, если он вышел за пределы экранаa
        }
        if (updateCounter >= 70) {
            if (buffer != 4) {
                this->res->img->ReLoad("./data/Image/" + to_string(buffer) + ".png");
                buffer++;
                updateCounter = 0;
                return;
            }
            if (buffer == 4) {
                this->res->img->ReLoad("./data/Image/" + to_string(buffer) + ".png");
                buffer = 1;
                updateCounter = 0;
                return;

            }
        }
    }

    // Отрисовка врага
    void Object::Render2D_AF() {
       
        ML::Box2D draw(0, 0, 32, 32);  // Размеры врага
/*        draw = get_src();*/  // Размеры врага
        draw.Offset(this->pos);
        src  = ML::Box2D(0, 0, 16, 16);//0,0,32,32
        /*ML::Box2D src = get_src();*/
        this->res->hitBase = draw;
        // Источник изображения
        this->res->img->Draw(draw, src);
    }
}
