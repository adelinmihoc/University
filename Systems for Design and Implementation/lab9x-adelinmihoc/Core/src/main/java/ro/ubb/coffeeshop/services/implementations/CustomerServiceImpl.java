package ro.ubb.coffeeshop.services.implementations;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import ro.ubb.coffeeshop.model.Address;
import ro.ubb.coffeeshop.model.Customer;
import ro.ubb.coffeeshop.repositories.AddressRepository;
import ro.ubb.coffeeshop.repositories.CustomerRepository;
import ro.ubb.coffeeshop.services.interfaces.CustomerService;
import ro.ubb.coffeeshop.validators.Validator;

import java.util.List;

@Slf4j
@Service
@RequiredArgsConstructor
public class CustomerServiceImpl implements CustomerService {
    private final CustomerRepository customerRepository;
    private final AddressRepository addressRepository;

    @Override
    public void addCustomer(Customer customer) {
        log.info("addCustomer: customer={} method entered", customer);
        Address address = (Address) Validator.checkNull(this.addressRepository.findById(customer.getAddress().getId())
                .orElse(null), "address not found");
        customer.setAddress(address);
        this.customerRepository.save(customer);
        log.info("addCustomer method finished");
    }

    @Override
    public void deleteCustomer(Integer cid) {
        log.info("deleteCustomer: cid={} method entered", cid);
        Customer customer = (Customer) Validator.checkNull(this.customerRepository.findById(cid)
                .orElse(null), "customers not found");
        Address address = customer.getAddress();
        address.getCustomers().remove(customer);
        this.customerRepository.deleteById(cid);
        this.addressRepository.save(address);
        log.info("deleteCustomer method finished");
    }

    @Override
    public void updateCustomer(Customer customer, Integer cid) {
        log.info("updateCustomer: customer={}, cid={} method entered", customer, cid);
        Customer customerToUpdate = (Customer) Validator.checkNull(this.customerRepository.findById(cid)
                .orElse(null), "customer not found");
        Address address = (Address) Validator.checkNull(this.addressRepository.findById(customer.getAddress().getId())
                .orElse(null), "address not found");

        customerToUpdate.setFirstName(customer.getFirstName());
        customerToUpdate.setLastName(customer.getLastName());
        customerToUpdate.setPhoneNumber(customer.getPhoneNumber());
        customerToUpdate.setAge(customer.getAge());
        customerToUpdate.setAddress(address);

        this.customerRepository.save(customerToUpdate);
        log.info("updateCustomer method finished");
    }

    @Override
    public List<Customer> getAllCustomers() {
        log.info("getAllCustomers method entered");
        List<Customer> customers = this.customerRepository.findAll();
        log.info("getAllCustomers: customers={} method finished", customers);
        return customers;
    }

    @Override
    public List<Customer> filterCustomersByName(String name) {
        log.info("filterCustomersByName: name={} method entered", name);
        List<Customer> customers = this.customerRepository.findAllByFirstNameContainingOrLastNameContaining(name, name);
        log.info("filterCustomersByName: customers={} method finished", customers);
        return customers;
    }

    @Override
    public List<Customer> filterCustomersByAgeInterval(Integer age1, Integer age2) {
        log.info("filterCustomersByAgeInterval: age={}, age2={} method entered", age1, age2);
        List<Customer> customers = this.customerRepository.findAllByAgeAfterAndAgeBefore(age1, age2);
        log.info("filterCustomersByAgeInterval: customers={} method finished", customers);
        return customers;
    }
}
