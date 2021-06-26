package service;

import domain.Client;
import domain.Validators.ClientValidator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.InMemoryRepositories.InMemoryRepository;
import repository.Repository;
import service.ClientService;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Set;

public class ClientServiceTest {

    Client c1, c2, c3;
    Repository<Integer, Client> repository;
    ClientService service;

    @BeforeEach
    public void setUp() {
        c1 = Client.Builder()
                .id(10)
                .firstName("John")
                .lastName("Jackson")
                .addressId(10)
                .age(40)
                .build();
        c2 = Client.Builder()
                .id(20)
                .firstName("Abdul")
                .lastName("Johnson")
                .addressId(20)
                .age(20)
                .build();
        c3 = Client.Builder()
                .id(30)
                .firstName("Mike")
                .lastName("Jack")
                .addressId(30)
                .build();

        repository = new InMemoryRepository<>(new ClientValidator());
        service = new ClientService(repository);

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
    public void filterClientsByNameTest() {
        Set<Client> nameLikeJack = service.filterClientsByName("Jack");
        Set<Client> nameLikeJohn = service.filterClientsByName("John");

        assertTrue(nameLikeJack.contains(c1));
        assertTrue(nameLikeJack.contains(c3));

        assertTrue(nameLikeJohn.contains(c2));
        assertTrue(nameLikeJohn.contains(c1));
    }

    @Test
    public void filterClientsInAgeIntervalTest() {
        Set<Client> clients = service.filterClientsInAgeInterval(30, 50);
        assertTrue(clients.contains(c1));
    }

}