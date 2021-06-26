package repository.FileRepositories;

import domain.BaseEntity;
import domain.Validators.Validator;
import domain.Validators.ValidatorException;
import repository.InMemoryRepositories.InMemoryRepository;
import java.util.Optional;
import java.util.function.UnaryOperator;

/**
 * Abstract class which extends the memory repository. Provides extra behaviour for persisting data to files
 *
 */
public abstract class FileRepository<ID, T extends BaseEntity<ID>> extends InMemoryRepository<ID, T> {

    protected final String filename;

    /**
     * Constructor, receives a Validator object and a file name
     * @param validator: specialized validator for the entities it stores
     * @param filename: the name of the file which will be used for persistence
     */
    protected FileRepository(Validator<ID, T> validator, String filename) {
        super(validator);
        this.filename = filename;
        loadData();
    }

    /**
     * Overrides the delete method of its parent. Also writes the changes into a file
     * @param id: the id of the entity to be removed
     * @return {@code Optional<T>}: an empty optional or an optional holding the value of the removed entity
     */
    @Override
    public Optional<T> delete(ID id) {
        UnaryOperator<Optional<T>> write = optional -> {
            writeAll();
            return optional;
        };
        Optional<T> optional = super.delete(id);
        return optional.isPresent() ? write.apply(optional) : Optional.empty();
    }

    /**
     * Overrides the update method of its parent. Also writes the changes into a file
     * @param entity: the entity to be updated
     * @return {@code Optional<T>}: an empty optional or an optional holding the previous value of that entity
     */
    @Override
    public Optional<T> update(T entity) throws ValidatorException {
        UnaryOperator<Optional<T>> write = optional -> {
            writeAll();
            return optional;
        };
        Optional<T> optional = super.update(entity);
        return optional.isPresent() ? write.apply(optional) : Optional.empty();
    }

    /**
     * An abstract method for writing the entities into a file
     * Will be specialized with regards to the types of files it will be working with
     */
    abstract protected void writeAll();

    /**
     * An abstract method for loading bootstrap data from files
     * Will be specialized with regards to the types of files it will be working with
     */
    abstract protected void loadData();
}
