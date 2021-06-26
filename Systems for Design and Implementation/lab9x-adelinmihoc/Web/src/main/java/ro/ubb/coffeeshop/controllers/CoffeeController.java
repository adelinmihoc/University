package ro.ubb.coffeeshop.controllers;

import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;
import ro.ubb.coffeeshop.dtos.CoffeeDTO;
import ro.ubb.coffeeshop.mappers.CoffeeMapper;
import ro.ubb.coffeeshop.services.interfaces.CoffeeService;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequiredArgsConstructor
public class CoffeeController {
    public final CoffeeService coffeeService;
    public final CoffeeMapper coffeeMapper;

    @PostMapping("api/coffees")
    public void addCoffee(@RequestBody CoffeeDTO coffeeDTO) {
        coffeeService.addCoffee(coffeeMapper.dtoToCoffee(coffeeDTO));
    }

    @GetMapping("api/coffees")
    public List<CoffeeDTO> getAllCoffees() {
        return this.coffeeService.getAllCoffees().stream()
                .map(coffeeMapper::coffeeToDto)
                .collect(Collectors.toList());
    }

    @DeleteMapping("api/coffees/{cid}")
    public void deleteCoffee(@PathVariable Integer cid) {
        coffeeService.deleteCoffee(cid);
    }

    @PutMapping("api/coffees/{cid}")
    public void updateCoffee(@RequestBody CoffeeDTO coffeeDTO, @PathVariable Integer cid) {
        coffeeService.updateCoffee(coffeeMapper.dtoToCoffee(coffeeDTO), cid);
    }

}
