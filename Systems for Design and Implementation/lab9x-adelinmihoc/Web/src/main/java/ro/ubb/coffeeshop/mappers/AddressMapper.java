package ro.ubb.coffeeshop.mappers;

import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.factory.Mappers;
import ro.ubb.coffeeshop.dtos.AddressDTO;
import ro.ubb.coffeeshop.model.Address;

@Mapper(config = NonBuilderConfigMapper.class, componentModel = "spring")
public interface AddressMapper {
    AddressMapper INSTANCE = Mappers.getMapper(AddressMapper.class);

    @Mapping(target = "customers", ignore = true)
    Address dtoToAddress(AddressDTO addressDTO);
    AddressDTO addressToDto(Address address);
}
