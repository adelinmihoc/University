package ro.ubb.coffeeshop.dtos;

import lombok.*;
import ro.ubb.coffeeshop.model.Status;

@Data
@ToString
@EqualsAndHashCode
@AllArgsConstructor
@NoArgsConstructor
public class OrderDTO {
    private Integer id;
    private CustomerDTO customer;
    private Status status;
    private String localDateTime;
}
