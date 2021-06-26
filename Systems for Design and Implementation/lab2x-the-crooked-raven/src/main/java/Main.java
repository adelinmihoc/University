import domain.*;
import domain.Validators.*;
import repository.*;
import repository.FileRepositories.XMLEncoderRepositories.*;
import repository.FileRepositories.XMLRepositories.*;
import repository.FileRepositories.TextRepositories.*;
import repository.InMemoryRepositories.InMemoryRepository;
import repository.dbrepository.*;
import service.*;
import ui.*;
import org.apache.commons.lang3.tuple.Pair;

import java.util.Scanner;


public class Main {
    private static final Validator<Integer, Client> clientValidator = new ClientValidator();
    private static final Validator<Integer, Coffee> coffeeValidator = new CoffeeValidator();
    private static final Validator<Integer, Address> addressValidator = new AddressValidator();
    private static final Validator<Pair<Integer, Integer>, Order> orderValidator = new OrderValidator();
    private static Repository<Integer, Client> clientRepository;
    private static Repository<Integer, Address> addressRepository;
    private static Repository<Integer, Coffee> coffeeRepository;
    private static Repository<Pair<Integer, Integer>, Order> orderRepository;
    private static ClientService clientService;
    private static AddressService addressService;
    private static CoffeeService coffeeService;
    private static OrderService orderService;

    private static void setServices() {
        addressService = new AddressService(addressRepository);
        clientService = new ClientService(clientRepository);
        coffeeService = new CoffeeService(coffeeRepository);
        orderService = new OrderService(orderRepository, coffeeRepository, clientRepository);
    }

    private static void useTextFilePersistence() {
        String clientsFileTxt = "../../../data/textFiles/clients.txt";
        String coffeeFileTxt = "../../../data/textFiles/coffee.txt";
        String addressFileTxt = "../../../data/textFiles/address.txt";
        String orderFileTxt = "../../../data/textFiles/order.txt";
        addressRepository = new AddressTextFileRepository(addressValidator, addressFileTxt);
        clientRepository = new ClientTextFileRepository(clientValidator, clientsFileTxt);
        coffeeRepository = new CoffeeTextFileRepository(coffeeValidator, coffeeFileTxt);
        orderRepository = new OrderTextFileRepository(orderValidator, orderFileTxt);
    }

    private static void useXMLFilePersistence() {
        String clientsFileXml = "../../../data/xmlFiles/clients.xml";
        String coffeeFileXml = "../../../data/xmlFiles/coffee.xml";
        String addressFileXml = "../../../data/xmlFiles/address.xml";
        String orderFileXml = "../../../data/xmlFiles/order.xml";
        addressRepository = new AddressXMLRepository(addressValidator, addressFileXml);
        clientRepository = new ClientXMLRepository(clientValidator, clientsFileXml);
        coffeeRepository = new CoffeeXMLRepository(coffeeValidator, coffeeFileXml);
        orderRepository = new OrderXMLRepository(orderValidator, orderFileXml);
    }

    private static void useXMLEncoderPersistence() {
        String clientsFileXml = "../../../data/xEncoderFiles/clients.xml";
        String coffeeFileXml = "../../../data/xEncoderFiles/coffee.xml";
        String addressFileXml = "../../../data/xEncoderFiles/address.xml";
        String orderFileXml = "../../../data/xEncoderFiles/order.xml";
        addressRepository = new XMLEncoderRepository<>(addressValidator, addressFileXml);
        clientRepository = new XMLEncoderRepository<>(clientValidator, clientsFileXml);
        coffeeRepository = new XMLEncoderRepository<>(coffeeValidator, coffeeFileXml);
        orderRepository = new OrderEncoderRepository(orderValidator, orderFileXml);
    }

    private static void useInMemoryPersistence() {
        addressRepository = new InMemoryRepository<>(addressValidator);
        clientRepository = new InMemoryRepository<>(clientValidator);
        coffeeRepository = new InMemoryRepository<>(coffeeValidator);
        orderRepository = new InMemoryRepository<>(orderValidator);
    }

    private static void useDatabasePersistence() throws ValidatorException {
        String database = "../../../data/database/coffeeShop.db";
        addressRepository = new AddressDbRepository(addressValidator, database);
        clientRepository = new ClientDbRepository(clientValidator, database);
        coffeeRepository = new CoffeeDbRepository(coffeeValidator, database);
        orderRepository = new OrderDbRepository(orderValidator, database);
    }

    private static void whatPersistence() throws ValidatorException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("""
                What kind of data persistence do you wish to use? >>>>
                1. In memory
                2. Text file
                3. Xml files verbose -- with encoder
                4. Xml files pretty -- with dataformat library
                5. Database
                >>>""");
        try {
            int number = Integer.parseInt(scanner.nextLine());
            switch (number) {
                case 1 -> useInMemoryPersistence();
                case 2 -> useTextFilePersistence();
                case 3 -> useXMLEncoderPersistence();
                case 4 -> useXMLFilePersistence();
                case 5 -> useDatabasePersistence();
                default -> { System.out.println("Invalid input"); System.exit(0); }
            }
        } catch (NumberFormatException e) {
            System.out.println("Invalid input");
            System.exit(0);
        }
    }

    public static void main(String[] args) {
        try {
            whatPersistence();
        } catch (ValidatorException ve) {
            System.out.println(ve.toString());
            useInMemoryPersistence();
        }

        setServices();
        Console console = new Console(clientService, coffeeService, addressService, orderService);
        console.runConsole();
    }

}