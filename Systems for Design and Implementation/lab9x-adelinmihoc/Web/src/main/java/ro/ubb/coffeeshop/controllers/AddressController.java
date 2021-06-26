package ro.ubb.coffeeshop.controllers;

import lombok.RequiredArgsConstructor;
import org.springframework.web.bind.annotation.*;
import ro.ubb.coffeeshop.dtos.AddressDTO;
import ro.ubb.coffeeshop.mappers.AddressMapper;
import ro.ubb.coffeeshop.services.interfaces.AddressService;

import java.util.List;
import java.util.stream.Collectors;

@RestController
@RequiredArgsConstructor
public class AddressController {
    private final AddressService addressService;
    private final AddressMapper addressMapper;

    @PostMapping("api/addresses")
    public void addAddress(@RequestBody AddressDTO addressDTO) {
        addressService.addAddress(addressMapper.dtoToAddress(addressDTO));
    }

    @GetMapping("/api/addresses")
    public List<AddressDTO> getAllAddresses() {
        return this.addressService.getAllAddresses().stream()
                .map(addressMapper::addressToDto)
                .collect(Collectors.toList());
    }

    @DeleteMapping("api/addresses/{aid}")
    public void deleteAddress(@PathVariable Integer aid) {
        this.addressService.deleteAddress(aid);
    }

    @PutMapping("api/addresses/{aid}")
    public void updateAddress(@RequestBody AddressDTO addressDTO, @PathVariable Integer aid) {
        this.addressService.updateAddress(addressMapper.dtoToAddress(addressDTO), aid);
    }

    @DeleteMapping("api/addresses/deleteAddressByNumber")
    public void deleteAddressesByNumber(@RequestParam(name = "number") Integer number) {
        this.addressService.deleteAddressesByNumber(number);
    }

}
