package ro.ubb.coffeeshop.services.interfaces;

import ro.ubb.coffeeshop.model.Address;

import java.util.List;

public interface AddressService {
    void addAddress(Address address);
    void deleteAddress(Integer aid);
    void updateAddress(Address address, Integer aid);
    List<Address> getAllAddresses();

    void deleteAddressesByNumber(Integer number);
}
