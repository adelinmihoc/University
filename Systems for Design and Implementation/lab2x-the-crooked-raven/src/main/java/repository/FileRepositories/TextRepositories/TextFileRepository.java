package repository.FileRepositories.TextRepositories;

import domain.BaseEntity;
import domain.Validators.Validator;
import domain.Validators.ValidatorException;
import repository.FileRepositories.FileRepository;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.function.Function;

/**
 *
 * Abstract class which extends the FileRepository. Provides specialized behaviour for working with text files
 */
public abstract class TextFileRepository<ID, T extends BaseEntity<ID>> extends FileRepository<ID, T> {

    protected TextFileRepository(Validator<ID, T> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     *
     *Loads data from text file into memory
     */
    @Override
    protected void loadData() {
        Path path = Paths.get(super.filename);

        try {
            Files.lines(path).forEach(line -> {
                List<String> items = Arrays.asList(line.split(", "));

                T entity = generateEntity(items);

                try {
                    super.save(entity);
                } catch (ValidatorException e) {
                    System.out.println(e.toString());
                }
            });
        } catch (IOException ex) {
            System.out.println("Error while trying to open file or read from it");
        }
    }

    /**
     * Overrides the save method of its parent. Also saves the entity into a text file
     * @param entity: the entity to be saved
     * @return {@code Optional<T>}: an empty optional or an optional holding the current value of that entity
     */
    @Override
    public Optional<T> save(T entity) {
        Function<T, Optional<T>> saveFunction = t -> {
            saveToFile(t);
            return Optional.empty();
        };
        Optional<T> optional = super.save(entity);
        return optional.isPresent() ? optional : saveFunction.apply(entity);
    }

    /**
     * Abstract method for generating an entity from a string
     * @param properties: the properties for instantiating an entity
     * @return T: a domain entity
     */
    abstract protected T generateEntity(List<String> properties);

    /**
     * Abstract method for converting an entity into a string
     * @param entity: the entity to be converted
     * @return String: the string form of the entity
     */
    abstract protected String convertEntity(T entity);

    /**
     * Saves an entity to a text file
     * @param entity: the entity to be saved
     */
    protected void saveToFile(T entity) {
        Path path = Paths.get(super.filename);

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.APPEND)) {
            bufferedWriter.write(convertEntity(entity));
            bufferedWriter.newLine();
        } catch (IOException e) {
            System.out.println("Error while trying to open file or write to it");
        }
    }

    /**
     * Writes all entities from memory to a text file
     */
    @Override
    protected void writeAll() {
        Path path = Paths.get(super.filename);

        try (BufferedWriter bufferedWriter = Files.newBufferedWriter(path, StandardOpenOption.TRUNCATE_EXISTING)) {
            findAll().forEach(entity -> {
                try {
                    bufferedWriter.write(convertEntity(entity));
                    bufferedWriter.newLine();
                } catch (IOException e) {
                    System.out.println("Error while writing to file");
                }
            });
        } catch (IOException e) {
            System.out.println("Error while trying to open file");
        }
    }

}
