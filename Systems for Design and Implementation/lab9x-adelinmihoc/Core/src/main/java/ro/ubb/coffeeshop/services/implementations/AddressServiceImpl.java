package ro.ubb.coffeeshop.services.implementations;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import ro.ubb.coffeeshop.model.Address;
import ro.ubb.coffeeshop.repositories.AddressRepository;
import ro.ubb.coffeeshop.services.interfaces.AddressService;
import ro.ubb.coffeeshop.validators.Validator;

import java.util.List;

@Slf4j
@Service
@RequiredArgsConstructor
public class AddressServiceImpl implements AddressService {
    private final AddressRepository addressRepository;

    @Transactional
    @Override
    public void addAddress(Address address) {
        log.info("addAddress: address = {} method entered", address);
        this.addressRepository.save(address);
        log.info("addAddress method finished");
    }

    @Transactional
    @Override
    public void deleteAddress(Integer aid) {
        log.info("deleteAddress: aid = {} method entered", aid);
        this.addressRepository.deleteById(aid);
        log.info("deleteAddress method finished");
    }

    @Transactional
    @Override
    public void updateAddress(Address address, Integer aid) {
        log.info("updateAddress: address = {}, aid = {} method entered", address, aid);

        Address addressToUpdate = (Address) Validator.checkNull(this.addressRepository.findById(aid)
                .orElse(null), "address not found");
        addressToUpdate.setStreet(address.getStreet());
        addressToUpdate.setCity(address.getCity());
        addressToUpdate.setNumber(address.getNumber());
        this.addressRepository.save(addressToUpdate);
        log.info("updateAddress method finished");
    }

    @Override
    public List<Address> getAllAddresses() {
        log.info("getAllAddresses method entered");
        List<Address> addresses = this.addressRepository.findAll();
        log.info("getAllAddresses: addresses={} method finished", addresses);
        return addresses;
    }

    @Transactional
    @Override
    public void deleteAddressesByNumber(Integer number) {
        log.info("deleteAddressesByNumber: number={} method entered", number);
        this.addressRepository.deleteAddressByNumber(number);
        log.info("deleteAddressesByNumber method finished");

    }
}
