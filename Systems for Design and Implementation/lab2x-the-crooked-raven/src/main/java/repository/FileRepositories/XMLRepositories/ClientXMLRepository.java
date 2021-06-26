package repository.FileRepositories.XMLRepositories;

import domain.Client;
import domain.Validators.Validator;

public class ClientXMLRepository extends XMLRepository<Integer, Client> {

    public ClientXMLRepository(Validator<Integer, Client> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Method for getting the class of the entities the repo is working with
     * @return {@code Class<T>}
     */
    @Override
    protected Class<Client> getEntityClass() {
        return Client.class;
    }

}
