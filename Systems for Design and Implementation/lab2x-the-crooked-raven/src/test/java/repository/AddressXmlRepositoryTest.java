package repository;

import domain.Address;
import domain.Validators.AddressValidator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;
import repository.FileRepositories.XMLRepositories.AddressXMLRepository;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static org.junit.jupiter.api.Assertions.*;

public class AddressXmlRepositoryTest {

    @TempDir
    static Path temp;

    private AddressValidator addressValidator;
    private Address address1, address2;
    private Repository<Integer, Address> addressRepository;
    private Path tempAddressPath;
    private String tempAddressFile;
    private Integer numberUpdated;

    @BeforeEach
    public void setUp() {
        tempAddressFile = "address.xml";
        addressValidator = new AddressValidator();
        numberUpdated = 90;

        address1 = Address.Builder()
                .id(10)
                .city("LosAngeles")
                .street("Palm Street")
                .number(20)
                .build();
        address2 = Address.Builder()
                .id(20)
                .city("Moscow")
                .street("Kremlin Street")
                .number(45)
                .build();
    }

    @AfterEach
    public void tearDown() {
        tempAddressFile = null;
        addressValidator = null;
        address1 = null;
        address2 = null;
        numberUpdated = null;
    }

    @Test
    @Order(1)
    public void saveTest() throws IOException {
        tempAddressPath = Files.createFile(temp.resolve(tempAddressFile));

        addressRepository = new AddressXMLRepository(addressValidator, tempAddressPath.toFile().getAbsolutePath());
        assertNull(addressRepository.save(address1).orElse(null));
        assertNull(addressRepository.save(address2).orElse(null));
        assertEquals(11, Files.readAllLines(tempAddressPath).size());
    }

    @Test
    @Order(2)
    public void operationsTest() throws IOException {
        tempAddressPath = temp.resolve(tempAddressFile);
        addressRepository = new AddressXMLRepository(addressValidator, tempAddressPath.toFile().getAbsolutePath());

        addressRepository.delete(address1.getId());
        address2.setNumber(numberUpdated);
        addressRepository.update(address2);

        assertEquals(6, Files.readAllLines(tempAddressPath).size());
    }

    @Test
    @Order(3)
    public void loadDataTest() {
        tempAddressPath = temp.resolve(tempAddressFile);
        addressRepository = new AddressXMLRepository(addressValidator, tempAddressPath.toFile().getAbsolutePath());

        address2.setNumber(numberUpdated);
        List<Address> addresses = StreamSupport.stream(addressRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());
        assertEquals(addresses.size(), 1);
        assertTrue(addresses.contains(address2));
    }

}
