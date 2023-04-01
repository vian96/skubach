#include "food.h"

Food::Food() {
    type = FoodType::Food;
    name = FoodName::Food;
}

Food::Food(FoodName name_, int calories_) : 
            name(name_), calories(calories_) {
    type = FoodType::Food;
}

Meat::Meat() {
    type = FoodType::Food;
    name = FoodName::Food;
}

Meat::Meat(FoodName name_, int calories_) : 
            Food(name_, calories_) {
    type = FoodType::Meat;
}

Fruit::Fruit() {
    type = FoodType::Food;
    name = FoodName::Food;
}

Fruit::Fruit(FoodName name_, int calories_) : 
            Food(name_, calories_) {
    type = FoodType::Fruit;
}


