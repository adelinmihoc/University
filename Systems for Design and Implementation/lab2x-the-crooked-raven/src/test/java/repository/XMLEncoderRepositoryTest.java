package repository;

import domain.*;
import domain.Validators.AddressValidator;
import domain.Validators.ClientValidator;
import domain.Validators.CoffeeValidator;
import domain.Validators.OrderValidator;
import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;
import repository.FileRepositories.XMLEncoderRepositories.OrderEncoderRepository;
import repository.FileRepositories.XMLEncoderRepositories.XMLEncoderRepository;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static org.junit.jupiter.api.Assertions.*;

public class XMLEncoderRepositoryTest {

    @TempDir
    static Path clientPath;
    @TempDir
    static Path coffeePath;
    @TempDir
    static Path addressPath;
    @TempDir
    static Path orderPath;

    private String orderFile, addressFile, clientFile, coffeeFile;

    private Repository<Pair<Integer, Integer>, Order> orderRepository;
    private Repository<Integer, Address> addressRepository;
    private Repository<Integer, Client> clientRepository;
    private Repository<Integer, Coffee> coffeeRepository;

    private AddressValidator addressValidator;
    private ClientValidator clientValidator;
    private CoffeeValidator coffeeValidator;
    private OrderValidator orderValidator;

    private Address address1, address2;
    private Client client1, client2, client3;
    private Coffee coffee1, coffee2, coffee3;
    private Order order1, order2, order3, order4;

    @BeforeEach
    public void setUp() {
        orderFile = "order.xml";
        addressFile = "address.xml";
        clientFile = "client.xml";
        coffeeFile = "coffee.xml";

        addressValidator = new AddressValidator();
        clientValidator = new ClientValidator();
        coffeeValidator = new CoffeeValidator();
        orderValidator = new OrderValidator();

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

        client1 = Client.Builder()
                .id(10)
                .firstName("John")
                .lastName("Jackson")
                .addressId(10)
                .build();
        client2 = Client.Builder()
                .id(20)
                .firstName("Abdul")
                .lastName("Mehmed")
                .addressId(20)
                .age(40)
                .build();
        client3 = Client.Builder()
                .id(30)
                .firstName("Mike")
                .lastName("Tyson")
                .addressId(30)
                .age(50)
                .phoneNumber("0009999000090909")
                .build();

        coffee1 = Coffee.Builder()
                .id(10)
                .name("Arabica")
                .origin("CentralAmerica")
                .build();
        coffee2 = Coffee.Builder()
                .id(20)
                .name("ArabicaHoney")
                .origin("Ethiopia")
                .quantity(200)
                .build();
        coffee3 = Coffee.Builder()
                .id(30)
                .name("Robusta")
                .origin("Sumatra")
                .quantity(400)
                .price(500)
                .build();

        order1 = Order.Builder()
                .id(new ImmutablePair<>(10, 10))
                .build();
        order1.getCoffeesId().add(11);
        order2 = Order.Builder()
                .id(new ImmutablePair<>(20, 20))
                .status(Status.canceled)
                .time(LocalDateTime.of(2012, 12, 12, 11, 45, 45))
                .build();
        order2.getCoffeesId().add(30);
        order2.getCoffeesId().add(40);
        order2.getCoffeesId().add(20);
        order3 = Order.Builder()
                .id(new ImmutablePair<>(30, 30))
                .status(Status.delivered)
                .time(LocalDateTime.now())
                .build();
        order3.getCoffeesId().add(10);
        order4 = Order.Builder()
                .id(new ImmutablePair<>(40, 40))
                .status(Status.delivered)
                .time(LocalDateTime.of(2007, 5, 30, 12, 24, 32))
                .build();
        order4.getCoffeesId().add(10);
        order4.getCoffeesId().add(20);
    }

    @AfterEach
    public void tearDown() {
        address1 = null;
        address2 = null;
        client1 = null;
        client2 = null;
        client3 = null;
        coffee1 = null;
        coffee2 = null;
        coffee3 = null;
        order1 = null;
        order2 = null;
        order3 = null;
        order4 = null;
        addressValidator = null;
        clientValidator = null;
        coffeeValidator = null;
        orderValidator = null;
        addressFile = null;
        clientFile = null;
        coffeeFile = null;
        orderFile = null;
    }

    @Test
    @org.junit.jupiter.api.Order(1)
    public void saveTest() throws IOException {
        Path tempAddressPath = Files.createFile(addressPath.resolve(addressFile));
        Path tempClientPath = Files.createFile(clientPath.resolve(clientFile));
        Path tempCoffeePath = Files.createFile(coffeePath.resolve(coffeeFile));
        Path tempOrderPath = Files.createFile(orderPath.resolve(orderFile));

        addressRepository = new XMLEncoderRepository<>(addressValidator, tempAddressPath.toFile().getAbsolutePath());
        clientRepository = new XMLEncoderRepository<>(clientValidator, tempClientPath.toFile().getAbsolutePath());
        coffeeRepository = new XMLEncoderRepository<>(coffeeValidator, tempCoffeePath.toFile().getAbsolutePath());
        orderRepository = new OrderEncoderRepository(orderValidator, tempOrderPath.toFile().getAbsolutePath());

        assertNull(addressRepository.save(address1).orElse(null));
        assertNull(addressRepository.save(address2).orElse(null));
        assertEquals(31, Files.readAllLines(tempAddressPath).size());

        assertNull(clientRepository.save(client1).orElse(null));
        assertNull(clientRepository.save(client2).orElse(null));
        assertNull(clientRepository.save(client3).orElse(null));
        assertEquals(54, Files.readAllLines(tempClientPath).size());

        assertNull(coffeeRepository.save(coffee1).orElse(null));
        assertNull(coffeeRepository.save(coffee2).orElse(null));
        assertNull(coffeeRepository.save(coffee3).orElse(null));
        assertEquals(45, Files.readAllLines(tempCoffeePath).size());

        assertNull(orderRepository.save(order1).orElse(null));
        assertNull(orderRepository.save(order2).orElse(null));
        assertNull(orderRepository.save(order3).orElse(null));
        assertNull(orderRepository.save(order4).orElse(null));
        assertEquals(118, Files.readAllLines(tempOrderPath).size());
    }

    @Test
    @org.junit.jupiter.api.Order(2)
    public void operationsTest() throws IOException {
        Path tempAddressPath = addressPath.resolve(addressFile);
        Path tempClientPath = clientPath.resolve(clientFile);
        Path tempCoffeePath = coffeePath.resolve(coffeeFile);
        Path tempOrderPath = orderPath.resolve(orderFile);

        addressRepository = new XMLEncoderRepository<>(addressValidator, tempAddressPath.toFile().getAbsolutePath());
        clientRepository = new XMLEncoderRepository<>(clientValidator, tempClientPath.toFile().getAbsolutePath());
        coffeeRepository = new XMLEncoderRepository<>(coffeeValidator, tempCoffeePath.toFile().getAbsolutePath());
        orderRepository = new OrderEncoderRepository(orderValidator, tempOrderPath.toFile().getAbsolutePath());

        addressRepository.delete(10);
        clientRepository.delete(10);
        coffeeRepository.delete(10);
        orderRepository.delete(new ImmutablePair<>(30, 30));

        client2.setPhoneNumber("7777777777777777");
        coffee2.setPrice(700);
        order1.setStatus(Status.delivered);
        clientRepository.update(client2);
        coffeeRepository.update(coffee2);
        orderRepository.update(order1);

        assertEquals(17, Files.readAllLines(tempAddressPath).size());
        assertEquals(43, Files.readAllLines(tempClientPath).size());
        assertEquals(37, Files.readAllLines(tempCoffeePath).size());
        assertEquals(92, Files.readAllLines(tempOrderPath).size());
    }

    @Test
    @org.junit.jupiter.api.Order(3)
    public void loadTest() {
        Path tempAddressPath = addressPath.resolve(addressFile);
        Path tempClientPath = clientPath.resolve(clientFile);
        Path tempCoffeePath = coffeePath.resolve(coffeeFile);
        Path tempOrderPath = orderPath.resolve(orderFile);

        addressRepository = new XMLEncoderRepository<>(addressValidator, tempAddressPath.toFile().getAbsolutePath());
        clientRepository = new XMLEncoderRepository<>(clientValidator, tempClientPath.toFile().getAbsolutePath());
        coffeeRepository = new XMLEncoderRepository<>(coffeeValidator, tempCoffeePath.toFile().getAbsolutePath());
        orderRepository = new OrderEncoderRepository(orderValidator, tempOrderPath.toFile().getAbsolutePath());

        List<Address> addresses = StreamSupport.stream(addressRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());
        List<Client> clients = StreamSupport.stream(clientRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());
        List<Coffee> coffees = StreamSupport.stream(coffeeRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());
        List<Order> orders = StreamSupport.stream(orderRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());

        client2.setPhoneNumber("7777777777777777");
        coffee2.setPrice(700);
        order1.setStatus(Status.delivered);

        assertTrue(addresses.contains(address2));
        assertFalse(addresses.contains(address1));

        assertTrue(clients.contains(client2));
        assertTrue(clients.contains(client3));
        assertFalse(clients.contains(client1));

        assertTrue(coffees.contains(coffee2));
        assertTrue(coffees.contains(coffee3));
        assertFalse(coffees.contains(coffee1));

        assertTrue(orders.contains(order1));
        assertTrue(orders.contains(order2));
        assertTrue(orders.contains(order4));
        assertFalse(orders.contains(order3));
    }
}
