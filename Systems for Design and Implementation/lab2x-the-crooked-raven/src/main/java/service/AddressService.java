package service;

import domain.Address;
import repository.Repository;

public class AddressService extends Service<Integer, Address> {

    /**
     * Constructor for AddressSerivce
     * @param repository of type {@code Repository<Integer, Address>}
     */
    public AddressService(Repository<Integer, Address> repository) {
        super(repository);
    }

    /**
     * Deletes all addresses with a given street number
     * @param number: integer
     */
    public void deleteAddressWithNumber(Integer number)
    {
        this.getAll().stream()
                .filter(address -> address.getNumber().equals(number))
                .forEach(address -> Delete(address.getId()));
    }
}
