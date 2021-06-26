package service;

import domain.Address;

import domain.Validators.AddressValidator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.InMemoryRepositories.InMemoryRepository;
import repository.Repository;

import java.util.Set;

import static org.junit.jupiter.api.Assertions.assertFalse;

public class AddressServiceTest {

    Address a1, a2, a3;
    Repository<Integer, Address> repository;
    AddressService service;

    @BeforeEach
    public void setUp() {
        a1 = Address.Builder()
                .id(14)
                .city("aaaa")
                .street("bbbb")
                .number(1)
                .build();
        a2 = Address.Builder()
                .id(15)
                .city("cccc")
                .street("dddd")
                .number(2)
                .build();
        a3 = Address.Builder()
                .id(16)
                .city("eeee")
                .street("ffff")
                .number(1)
                .build();

        repository = new InMemoryRepository<>(new AddressValidator());
        service = new AddressService(repository);

        service.Add(a1);
        service.Add(a2);
        service.Add(a3);
    }

    @AfterEach
    public void tearDown() {
        a1 = null;
        a2 = null;
        a3 = null;
        repository = null;
        service = null;
    }


    @Test
    public void deleteAddressByNumber() {
        service.deleteAddressWithNumber(1);
        Set<Address> addresses = service.getAll();
        assertFalse(addresses.contains(a1));
    }

}
