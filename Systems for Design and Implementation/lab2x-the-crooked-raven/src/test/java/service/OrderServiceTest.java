package service;

import domain.Client;
import domain.Coffee;
import domain.Order;
import domain.Status;
import domain.Validators.*;
import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.InMemoryRepositories.InMemoryRepository;
import repository.Repository;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static org.junit.jupiter.api.Assertions.*;

class OrderServiceTest {
    Order o1, o2, o3, o4, o5, o6;
    Coffee c1, c2, c3;
    Client cl1, cl2, cl3;
    Client client1, client2;
    Coffee coffee1, coffee2;
    Repository<Pair<Integer, Integer>, Order> repository;
    Repository<Integer, Coffee> coffeeRepository;
    Repository<Integer, Client> clientRepository;
    OrderService service;


    @BeforeEach
    public void setUp() {
        c1 = Coffee.Builder()
                .id(10)
                .name("ffff")
                .origin("ffff")
                .build();
        c2 = Coffee.Builder()
                .id(20)
                .name("ffff")
                .origin("ffff")
                .build();
        c3 = Coffee.Builder()
                .id(30)
                .name("ffff")
                .origin("ffff")
                .build();

        cl1 = Client.Builder()
                .id(100)
                .firstName("ffff")
                .lastName("ffff")
                .addressId(1)
                .build();
        cl2 = Client.Builder()
                .id(200)
                .firstName("ffff")
                .lastName("ffff")
                .addressId(1)
                .build();
        cl3 = Client.Builder()
                .id(300)
                .firstName("ffff")
                .lastName("ffff")
                .addressId(1)
                .build();

        o1 = Order.Builder()
                .id(new ImmutablePair<>(10, 10))
                .status(Status.delivered)
                .time(LocalDateTime.of(2000, 3, 4, 0, 0))
                .build();
        o1.getCoffeesId().add(11);
        o2 = Order.Builder()
                .id(new ImmutablePair<>(12, 12))
                .status(Status.delivered)
                .time(LocalDateTime.of(2010, 3, 4, 0, 0))
                .build();
        o2.getCoffeesId().add(11);
        o3 = Order.Builder()
                .id(new ImmutablePair<>(14, 14))
                .status(Status.delivered)
                .time(LocalDateTime.of(2020, 3, 4, 0, 0))
                .build();
        o3.getCoffeesId().add(11);

        o4 = Order.Builder()
                .id(new ImmutablePair<>(1, 100))
                .status(Status.pending)
                .time(LocalDateTime.now())
                .build();

        o5 = Order.Builder()
                .id(new ImmutablePair<>(1, 200))
                .status(Status.pending)
                .time(LocalDateTime.now())
                .build();
        o5.getCoffeesId().add(11);
        o6 = Order.Builder()
                .id(new ImmutablePair<>(1, 200))
                .status(Status.pending)
                .time(LocalDateTime.now())
                .build();
        o6.getCoffeesId().add(11);

        o4.getCoffeesId().add(10);
        o4.getCoffeesId().add(20);

        client1 = Client.Builder()
                .id(10)
                .firstName("John")
                .lastName("Mike")
                .addressId(12)
                .age(50)
                .phoneNumber("0222222222222222")
                .build();
        client2 = Client.Builder()
                .id(20)
                .firstName("Jack")
                .lastName("George")
                .addressId(14)
                .age(60)
                .phoneNumber("0333333333333333")
                .build();

        coffee1 = Coffee.Builder()
                .id(10)
                .name("Arabica")
                .origin("Ethiopia")
                .quantity(200)
                .price(500)
                .build();
        coffee2 = Coffee.Builder()
                .id(20)
                .name("Robusta")
                .origin("Indonezia")
                .price(600)
                .build();

        repository = new InMemoryRepository<>(new OrderValidator());

        coffeeRepository = new InMemoryRepository<>(new CoffeeValidator());
        coffeeRepository.save(coffee1);
        coffeeRepository.save(coffee2);

        clientRepository = new InMemoryRepository<>(new ClientValidator());
        clientRepository.save(client1);
        clientRepository.save(client2);

        service = new OrderService(repository, coffeeRepository, clientRepository);

        clientRepository.save(cl1);
        clientRepository.save(cl2);
        clientRepository.save(cl3);

        coffeeRepository.save(c1);
        coffeeRepository.save(c2);
        coffeeRepository.save(c3);

        service.Add(o1);
        service.Add(o2);
        service.Add(o3);
        service.Add(o4);
    }

    @AfterEach
    public void tearDown() {
        o1 = null;
        o2 = null;
        o3 = null;
        repository = null;
        service = null;
    }

    @Test
    public void filterClientsByNameTest() {
        assertEquals(service.getAll().size(), 4);
        service.deleteOrderByDate(LocalDateTime.of(2005, 3, 4, 0, 0), LocalDateTime.of(2012, 3, 4, 0, 0));
        assertEquals(service.getAll().size(), 3);
    }

    @Test
    public void filterClientCoffeesTest() {
        Set<Coffee> coffees = service.filterClientCoffees(100);
        assertFalse(coffees.contains(c2));
        assertFalse(coffees.contains(c1));
    }

    @Test
    public void filterClientOrdersTest() {
        Set<Order> orders = service.filterClientOrders(100);
        assertTrue(orders.contains(o4));
    }

    @Test
    public void buyCoffeeTest() {
        service.buyCoffee(50, 10, 10);
        service.buyCoffee(60, 20, 20);

        Order orderNew1 = Order.Builder()
                .id(new ImmutablePair<>(50, 10))
                .status(Status.pending)
                .build();
        orderNew1.getCoffeesId().add(10);

        Order orderNew2 = Order.Builder()
                .id(new ImmutablePair<>(60, 20))
                .status(Status.outOfStock)
                .build();
        orderNew1.getCoffeesId().add(20);

        Set<Order> orders = StreamSupport.stream(repository.findAll().spliterator(), false)
                .collect(Collectors.toSet());

        assertEquals(Status.pending, repository.findOne(new ImmutablePair<>(50, 10)).get().getStatus());
        assertEquals(Status.outOfStock, repository.findOne(new ImmutablePair<>(60, 20)).get().getStatus());
        assertThrows(CoffeeValidatorException.class, () -> service.buyCoffee(100, 300, 400));
        assertThrows(CoffeeValidatorException.class, () -> service.buyCoffee(200, 10, 500));
    }

    @Test
    public void deleteCoffeesFromOrderTest() {
        service.buyCoffee(50, 10, 10);
        service.addCoffeesToOrder(50, 10, List.of(20));

        List<Integer> coffees = new ArrayList<>();
        coffees.add(10);

        service.deleteCoffeesFromOrder(50, 10, coffees);

        assertFalse(repository.findOne(new ImmutablePair<>(50, 10)).get().getCoffeesId().contains(10));
        assertThrows(OrderValidatorException.class, () -> service.deleteCoffeesFromOrder(400, 30, coffees));
    }

    @Test
    public void addCoffeesToOrderTest() {
        service.buyCoffee(50, 10, 10);

        List<Integer> coffees = new ArrayList<>();
        coffees.add(20);

        service.addCoffeesToOrder(50, 10, coffees);
        assertTrue(repository.findOne(new ImmutablePair<>(50, 10)).get().getCoffeesId().contains(20));
        assertThrows(OrderValidatorException.class, () -> service.deleteCoffeesFromOrder(400, 30, coffees));
    }

    @Test
    public void changeStatusTest() {
        service.changeStatus(14, 14, Status.canceled);
        assertEquals(repository.findOne(new ImmutablePair<>(14, 14)).get().getStatus(), Status.canceled);
    }
}