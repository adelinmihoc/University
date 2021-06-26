package repository.FileRepositories.TextRepositories;

import domain.Order;
import domain.Status;
import domain.Validators.Validator;
import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Optional;

/**
 *
 * Specialized TextFileRepository for entities of type Order
 */
public class OrderTextFileRepository extends TextFileRepository<Pair<Integer, Integer>, Order> {
    public OrderTextFileRepository(Validator<Pair<Integer, Integer>, Order> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Tries to convert a list of strings into an Order Entity
     * @param properties: the possible properties for an Order Entity
     * @return Order: if the conversion was successful, null otherwise
     */
    @Override
    protected Order generateEntity(List<String> properties) {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd/HH:mm:ss");
        Order order;
        try {
            String statusString = (String) Validator.checkInput(properties.get(2), "null", false);
            String dateString = (String) Validator.checkInput(properties.get(3), "null", false);
            order = Order.Builder()
                    .id(new ImmutablePair<>(Integer.parseInt(properties.get(0)), Integer.parseInt(properties.get(1))))
                    .status(statusString == null ? null : Status.valueOf(statusString))
                    .time(dateString == null ? null : LocalDateTime.parse(dateString, formatter))
                    .build();

            Order finalOrder = order;
            Optional.of(properties).filter(p -> p.size() > 4).ifPresent(
                    props -> props.subList(4, props.size()).forEach(
                            ord -> finalOrder.getCoffeesId().add(Integer.parseInt(ord))));

            order = finalOrder;
        } catch (Exception e) {
            order = null;
        }
        return order;
    }

    /**
     * Converts an Order Entity into a csv-like string
     * @param entity: the entity to be converted
     * @return String: the string form of the entity
     */
    @Override
    protected String convertEntity(Order entity) {
        StringBuilder stringBuilder = new StringBuilder();
        entity.getCoffeesId().forEach(id -> stringBuilder.append(id).append(", "));
        Optional.of(stringBuilder).filter(e -> e.length() > 0).ifPresent(
                sb -> stringBuilder.delete(stringBuilder.length() - 2, stringBuilder.length()));

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd/HH:mm:ss");
        String orderString = entity.getId().getLeft() + ", " + entity.getId().getRight() + ", " + entity.getStatus() + ", " +
                (entity.getTime() == null ? null : entity.getTime().format(formatter));
        return stringBuilder.length() > 0 ? orderString + ", " + stringBuilder.toString() : orderString;
    }
}
