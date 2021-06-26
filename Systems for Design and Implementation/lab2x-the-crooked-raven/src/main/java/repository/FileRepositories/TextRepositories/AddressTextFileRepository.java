package repository.FileRepositories.TextRepositories;

import domain.Address;
import domain.Validators.Validator;
import java.util.List;

/**
 *
 * Specialized TextFileRepository for entities of type Address
 */
public class AddressTextFileRepository extends TextFileRepository<Integer, Address> {
    public AddressTextFileRepository(Validator<Integer, Address> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Tries to convert a list of strings into an Address Entity
     * @param properties: the possible properties for an Address Entity
     * @return Address: if the conversion was successful, null otherwise
     */
    @Override
    protected Address generateEntity(List<String> properties) {
        Address address;
        try {
            address = Address.Builder()
                    .id(Integer.parseInt(properties.get(0)))
                    .city(properties.get(1))
                    .street(properties.get(2))
                    .number(Integer.parseInt(properties.get(3)))
                    .build();
        } catch (Exception e) {
            address = null;
        }
        return address;
    }

    /**
     * Converts an Address Entity into a csv-like string
     * @param entity: the entity to be converted
     * @return String: the string form of the entity
     */
    @Override
    protected String convertEntity(Address entity) {
        return entity.getId() + ", " + entity.getCity() + ", " + entity.getStreet() + ", " + entity.getNumber();
    }
}
