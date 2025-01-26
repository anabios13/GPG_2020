#include "Task_Coin.h"

#include  "MyPG.h"
#include "myLib.h"
#include <chrono> // Для работы с таймерами
namespace Coin {
    Resource::WP  Resource::instance;
    //// Инициализация ресурса (картинка  монетки)
    bool Resource::Initialize() {
        this->img = DG::Image::Create("./data/Image/Coin.png");
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

    void Coin::Object::UpDate() {
        static int buffer = 1; // Текущее состояние анимации
        static bool repeatOne = false; // Флаг для второго появления 1
        static auto lastUpdate = std::chrono::steady_clock::now(); // Время последнего обновления

        // Двигаем объект влево
        this->pos.x -= this->speed;

        // Получаем текущее время
        auto now = std::chrono::steady_clock::now();

        // Вычисляем прошедшее время в миллисекундах
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate).count();

        // Проверяем, прошло ли заданное время (например, 70 миллисекунд)
        if (elapsed >= 100) {
            if (buffer == 1 && !repeatOne) {
                // Первый раз выводим 1
                this->res->img->ReLoad("./data/Image/" + std::to_string(buffer) + ".png");
                repeatOne = true; // Устанавливаем флаг для второго 1
            }
            else {
                if (buffer != 4) {
                    // Обычное увеличение buffer
                    this->res->img->ReLoad("./data/Image/" + std::to_string(buffer) + ".png");
                    buffer++;
                    repeatOne = false; // Сбрасываем флаг
                }
                else {
                    // Если buffer равен 4, возвращаемся к 1
                    this->res->img->ReLoad("./data/Image/" + std::to_string(buffer) + ".png");
                    buffer = 1;
                    repeatOne = false; // Сбрасываем флаг для нового цикла
                }
            }

            // Обновляем время последнего вызова
            lastUpdate = now;
        }

        // Уничтожаем объект, если он вышел за пределы экрана
        if (this->pos.x < -100) {
            this->Kill();
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
