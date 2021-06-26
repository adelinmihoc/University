package repository.FileRepositories.XMLEncoderRepositories;

import domain.Order;
import domain.PersistenceDelegates.PairPersistenceDelegate;
import domain.PersistenceDelegates.TimePersistenceDelegate;
import domain.Validators.Validator;
import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import java.beans.XMLEncoder;
import java.io.FileOutputStream;
import java.io.IOException;
import java.time.LocalDateTime;

public class OrderEncoderRepository extends XMLEncoderRepository<Pair<Integer, Integer>, Order> {
    /**
     * Constructor, receives a Validator object and a file name
     *
     * @param validator : specialized validator for the entities it stores
     * @param filename  : the name of the file which will be used for persistence
     */
    public OrderEncoderRepository(Validator<Pair<Integer, Integer>, Order> validator, String filename) {
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
            xmlEncoder.setPersistenceDelegate(LocalDateTime.class, new TimePersistenceDelegate());
            xmlEncoder.setPersistenceDelegate(ImmutablePair.class, new PairPersistenceDelegate());
            findAll().forEach(xmlEncoder::writeObject);
        } catch (IOException e) {
            System.out.println("Error while opening xml file");
        }
    }
}
