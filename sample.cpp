#include "FiguresRainPolygon.hpp"
#include "FiguresRainScene.hpp"

#include <vector>
#include <iostream>

using namespace std;

// Нужно задать ваши классы для описания фигур.
// Каждый класс унаследован от VisPolygon, реализует его интерфейс.
// Внутри класс может иметь любую реализацию.
// Здесь дан только быстрый и грязный пример для треугольника.

// Класс треугольника.
// Набор классов в решении *ваш* - что в них нужно, то и реализуете.
// Копировать этот класс *не* надо. Он тут только для примера.
// Как уже было сказано выше, это очень быстрый и грязный пример, просто чтобы показать технические приёмы.
class Triangle : public VisPolygon {
protected:
    // Например, храним только одну точку. Причём это даже не центр масс.
    // В данном примере фигура при движении считается равной вот этой самой некоторой её точке.
    // А все остальные вершины "дорисовываются" чисто на этапе построения картинки.
    double x;
    double y;
    // Некий характерный размер нашего треугольника.
    // Выражен в попугаях. Интерпретируется нашим кодом. Как именно - наше дело.
    // Этот параметр "в сыром виде" наружу не виден вообще.
    double size;
    // Скорость фигуры, куда же без неё
    double vx;
    double vy;

public:
    // Конструктор
    Triangle(double x, double y, double size, double vx, double vy) : x(x), y(y), size(size), vx(vx), vy(vy) {
    }

    // Далее какие-то ваши методы, никак не связанные с VisPolygon.
    // Например, в данном примере этот метод отвечает за движение нашего треугольника нашим движком.
    void move(double dt) {
        x += vx * dt;
        y += vy * dt;
    }

    // Ещё нужна реализация методов интерфейса на базе *ваших* переменных.
    // Переписывать всю свою реализацию под имена методов и полей из интерфейса *не* надо.
    // В данном примере вообще точки для визуализации "дорисовываются" на лету на базе одной хранимой точки.
    vector<VisPoint> getVertices() const override {
        vector<VisPoint> vertices = vector<VisPoint>(3);
        vertices[0] = VisPoint(x - size, y);
        vertices[1] = VisPoint(x + size, y);
        vertices[2] = VisPoint(x, y + size);
        return vertices;
    }
};

// Ваш класс сцены. В нём вся основная логика. Порождение и уничтожение фигур, обработка стенок - всё здесь.
// Класс унаследован от FiguresRainScene, реализует интерфейс с методами getNumberOfFigures / getFigure / doTimeStep.
class SampleScene : public FiguresRainScene {
protected:
    // В этом примере у нас сплошные треугольники.
    // В вашей реализации фигуры должны быть разные. Любые. Но разные.
    vector<Triangle> bodies;

public:
    // Далее реализация методов интерфейса на базе *ваших* данных

    unsigned int getNumberOfFigures() const override {
        return bodies.size();
    }

    const VisPolygon* getFigure(unsigned int number) const override {
        return &bodies.at(number);
    }

    void doTimeStep() override {
        for(Triangle& t : bodies)
            t.move(0.1);
    }

    // Далее, возможно, ещё какая-то куча ваших методов, с интерфейсом не связанных
    // ...

    // Какая-то работа по иниту, например.
    // Здесь у нас всего два треугольника во всей сцене. Ничего не порождается и не уничтожается. И никакого рандома.
    void initScene() {
        bodies.push_back(Triangle(10, 10, 1, 1, 1));
        bodies.push_back(Triangle(20, 20, 1, -1, -1));
    }
};

// Функция, которая готовит всю сцену и возвращает готовый объект.
// Если нужно читать из файла и консоли, вызывать кучу методов - это здесь.
FiguresRainScene* getScene()
{
    // Например, инит сцены может быть устроен технически так.
    // Ну или как-то иначе.
    // Приведите это в тот вид, который нужен в вашем случае.
    SampleScene* s = new SampleScene();
    s->initScene();
    return s;
}

/*
// Ваш отладочный main
int main()
{
    // Создаём сцену
    SampleScene* scene = (SampleScene*)getScene();

    // Некая работа со сценой в рамках вашей отладки
    // for(...) {
    //     scene->doTimeStep();
    //     scene->print();
    //     scene->whatever();
    // }

    // Удаляем сцену
    delete scene;

    return 0;
};
*/