package repository.FileRepositories.XMLRepositories;

import com.fasterxml.jackson.databind.SerializationFeature;
import com.fasterxml.jackson.dataformat.xml.XmlMapper;
import com.fasterxml.jackson.module.jaxb.JaxbAnnotationModule;
import domain.BaseEntity;
import domain.Validators.Validator;
import domain.Validators.ValidatorException;
import repository.FileRepositories.FileRepository;
import javax.xml.stream.*;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Optional;
import java.util.function.Function;

/**
 * Generic class which extends the FileRepository. Provides specialized behaviour for working with xml files
 */
public abstract class XMLRepository<ID, T extends BaseEntity<ID>> extends FileRepository<ID, T> {

    protected XMLRepository(Validator<ID, T> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Loads bootstrap data from an xml file into memory
     */
    @Override
    protected void loadData() {
        XMLInputFactory factory = XMLInputFactory.newFactory();
        try {
            BufferedReader bufferedReader = Files.newBufferedReader(Paths.get(super.filename));
            XMLStreamReader reader = factory.createXMLStreamReader(bufferedReader);
            XmlMapper mapper = new XmlMapper();
            mapper.registerModule(new JaxbAnnotationModule());

            reader.next();
            reader.next();

            while (true) {
                try {
                    super.save(validator.verifyNullableFields(mapper.readValue(reader, getEntityClass())));
                    reader.next();
                } catch (IOException e) {
                    break;
                } catch (ValidatorException ve) {
                    System.out.println(ve.toString());
                }
            }
            reader.close();
        } catch (XMLStreamException | IOException e) {
            System.out.println("Error parsing xml file: " + e.getMessage());
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
     * Writes all changes in xml format to a file
     */
    @Override
    protected void writeAll() {
        XMLOutputFactory xmlOutputFactory = XMLOutputFactory.newFactory();
        try {
            BufferedWriter bufferedWriter = Files.newBufferedWriter(Paths.get(super.filename), StandardOpenOption.TRUNCATE_EXISTING);
            XMLStreamWriter writer = xmlOutputFactory.createXMLStreamWriter(bufferedWriter);

            XmlMapper mapper = new XmlMapper();
            mapper.registerModule(new JaxbAnnotationModule());
            mapper.enable(SerializationFeature.INDENT_OUTPUT);

            writer.writeStartDocument();
            writer.writeStartElement(getEntityClass().getSimpleName() + "s");

            findAll().forEach(entity -> {
                try {
                    mapper.writeValue(writer, entity);
                } catch (IOException e) {
                    System.out.println("Error writing to xml file");
                }
            });

            writer.writeEndElement();
            writer.writeEndDocument();
            writer.close();
        } catch (XMLStreamException | IOException e) {
            System.out.println("Error parsing xml file: " + e.getMessage());
        }
    }

    /**
     * Abstract method for getting the class of the entities the repo is working with
     * @return {@code Class<T>}
     */
    abstract protected Class<T> getEntityClass();

}
