package ro.ubb.coffeeshop.services.implementations;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import ro.ubb.coffeeshop.model.Coffee;
import ro.ubb.coffeeshop.repositories.CoffeeRepository;
import ro.ubb.coffeeshop.services.interfaces.CoffeeService;
import ro.ubb.coffeeshop.validators.Validator;

import java.util.List;

@Slf4j
@Service
@RequiredArgsConstructor
public class CoffeeServiceImpl implements CoffeeService {
    private final CoffeeRepository coffeeRepository;

    @Transactional
    @Override
    public void addCoffee(Coffee coffee) {
        log.info("addCoffee: coffee={} method entered", coffee);
        this.coffeeRepository.save(coffee);
        log.info("addCoffee method finished");
    }

    @Transactional
    @Override
    public void deleteCoffee(Integer cid) {
        log.info("deleteCoffee: cid={} method entered", cid);
        this.coffeeRepository.deleteById(cid);
        log.info("deleteCoffee method finished");
    }

    @Transactional
    @Override
    public void updateCoffee(Coffee coffee, Integer cid) {
        log.info("updateCoffee: coffee={}, cid={} method entered", coffee, cid);
        Coffee coffeeToUpdate = (Coffee) Validator.checkNull(this.coffeeRepository.findById(cid)
                .orElse(null), "coffee not found");

        coffeeToUpdate.setName(coffee.getName());
        coffeeToUpdate.setOrigin(coffee.getOrigin());
        coffeeToUpdate.setPrice(coffee.getPrice());
        coffeeToUpdate.setQuantity(coffee.getQuantity());

        this.coffeeRepository.save(coffeeToUpdate);
        log.info("updateCoffee method finished");
    }

    @Override
    public List<Coffee> getAllCoffees() {
        log.info("getAllCoffees method entered");
        List<Coffee> coffees = this.coffeeRepository.findAll();
        log.info("getAllCoffees: coffees={} method finished", coffees);
        return coffees;
    }

    @Override
    public List<Coffee> filterCoffeesByName(String name) {
        log.info("filterCoffeesByName: name={} method entered", name);
        List<Coffee> coffees = this.coffeeRepository.findAllByNameContaining(name);
        log.info("filterCoffeesByName: coffees={} method finished", coffees);
        return coffees;
    }

    @Override
    public List<Coffee> filterCoffeesByOrigin(String origin) {
        log.info("filterCoffeesByOrigin: origin={} method entered", origin);
        List<Coffee> coffees = this.coffeeRepository.findAllByOriginContaining(origin);
        log.info("filterCoffeesByOrigin: coffees={} method finished", coffees);
        return coffees;
    }
}
