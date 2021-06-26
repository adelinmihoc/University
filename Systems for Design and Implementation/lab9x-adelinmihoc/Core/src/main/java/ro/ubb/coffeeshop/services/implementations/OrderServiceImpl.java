package ro.ubb.coffeeshop.services.implementations;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import ro.ubb.coffeeshop.model.Coffee;
import ro.ubb.coffeeshop.model.Customer;
import ro.ubb.coffeeshop.model.Order;
import ro.ubb.coffeeshop.model.Status;
import ro.ubb.coffeeshop.repositories.CoffeeRepository;
import ro.ubb.coffeeshop.repositories.CustomerRepository;
import ro.ubb.coffeeshop.repositories.OrderRepository;
import ro.ubb.coffeeshop.services.interfaces.OrderService;
import ro.ubb.coffeeshop.validators.Validator;

import java.time.LocalDateTime;
import java.util.List;

@Slf4j
@Service
@RequiredArgsConstructor
public class OrderServiceImpl implements OrderService {
    private final OrderRepository orderRepository;
    private final CoffeeRepository coffeeRepository;
    private final CustomerRepository customerRepository;

    @Override
    public void addOrder(Integer customerId) {
        log.info("addOrder: customerId={} method entered", customerId);
        Customer customer = (Customer) Validator.checkNull(this.customerRepository
                .findById(customerId).orElse(null), "customer not found");

        Order order = Order.builder()
                .customer(customer)
                .status(Status.pending)
                .localDateTime(LocalDateTime.now())
                .build();

        this.orderRepository.save(order);
        log.info("addOrder method finished");
    }

    @Override
    public void deleteOrder(Integer oid) {
        log.info("deleteOrder: oid={} method entered", oid);
        Order order = (Order) Validator.checkNull(this.orderRepository.findById(oid)
                .orElse(null), "order not found");
        Customer customer = order.getCustomer();
        customer.getOrders().remove(order);

        order.getOrderedCoffees().forEach(coffee -> {
            coffee.getOrders().remove(order);
            coffeeRepository.save(coffee);
        });
        this.customerRepository.save(customer);
        log.info("deleteOrder method finished");
    }

    @Override
    public void changeStatus(Integer oid, Status status) {
        log.info("changeStatus: oid={}, status={} method entered", oid, status);
        Order orderToUpdate = (Order) Validator.checkNull(this.orderRepository.findById(oid)
                .orElse(null), "order not found");

        orderToUpdate.setStatus(status);

        this.orderRepository.save(orderToUpdate);
    }

    @Override
    public List<Order> getAllOrders() {
        log.info("getAllOrders method entered");
        List<Order> orders = this.orderRepository.findAll();
        log.info("getAllOrders: orders={} method finished", orders);
        return orders;
    }

    @Override
    public List<Order> filterCustomerOrders(Integer cid) {
        log.info("filterCustomerOrders: cid={} method entered", cid);
        Customer customer = (Customer) Validator.checkNull(this.customerRepository.findById(cid)
                .orElse(null), "customer not found");
        List<Order> orders = this.orderRepository.findAllByCustomer(customer);
        log.info("filterCustomerOrders: orders={} method finished", orders);
        return orders;
    }

    @Override
    public List<Coffee> filterCustomerCoffees(Integer cid) {
        log.info("filterCustomerCoffees: cid={} method entered", cid);
        Customer customer = (Customer) Validator.checkNull(this.customerRepository.findById(cid)
                .orElse(null), "customer not found");
        List<Coffee> coffees = this.orderRepository.findCustomerCoffees(customer);
        log.info("filterCustomerCoffees: coffees={} method finished", coffees);
        return coffees;
    }

    @Override
    public List<Coffee> getCoffees(Integer oid) {
        log.info("getCoffees: oid={} method entered", oid);
        Order order = (Order) Validator.checkNull(this.orderRepository
                .findById(oid).orElse(null), "order not found");
        List<Coffee> coffees = order.getOrderedCoffees();
        log.info("getCoffees: coffees={} method finished", coffees);
        return coffees;
    }

    @Override
    public void addCoffeeToOrder(Integer oid, Integer cid) {
        log.info("addCoffeeToOrder: oid={}, cid={} method entered", oid, cid);
        Order order = (Order) Validator.checkNull(this.orderRepository.findById(oid)
                .orElse(null), "order not found");
        Coffee coffee = (Coffee) Validator.checkNull(this.coffeeRepository.findById(cid)
                .orElse(null), "coffee not found");
        order.getOrderedCoffees().add(coffee);
        this.orderRepository.save(order);
        log.info("addCoffeeToOrder method finished");
    }
}
