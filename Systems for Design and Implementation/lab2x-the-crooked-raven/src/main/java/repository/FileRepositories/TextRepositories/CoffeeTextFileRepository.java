package repository.FileRepositories.TextRepositories;

import domain.Coffee;
import domain.Validators.Validator;
import java.util.List;

/**
 *
 * Specialized TextFileRepository for entities of type Coffee
 */
public class CoffeeTextFileRepository extends TextFileRepository<Integer, Coffee> {

    public CoffeeTextFileRepository(Validator<Integer, Coffee> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Tries to convert a list of strings into a Coffee Entity
     * @param properties: the possible properties for a Coffee Entity
     * @return Coffee: if the conversion was successful, null otherwise
     */
    @Override
    protected Coffee generateEntity(List<String> properties) {
        Coffee coffee;
        try{
            coffee = Coffee.Builder()
                    .id(Integer.valueOf(properties.get(0)))
                    .name(properties.get(1))
                    .origin(properties.get(2))
                    .quantity((Integer) Validator.checkInput(properties.get(3), "null", true))
                    .price((Integer) Validator.checkInput(properties.get(4), "null", true))
                    .build();
        } catch (Exception e) {
            coffee = null;
        }
        return coffee;
    }

    /**
     * Converts a Coffee Entity into a csv-like string
     * @param coffee: the entity to be converted
     * @return String: the string form of the entity
     */
    @Override
    protected String convertEntity(Coffee coffee) {
        return coffee.getId() + ", " + coffee.getName() + ", " + coffee.getOrigin() +
                ", " + coffee.getQuantity() + ", " + coffee.getPrice();
    }

}
