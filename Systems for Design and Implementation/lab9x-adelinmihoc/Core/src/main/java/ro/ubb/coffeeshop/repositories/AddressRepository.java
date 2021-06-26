package ro.ubb.coffeeshop.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import ro.ubb.coffeeshop.model.Address;

@Repository
public interface AddressRepository extends JpaRepository<Address, Integer> {
    void deleteAddressByNumber(Integer number);
}
