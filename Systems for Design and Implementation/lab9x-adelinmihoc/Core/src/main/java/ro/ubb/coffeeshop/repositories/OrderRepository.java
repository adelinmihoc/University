package ro.ubb.coffeeshop.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import ro.ubb.coffeeshop.model.Coffee;
import ro.ubb.coffeeshop.model.Customer;
import ro.ubb.coffeeshop.model.Order;

import java.util.List;

@Repository
public interface OrderRepository extends JpaRepository<Order, Integer> {
    List<Order> findAllByCustomer(Customer customer);

    @Query("select distinct o.orderedCoffees from Order o where o.customer = ?1")
    List<Coffee> findCustomerCoffees(Customer customer);
}
