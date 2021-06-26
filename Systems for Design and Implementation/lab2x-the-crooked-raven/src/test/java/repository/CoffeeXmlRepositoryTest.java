package repository;

import domain.Coffee;
import domain.Validators.CoffeeValidator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;
import repository.FileRepositories.XMLRepositories.CoffeeXMLRepository;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static org.junit.jupiter.api.Assertions.*;

public class CoffeeXmlRepositoryTest {

    @TempDir
    static Path tempDir;

    private String fileName;
    private Path tempCoffeeFile;
    private Repository<Integer, Coffee> coffeeRepo;
    private Coffee coffee1, coffee2, coffee3;
    private Integer priceUpdated;
    private CoffeeValidator coffeeValidator;

    @BeforeEach
    public void setUp() {
        priceUpdated = 500;
        coffeeValidator = new CoffeeValidator();

        coffee1 = Coffee.Builder()
                .id(10)
                .name("Arabica")
                .origin("CentralAmerica")
                .build();
        coffee2 = Coffee.Builder()
                .id(20)
                .name("ArabicaHoney")
                .origin("Ethiopia")
                .build();
        coffee3 = Coffee.Builder()
                .id(30)
                .name("Robusta")
                .origin("Sumatra")
                .build();

        fileName = "coffee.xml";
    }

    @AfterEach
    public void tearDown() {
        coffee1 = null;
        coffee2 = null;
        coffee3 = null;
        fileName = null;
        coffeeValidator = null;
        priceUpdated = null;
    }

    @Test
    @Order(1)
    public void saveCoffeeTest() throws IOException {
        tempCoffeeFile = Files.createFile(tempDir.resolve(fileName));

        coffeeRepo = new CoffeeXMLRepository(coffeeValidator, tempCoffeeFile.toFile().getAbsolutePath());
        assertNull(coffeeRepo.save(coffee1).orElse(null));
        assertNull(coffeeRepo.save(coffee2).orElse(null));
        assertNull(coffeeRepo.save(coffee3).orElse(null));
        assertEquals(19, Files.readAllLines(tempCoffeeFile).size());
    }

    @Test
    @Order(2)
    public void operationsTest() throws IOException {
        tempCoffeeFile = tempDir.resolve(fileName);
        coffeeRepo = new CoffeeXMLRepository(coffeeValidator, tempCoffeeFile.toFile().getAbsolutePath());

        coffeeRepo.delete(coffee1.getId());
        coffee2.setPrice(priceUpdated);
        coffeeRepo.update(coffee2);
        assertEquals(13, Files.readAllLines(tempCoffeeFile).size());
    }

    @Test
    @Order(3)
    public void loadDataCoffeeTest() {
        tempCoffeeFile = tempDir.resolve(fileName);
        coffeeRepo = new CoffeeXMLRepository(coffeeValidator, tempCoffeeFile.toFile().getAbsolutePath());

        List<Coffee> coffees = StreamSupport.stream(coffeeRepo.findAll().spliterator(), false)
                .collect(Collectors.toList());
        coffee2.setPrice(priceUpdated);
        assertEquals(coffees.size(), 2);
        assertTrue(coffees.contains(coffee2));
        assertTrue(coffees.contains(coffee3));
    }
}
