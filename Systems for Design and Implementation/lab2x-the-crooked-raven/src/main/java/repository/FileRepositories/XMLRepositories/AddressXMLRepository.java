package repository.FileRepositories.XMLRepositories;

import domain.Address;
import domain.Validators.Validator;

public class AddressXMLRepository extends XMLRepository<Integer, Address> {
    public AddressXMLRepository(Validator<Integer, Address> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Method for getting the class of the entities the repo is working with
     * @return {@code Class<T>}
     */
    @Override
    protected Class<Address> getEntityClass() {
        return Address.class;
    }
}
