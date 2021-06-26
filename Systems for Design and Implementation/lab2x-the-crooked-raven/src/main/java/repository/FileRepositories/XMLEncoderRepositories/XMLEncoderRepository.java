package repository.FileRepositories.XMLEncoderRepositories;

import domain.BaseEntity;
import domain.Validators.Validator;
import repository.FileRepositories.FileRepository;
import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Optional;
import java.util.function.Function;
import java.util.stream.Stream;

public class XMLEncoderRepository<ID, T extends BaseEntity<ID>> extends FileRepository<ID, T> {
    /**
     * Constructor, receives a Validator object and a file name
     *
     * @param validator : specialized validator for the entities it stores
     * @param filename  : the name of the file which will be used for persistence
     */
    public XMLEncoderRepository(Validator<ID, T> validator, String filename) {
        super(validator, filename);
    }

    /**
     * Writes all changes in xml format to a file
     */
    @Override
    protected void writeAll() {
        try (FileOutputStream fileOutputStream = new FileOutputStream(filename, false);
             XMLEncoder xmlEncoder = new XMLEncoder(fileOutputStream)) {
            xmlEncoder.setExceptionListener(e ->
                    System.out.println("There was an error while serializing objects to xml: " + e.toString()));
            findAll().forEach(xmlEncoder::writeObject);
        } catch (IOException e) {
            System.out.println("Error while opening xml file");
        }
    }

    /**
     * Overrides the save method of its parent. Also saves the entity into an xml file
     * @param entity: the entity to be saved
     * @return {@code Optional<T>}: an empty optional or an optional holding the current value of that entity
     */
    @Override
    @SuppressWarnings("DuplicatedCode")
    public Optional<T> save(T entity) {
        Function<T, Optional<T>> saveFunction = t -> {
            writeAll();
            return Optional.empty();
        };
        Optional<T> optional = super.save(entity);
        return optional.isPresent() ? optional : saveFunction.apply(entity);
    }

    /**
     * Loads bootstrap data from an xml file into memory
     */
    @Override
    @SuppressWarnings("unchecked")
    protected void loadData() {
        try(FileInputStream fileInputStream = new FileInputStream(filename);
            XMLDecoder xmlDecoder = new XMLDecoder(fileInputStream)) {
            xmlDecoder.setExceptionListener(e ->
                    System.out.println("There was an error while deserializing objects from xml: " + e.toString()));
            try {
                Stream.generate(xmlDecoder::readObject)
                        .limit(10000)
                        .forEach(t -> super.save((T) t));
            } catch (ArrayIndexOutOfBoundsException ae) {
                System.out.println("End of file");
            }
        } catch (IOException e) {
            System.out.println("Error while opening xml file");
        }
    }
}
