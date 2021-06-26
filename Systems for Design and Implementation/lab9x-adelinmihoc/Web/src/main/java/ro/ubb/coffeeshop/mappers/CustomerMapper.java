package ro.ubb.coffeeshop.mappers;

import org.mapstruct.Mapper;
import org.mapstruct.factory.Mappers;
import ro.ubb.coffeeshop.dtos.CustomerDTO;
import ro.ubb.coffeeshop.model.Customer;

@Mapper(config = NonBuilderConfigMapper.class, componentModel = "spring")
public interface CustomerMapper {
    CustomerMapper INSTANCE = Mappers.getMapper(CustomerMapper.class);

    Customer dtoToCustomer(CustomerDTO customerDTO);
    CustomerDTO customerToDTO(Customer customer);
}
