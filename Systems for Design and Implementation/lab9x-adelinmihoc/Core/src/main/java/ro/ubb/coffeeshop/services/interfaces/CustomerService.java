package ro.ubb.coffeeshop.services.interfaces;

import ro.ubb.coffeeshop.model.Customer;

import java.util.List;

public interface CustomerService {
    void addCustomer(Customer customer);
    void deleteCustomer(Integer cid);
    void updateCustomer(Customer customer, Integer cid);
    List<Customer> getAllCustomers();

    List<Customer> filterCustomersByName(String name);
    List<Customer> filterCustomersByAgeInterval(Integer age1, Integer age2);

}
