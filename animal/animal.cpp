#include "animal.h"

#include <stdexcept>

// ----------------------------------------------
// ANIMAL IMPLEMENTATIONS
bool Animal::check_food(const Food &food) const {
    return true;
}

int Animal::digested_calories (const Food &food) const {
    return food.calories;
}

Animal::Animal() {
    type = AnimalType::Animal;
}

void Animal::eat(const Food &food) {
    if (!check_food (food))
        throw std::invalid_argument("Wrong meat!");

    satiety += digested_calories(food);

    if (satiety > max_size)
        throw std::overflow_error("I am blown up!");
}

void Animal::run(int length) {
    satiety -= length;
    if (satiety < 0)
        throw std::underflow_error("I starved to death :(");
}

Animal Animal::breed(const Animal &partner) const {
    throw std::logic_error("I have no genes :(");
}

// ----------------------------------------------
// PARROT IMPLEMENTATIONS
// ----------------------------------------------

bool Parrot::check_food(const Food &food) const {
    return food.type == FoodType::Fruit;
}

Parrot::Parrot() {
    type = AnimalType::Parrot;
}

Animal Parrot::breed(const Animal &partner) const {
    if (this == &partner)
        throw std::logic_error("I can't breed with myself");

    if (type != partner.type)
        throw std::invalid_argument("this is not a parrot");

    return Parrot();
}

// ----------------------------------------------
// CAT IMPLEMENTATIONS
// ----------------------------------------------

bool Cat::check_food(const Food &food) const {
    return food.type == FoodType::Meat;
}

int Cat::digested_calories (const Food &food) const {
    // if matches fav_food calories intake is increased two times
    return (1 + (food.name == fav_food)) * food.calories; 
}

 Cat::Cat() {
    type = AnimalType::Cat;
}

Animal Cat::breed(const Animal &partner) const {
    if (this == &partner)
        throw std::logic_error("I can't breed with myself");
    if (type != partner.type)
        throw std::invalid_argument("this is not a cat");
        
    return Cat();
}
