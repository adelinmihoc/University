package ro.ubb.coffeeshop.controllers;

import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;
import ro.ubb.coffeeshop.dtos.CustomerDTO;
import ro.ubb.coffeeshop.mappers.CustomerMapper;
import ro.ubb.coffeeshop.services.interfaces.CustomerService;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequiredArgsConstructor
public class CustomerController {
    private final CustomerService customerService;
    private final CustomerMapper customerMapper;

    @PostMapping("api/customers")
    public void addCustomer(@RequestBody CustomerDTO customerDTO) {
        this.customerService.addCustomer(customerMapper.dtoToCustomer(customerDTO));
    }

    @GetMapping("api/customers")
    public List<CustomerDTO> getAllCustomers() {
        return this.customerService.getAllCustomers().stream()
                .map(customerMapper::customerToDTO)
                .collect(Collectors.toList());
    }

    @DeleteMapping("api/customers/{cid}")
    public void deleteCustomer(@PathVariable Integer cid) {
        this.customerService.deleteCustomer(cid);
    }

    @PutMapping("api/customers/{cid}")
    public void updateCustomer(@RequestBody CustomerDTO customerDTO, @PathVariable Integer cid) {
        this.customerService.updateCustomer(customerMapper.dtoToCustomer(customerDTO), cid);
    }

    @GetMapping("api/customers/filterCustomersByName")
    public List<CustomerDTO> filterCustomersByName(@RequestParam(name = "name") String name) {
        return this.customerService.filterCustomersByName(name).stream()
                .map(customerMapper::customerToDTO)
                .collect(Collectors.toList());
    }

    @GetMapping("api/customers/filterCustomersByAgeInterval")
    public List<CustomerDTO> filterCustomersByAgeInterval(
            @RequestParam(name = "age1") Integer age1,
            @RequestParam(name = "age2") Integer age2) {
        return this.customerService.filterCustomersByAgeInterval(age1, age2).stream()
                .map(customerMapper::customerToDTO)
                .collect(Collectors.toList());
    }
}
