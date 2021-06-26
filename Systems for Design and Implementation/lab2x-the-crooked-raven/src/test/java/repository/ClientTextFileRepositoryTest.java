package repository;

import domain.Client;
import domain.Validators.ClientValidator;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Order;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;
import repository.FileRepositories.TextRepositories.ClientTextFileRepository;

import static org.junit.jupiter.api.Assertions.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientTextFileRepositoryTest {

    @TempDir
    static Path tempDir;

    private Path tempClientsFile;
    private Repository<Integer, Client> clientRepo;
    private Client client1, client2, client3;
    private String fileName;
    private ClientValidator clientValidator;
    private Integer ageUpdated;

    @BeforeEach
    public void setUp() {
        clientValidator = new ClientValidator();
        ageUpdated = 50;

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
                .build();
        client3 = Client.Builder()
                .id(30)
                .firstName("Mike")
                .lastName("Tyson")
                .addressId(30)
                .build();

        fileName = "Clients.txt";
    }

    @AfterEach
    public void tearDown() {
        client1 = null;
        client2 = null;
        client3 = null;
        fileName = null;
        clientValidator = null;
        ageUpdated = null;
    }

    @Test
    @Order(1)
    public void saveClientTest() throws IOException {
        tempClientsFile = Files.createFile(tempDir.resolve(fileName));
        clientRepo = new ClientTextFileRepository(clientValidator, tempClientsFile.toFile().getAbsolutePath());

        assertNull(clientRepo.save(client1).orElse(null));
        assertNull(clientRepo.save(client2).orElse(null));
        assertNull(clientRepo.save(client3).orElse(null));
        assertEquals(3, Files.readAllLines(tempClientsFile).size());
    }

    @Test
    @Order(2)
    public void loadDataClientTest() {
        tempClientsFile = tempDir.resolve(fileName);
        clientRepo = new ClientTextFileRepository(clientValidator, tempClientsFile.toFile().getAbsolutePath());

        List<Client> clients = StreamSupport.stream(clientRepo.findAll().spliterator(), false)
                .collect(Collectors.toList());
        client2.setAge(ageUpdated);
        assertEquals(clients.size(), 3);
        assertTrue(clients.contains(client2));
        assertTrue(clients.contains(client3));
    }

}
