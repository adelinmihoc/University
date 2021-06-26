package service;

import domain.Coffee;
import repository.Repository;
import services.ICoffeeService;

import java.util.Set;
import java.util.concurrent.CompletableFuture;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class CoffeeService extends Service<Integer, Coffee> implements ICoffeeService {
    /**
     * Constructor for CoffeeService
     * @param constructorRepo of type {@code Repository<Integer, Coffee>}
     */
    public CoffeeService(Repository<Integer, Coffee> constructorRepo) {
        super(constructorRepo);
    }

    /**
     * Gets the coffees that have a substring in their name in a set
     * @param name of type String
     * @return {@code CompletableFuture<Set<Coffee>>}
     */
    public CompletableFuture<Set<Coffee>> filterCoffeesByName(String name) {
        return CompletableFuture.completedFuture(
                StreamSupport.stream(this.repository.findAll().spliterator(), false)
                .filter(coffee -> coffee.getName().contains(name)).collect(Collectors.toSet()));
    }

    /**
     * Gets the coffees that have a substring in their origin in a set
     * @param origin : string
     * @return {@code CompletableFuture<Set<Coffee>>}
     */
    public CompletableFuture<Set<Coffee>> filterCoffeesByOrigin(String origin) {
        return CompletableFuture.completedFuture(
                StreamSupport.stream(this.repository.findAll().spliterator(), false)
                .filter(coffee -> coffee.getOrigin().contains(origin)).collect(Collectors.toSet()));
    }

}
