#include <iostream>
#include <string>
#include <vector>

#include "food.h"
#include "animal.h"

// unused, was created for some tests
Food create_by_name (char type, char name) {
    switch ((char)type)
    {
    case 'm':
        return Meat((FoodName)name);
    
    case 'f':
        return Fruit((FoodName)name);

    default:
        return Food();
    }
}

int main() {
    std::vector<Cat> cats;
    std::vector<Parrot> pars;
    std::vector<Food> foods;

    for (int i = 0; i < 10; i++) {
        Cat cat{};
        cat.satiety = i;
        cat.max_size = i + 5;
        Parrot par{};
        par.satiety = i;
        par.max_size = i + 5;

        cats.push_back(cat);
        pars.push_back(par);
    }

    try {
        cats.back().eat(Meat(FoodName::Pork, 10));
        std::cout << "overflow test failed\n";
    }
    catch (std::overflow_error) { 
        cats.pop_back();
    }

    try {
        pars.back().eat(Meat(FoodName::Pork, 10));
        std::cout << "wrong food test failed\n";
    }
    catch (std::invalid_argument) {
        pars.pop_back();
     }

    try {
        cats.back().eat(Meat(FoodName::Beef, 3));
        std::cout << "double fav food test failed\n";
    }
    catch (std::overflow_error) { 
        cats.pop_back();
    }

    try {
        pars.back().run(20);
        std::cout << "starving test failed\n";
    }
    catch (std::underflow_error) { 
        pars.pop_back();
    }

    int ind = cats.size()-1;
    cats[ind].run(ind-2);
    if (cats[ind].satiety != 2) 
        std::cout << "run test failed\n";

    ind = pars.size()-1;
    try {
        pars[ind].breed(pars[ind]);
        std::cout << "self breeding test failed\n";
    }
    catch (std::logic_error) { 
        pars.pop_back();
    }

    try {
        cats.back().breed(pars.back());
        std::cout << "breeding with others test failed!\n";
    }
    catch (std::invalid_argument) {
        pars.pop_back();
    }

    Animal breeded = cats.back().breed(cats[0]);
    if (breeded.type != AnimalType::Cat)
        std::cout << "successful breeding test failed\n";

    std::cout << "if out is empty then everything is successful\n";

    // std::cout << (char)animals[0].type << (char)animals[1].type << std::endl;
    // std::cout << (char)((Cat)animals[0]).breed(animals[0]).type();
}

