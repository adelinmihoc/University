package ro.ubb.coffeeshop.controllers;

import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;
import ro.ubb.coffeeshop.dtos.CoffeeDTO;
import ro.ubb.coffeeshop.dtos.OrderDTO;
import ro.ubb.coffeeshop.mappers.CoffeeMapper;
import ro.ubb.coffeeshop.mappers.OrderMapper;
import ro.ubb.coffeeshop.model.Status;
import ro.ubb.coffeeshop.services.interfaces.OrderService;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequiredArgsConstructor
public class OrderController {
    private final OrderService orderService;
    private final OrderMapper orderMapper;
    private final CoffeeMapper coffeeMapper;

    @PostMapping("api/orders")
    public void addOrder(@RequestParam(name = "customerId") Integer customerId) {
        this.orderService.addOrder(customerId);
    }

    @GetMapping("api/orders")
    public List<OrderDTO> getAllOrders() {
        return this.orderService.getAllOrders().stream()
                .map(orderMapper::orderToDto)
                .collect(Collectors.toList());
    }

    @GetMapping("api/orders/{oid}/coffees")
    public List<CoffeeDTO> getOrderCoffees(@PathVariable Integer oid) {
        return this.orderService.getCoffees(oid).stream()
                .map(coffeeMapper::coffeeToDto)
                .collect(Collectors.toList());
    }

    @PutMapping("api/orders/{oid}/coffees/{cid}")
    public void addCoffeeToOrder(@PathVariable Integer oid, @PathVariable Integer cid) {
        this.orderService.addCoffeeToOrder(oid, cid);
    }

    @DeleteMapping("api/orders/{oid}")
    public void deleteOrder(@PathVariable Integer oid) {
        this.orderService.deleteOrder(oid);
    }

    @PutMapping("api/orders/{oid}")
    public void changeOrderStatus(@PathVariable Integer oid, @RequestParam(name = "status") Status status) {
        this.orderService.changeStatus(oid, status);
    }

    @GetMapping("api/orders/filterCustomerCoffees")
    public List<CoffeeDTO> filterCustomerCoffees(@RequestParam(name = "customerId") Integer cid) {
        return this.orderService.filterCustomerCoffees(cid).stream()
                .map(coffeeMapper::coffeeToDto)
                .collect(Collectors.toList());
    }

    @GetMapping("api/orders/filterCustomerOrders")
    public List<OrderDTO> filterCustomerOrders(@RequestParam(name = "customerId") Integer cid) {
        return this.orderService.filterCustomerOrders(cid).stream()
                .map(orderMapper::orderToDto)
                .collect(Collectors.toList());
    }
}
