package ro.ubb.coffeeshop.services.interfaces;

import ro.ubb.coffeeshop.model.Coffee;
import ro.ubb.coffeeshop.model.Order;
import ro.ubb.coffeeshop.model.Status;

import java.util.List;

public interface OrderService {
    void addOrder(Integer clientId);
    void deleteOrder(Integer oid);
    void changeStatus(Integer oid, Status status);
    List<Order> getAllOrders();

    List<Order> filterCustomerOrders(Integer cid);
    List<Coffee> filterCustomerCoffees(Integer cid);
    List<Coffee> getCoffees(Integer oid);
    void addCoffeeToOrder(Integer oid, Integer cid);
}
