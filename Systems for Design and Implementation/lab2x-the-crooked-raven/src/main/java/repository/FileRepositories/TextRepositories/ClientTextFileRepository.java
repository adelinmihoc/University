package repository.FileRepositories.TextRepositories;

import domain.Client;
import domain.Validators.Validator;
import java.util.List;

/**
 *
 * Specialized TextFileRepository for entities of type Client
 */
public class ClientTextFileRepository extends TextFileRepository<Integer, Client> {

    public ClientTextFileRepository(Validator<Integer, Client> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Tries to convert a list of strings into a Client Entity
     * @param properties: the possible properties for a Client Entity
     * @return Client: if the conversion was successful, null otherwise
     */
    @Override
    protected Client generateEntity(List<String> properties) {
        Client client;
        try {
            client = Client.Builder()
                    .id(Integer.parseInt(properties.get(0)))
                    .firstName(properties.get(1))
                    .lastName(properties.get(2))
                    .addressId(Integer.parseInt(properties.get(3)))
                    .age((Integer) Validator.checkInput(properties.get(4), "null", true))
                    .phoneNumber((String) Validator.checkInput(properties.get(5), "null", false))
                    .build();
        } catch (Exception e) {
            client = null;
        }
        return client;
    }

    /**
     * Converts a Client Entity into a csv-like string
     * @param client: the entity to be converted
     * @return String: the string form of the entity
     */
    @Override
    protected String convertEntity(Client client) {
        return client.getId() + ", " + client.getFirstName() + ", " + client.getLastName() + ", " + client.getAddressId() +
                ", " + client.getAge() + ", " + client.getPhoneNumber();
    }

}
