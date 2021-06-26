package repository.InMemoryRepositories;

import domain.BaseEntity;
import domain.Validators.Validator;
import domain.Validators.ValidatorException;
import repository.Repository;
import java.util.*;

/**
 * Basic generic implementation of the Repository interface. Persists data in memory
 */
public class InMemoryRepository<ID, T extends BaseEntity<ID>> implements Repository<ID, T> {

    protected Map<ID, T> entities;
    protected Validator<ID, T> validator;

    /**
     * Constructor for InMemoryRepository
     * @param validator of type {@code Validator<T>}
     */
    public InMemoryRepository(Validator<ID, T> validator) {
        this.validator = validator;
        this.entities = new HashMap<>();
    }

    /**
     * Finds an object by its id
     * @param id of type ID
     * @return an {@code Optional<T>}, the object we are searching for or null
     */
    public Optional<T> findOne(ID id) {
        return Optional.ofNullable(this.entities.get(id));
    }

    /**
     * Finds all objects
     * @return {@code Iterable<T>}, all objects
     */
    public Iterable<T> findAll() {
        return new HashSet<>(this.entities.values());
    }

    /**
     * Saves an object
     * @param entity of type T
     * @return an {@code Optional<T>}, the saved object, or null, if there is no such object
     */
    public Optional<T> save(T entity) throws ValidatorException {
        this.validator.validate(entity);
        return Optional.ofNullable(this.entities.putIfAbsent(entity.getId(), entity));
    }

    /**
     * Deletes an object by its id
     * @param id of type ID
     * @return an {@code Optional<T>}, the deleted object, or null, if there is no such object
     */
    public Optional<T> delete(ID id) {
        return Optional.ofNullable(this.entities.remove(id));
    }

    /**
     * Updates an object
     * @param entity of type T
     * @return an {@code Optional<T>}, the updated object, or null, if there is no such object
     */
    public Optional<T> update(T entity) throws ValidatorException {
        this.validator.validate(entity);
        return Optional.ofNullable(this.entities.computeIfPresent(entity.getId(), (k, v) -> entity));
    }

}

