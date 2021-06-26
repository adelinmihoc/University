package service;


import domain.BaseEntity;
import repository.Repository;

import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public abstract class Service<ID, entity extends BaseEntity<ID>> {
    protected final Repository<ID, entity> repository;


    /**
     * Constructor for Serivce
     * @param constructorRepo of type {@code Repository<ID, entity>}
     */
    protected Service(Repository<ID, entity> constructorRepo) {
        repository = constructorRepo;
    }

    /**
     * Adds an element to the repository
     * @param element of type entity
     */
    public void Add(entity element) {
        repository.save(element);
    }

    /**
     * Updates an element from the repository
     * @param element of type entity
     */
    public void Update(entity element) {
        repository.update(element);
    }

    /**
     * Deletes an element from the repository
     * @param id of type ID
     */
    public void Delete(ID id) {
        repository.delete(id);
    }

    /**
     * Gets all entities in a set
     * @return {@code Set<entity>}
     */
    public Set<entity> getAll() {
        Iterable<entity> coffees = this.repository.findAll();
        return StreamSupport.stream(coffees.spliterator(), false).collect(Collectors.toSet());
    }

}
