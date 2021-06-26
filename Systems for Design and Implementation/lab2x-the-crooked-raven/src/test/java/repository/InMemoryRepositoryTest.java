package repository;

import domain.Client;
import domain.Validators.ClientValidator;
import domain.Validators.Validator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.InMemoryRepositories.InMemoryRepository;
import java.util.Collection;
import java.util.Optional;
import static org.junit.jupiter.api.Assertions.*;

public class InMemoryRepositoryTest {
    private Client c1;
    private Client c2;
    Validator<Integer, Client> testValidator;
    Repository<Integer, Client> testRepository;

    @BeforeEach
    public void setUp() {
        c1 = Client.Builder()
                .id(14)
                .firstName("John")
                .lastName("Mike")
                .addressId(10)
                .age(19)
                .build();

        c2 = Client.Builder()
                .id(21)
                .firstName("George")
                .lastName("Jackson")
                .addressId(20)
                .build();

        testValidator = new ClientValidator();
        testRepository = new InMemoryRepository<>(testValidator);
    }

    @AfterEach
    public void tearDown() {
        c1 = null;
        c2 = null;
        testRepository = null;
        testValidator = null;
    }

    @Test
    public void findOne() {
        testRepository.save(c1);
        assertEquals(testRepository.findOne(14).orElse(null), c1);
        assertEquals(testRepository.findOne(null), Optional.empty());
    }

    @Test
    public void findAll() {
        assertEquals(((Collection<?>)testRepository.findAll()).size(), 0);
        testRepository.save(c1);
        assertEquals(((Collection<?>)testRepository.findAll()).size(), 1);
        testRepository.save(c2);
        assertEquals(((Collection<?>)testRepository.findAll()).size(), 2);
    }

    @Test
    public void save() {
        testRepository.save(c1);
        assertEquals(testRepository.findOne(14).orElse(null), c1);
        testRepository.save(c2);
        assertEquals(testRepository.findOne(21).orElse(null), c2);
    }

    @Test
    public void delete() {
        testRepository.save(c1);
        testRepository.delete(14);
        assertEquals(testRepository.findOne(14), Optional.empty());
        assertEquals(testRepository.delete(null), Optional.empty());
    }

    @Test
    public void update() {
        testRepository.save(c2);
        c2.setAge(21);
        testRepository.update(c2);
        //System.out.println(testRepository.findAll());
        assertEquals(testRepository.findOne(21).orElse(Client.Builder().build()).getAge(), 21);
    }
}