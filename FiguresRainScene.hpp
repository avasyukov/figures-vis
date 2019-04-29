#ifndef FIGURES_RAIN_SCENE_HPP
#define FIGURES_RAIN_SCENE_HPP

#include "FiguresRainPolygon.hpp"

// Интерфейс всей сцены целиком.
// Ваша сцена должна его реализовать.
class FiguresRainScene {
public:
    virtual ~FiguresRainScene() = default;
    virtual unsigned int getNumberOfFigures() const = 0;
    virtual const VisPolygon* getFigure(unsigned int number) const = 0;
    virtual void doTimeStep() = 0;
};

#endif //FIGURES_RAIN_SCENE_HPP