package ro.ubb.coffeeshop.mappers;

import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.factory.Mappers;
import ro.ubb.coffeeshop.dtos.CoffeeDTO;
import ro.ubb.coffeeshop.model.Coffee;

@Mapper(config = NonBuilderConfigMapper.class, componentModel = "spring")
public interface CoffeeMapper {
    CoffeeMapper INSTANCE = Mappers.getMapper(CoffeeMapper.class);

    @Mapping(target = "orders", ignore = true)
    @Mapping(target = "details", ignore = true)
    Coffee dtoToCoffee(CoffeeDTO coffeeDTO);
    CoffeeDTO coffeeToDto(Coffee coffee);
}
