package domain.Validators;

import domain.ShopOrder;
import org.springframework.stereotype.Component;

import java.util.Optional;

@Component
public class OrderValidator implements Validator<Integer, ShopOrder> {
    /**
     * Constructor for OrderValidator. Performs different checks
     * @param entity: the order to be verified
     * @throws OrderValidatorException
     *          in case of null objects/fields or invalid data
     */
    @Override
    public void validate(ShopOrder entity) throws OrderValidatorException {
        checkNull(entity, "Object is null");
        checkNull(entity.getId(), "ShopOrder Id is null");
        checkId(entity.getId(), "Invalid id");
    }

    @Override
    public void checkNull(Object obj, String message) throws OrderValidatorException {
        Optional.ofNullable(obj).orElseThrow(() -> {
            throw new OrderValidatorException(message);
        });
    }

    @Override
    public void checkId(Integer integer, String message) throws ValidatorException {
        Optional.ofNullable(integer).filter(id -> id <= 0)
            .ifPresent(id -> {
                throw new OrderValidatorException(message);
            });
    }

}
