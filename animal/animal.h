#ifndef ANIMAL_H
#define ANIMAL_H

#include "food.h"
#include <string>

enum class AnimalType {Animal = '-', Cat = 'c', Parrot = 'p'};

class Animal {
    virtual bool check_food(const Food &food) const;

    virtual int digested_calories (const Food &food) const;

public:
    std::string name;
    int age = 0;
    int satiety = 0;
    int max_size = 10;

    AnimalType type;

    Animal();

    void eat(const Food &food);

    void run(int length);

    virtual Animal breed(const Animal &partner) const;
};

class Parrot : public Animal { 
    virtual bool check_food(const Food &food) const;

public:
    Parrot();

    virtual Animal breed(const Animal &partner) const;
};

class Cat : public Animal {
    virtual bool check_food(const Food &food) const;

    virtual int digested_calories (const Food &food) const;

    int claw_len;
    FoodName fav_food = FoodName::Beef;

public:
    Cat();

    virtual Animal breed(const Animal &partner) const;
};

#endif // ANIMAL_H
