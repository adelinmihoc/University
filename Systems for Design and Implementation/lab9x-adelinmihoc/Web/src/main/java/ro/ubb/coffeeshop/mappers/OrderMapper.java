package ro.ubb.coffeeshop.mappers;

import org.mapstruct.Mapper;
import org.mapstruct.factory.Mappers;
import ro.ubb.coffeeshop.dtos.OrderDTO;
import ro.ubb.coffeeshop.model.Order;
import org.mapstruct.Mapping;

@Mapper(config = NonBuilderConfigMapper.class, componentModel = "spring")
public interface OrderMapper extends DateMapper {
    OrderMapper INSTANCE = Mappers.getMapper(OrderMapper.class);

    @Mapping(target = "orderedCoffees", ignore = true)
    @Mapping(target = "localDateTime", source = "localDateTime", qualifiedByName = "stringToDate")
    Order dtoToOrder(OrderDTO orderDTO);
    @Mapping(target = "localDateTime", source = "localDateTime", qualifiedByName = "dateToString")
    OrderDTO orderToDto(Order order);
}
