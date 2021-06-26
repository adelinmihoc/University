package ro.ubb.coffeeshop.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ro.ubb.coffeeshop.model.Customer;

import java.util.List;

@Repository
public interface CustomerRepository extends JpaRepository<Customer, Integer> {
    List<Customer> findAllByFirstNameContainingOrLastNameContaining(String firstName, String lastName);
    List<Customer> findAllByAgeAfterAndAgeBefore(Integer age1, Integer age2);
}
