package service;

import domain.Client;
import domain.Coffee;
import domain.Validators.ClientValidator;
import domain.Validators.CoffeeValidator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.InMemoryRepositories.InMemoryRepository;
import repository.Repository;

import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

public class CoffeeServiceTest {
    Coffee c1, c2, c3;
    Repository<Integer, Coffee> repository;
    CoffeeService service;

    @BeforeEach
    public void setUp() {
        c1 = Coffee.Builder()
                .id(10)
                .name("Jacobs")
                .origin("Colombia")
                .price(12)
                .build();
        c2 = Coffee.Builder()
                .id(20)
                .name("Nescafe")
                .origin("Jamaica")
                .price(14)
                .build();
        c3 = Coffee.Builder()
                .id(30)
                .name("HeavyCup")
                .origin("Lebanon")
                .price(15)
                .build();

        repository = new InMemoryRepository<>(new CoffeeValidator());
        service = new CoffeeService(repository);

        service.Add(c1);
        service.Add(c2);
        service.Add(c3);
    }

    @AfterEach
    public void tearDown() {
        c1 = null;
        c2 = null;
        c3 = null;
        repository = null;
        service = null;
    }


    @Test
    public void filterCoffeesByNameTest() {
        Set<Coffee> nameLikeJ = service.filterCoffeesByName("J");
        Set<Coffee> nameLikeA = service.filterCoffeesByName("a");


        assertTrue(nameLikeJ.contains(c1));
        assertFalse(nameLikeJ.contains(c3));

        assertTrue(nameLikeA.contains(c3));
        assertTrue(nameLikeA.contains(c2));
        assertTrue(nameLikeA.contains(c1));
    }

    @Test
    public void filterCoffeesByOriginTest() {
        Set<Coffee> coffeesLikeJam = service.filterCoffeesByOrigin("Jam");
        Set<Coffee> coffeesLikeCol = service.filterCoffeesByOrigin("Col");
        
        assertTrue(coffeesLikeJam.contains(c2));
        assertFalse(coffeesLikeJam.contains(c3));
        
        assertTrue(coffeesLikeCol.contains(c1));
    }

}