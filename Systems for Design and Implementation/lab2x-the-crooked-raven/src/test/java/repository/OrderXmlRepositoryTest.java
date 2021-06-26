package repository;

import domain.Order;
import domain.Status;
import domain.Validators.OrderValidator;
import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;
import repository.FileRepositories.XMLRepositories.OrderXMLRepository;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

import static org.junit.jupiter.api.Assertions.*;

public class OrderXmlRepositoryTest {

    @TempDir
    static Path tempDir;

    private OrderValidator orderValidator;
    private String tempFile;
    private Path tempPath;
    private Order order1, order2, order3, order4;
    private Repository<Pair<Integer, Integer>, Order> orderRepository;
    private Status statusUpdate;

    @BeforeEach
    public void setUp() {
        orderValidator = new OrderValidator();
        tempFile = "order.xml";
        statusUpdate = Status.canceled;

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
        order1 = null;
        order2 = null;
        order3 = null;
        order4 = null;
        orderValidator = null;
        statusUpdate = null;
        tempFile = null;
    }

    @Test
    @org.junit.jupiter.api.Order(1)
    public void saveTest() throws IOException {
        tempPath = Files.createFile(tempDir.resolve(tempFile));
        orderRepository = new OrderXMLRepository(orderValidator, tempPath.toFile().getAbsolutePath());

        assertNull(orderRepository.save(order1).orElse(null));
        assertNull(orderRepository.save(order2).orElse(null));
        assertNull(orderRepository.save(order3).orElse(null));
        assertNull(orderRepository.save(order4).orElse(null));
        assertEquals(36, Files.readAllLines(tempPath).size());
    }

    @Test
    @org.junit.jupiter.api.Order(2)
    public void operationsTest() throws IOException {
        tempPath = tempDir.resolve(tempFile);
        orderRepository = new OrderXMLRepository(orderValidator, tempPath.toFile().getAbsolutePath());

        orderRepository.delete(order1.getId());
        order3.setStatus(statusUpdate);
        orderRepository.update(order3);
        assertEquals(28, Files.readAllLines(tempPath).size());
    }

    @Test
    @org.junit.jupiter.api.Order(3)
    public void loadDataTest() {
        tempPath = tempDir.resolve(tempFile);
        orderRepository = new OrderXMLRepository(orderValidator, tempPath.toFile().getAbsolutePath());

        order3.setStatus(statusUpdate);
        List<Order> orders = StreamSupport.stream(orderRepository.findAll().spliterator(), false)
                .collect(Collectors.toList());
        assertEquals(3, orders.size());
        assertTrue(orders.contains(order2));
        assertTrue(orders.contains(order3));
        assertTrue(orders.contains(order4));
    }

}
