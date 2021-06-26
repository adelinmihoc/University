package ro.ubb.coffeeshop.services.interfaces;

import ro.ubb.coffeeshop.model.Coffee;

import java.util.List;

public interface CoffeeService {
    void addCoffee(Coffee coffee);
    void deleteCoffee(Integer cid);
    void updateCoffee(Coffee coffee, Integer cid);
    List<Coffee> getAllCoffees();

    List<Coffee> filterCoffeesByName(String name);
    List<Coffee> filterCoffeesByOrigin(String origin);
}
