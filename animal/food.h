#ifndef FOOD_H
#define FOOD_H

enum class FoodType {Food = '-', Meat = 'm', Fruit = 'f'};
enum class FoodName {Food = '-', Beef = 'b', Pork = 'p', Apple = 'a', Tangerine = 't'};

class Food {
public:
    int calories;
    FoodType type;
    FoodName name;

    Food(FoodName name_, int calories_ = 0);
    Food();
};

class Meat : public Food {
public:
    Meat();
    Meat(FoodName name_, int calories_ = 0);
};

class Fruit : public Food {
public:
    Fruit();
    Fruit(FoodName name_, int calories_ = 0);
};

#endif // FOOD_H
