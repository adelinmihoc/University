package repository.FileRepositories.XMLRepositories;

import domain.Order;
import domain.Validators.Validator;
import org.apache.commons.lang3.tuple.Pair;

public class OrderXMLRepository extends XMLRepository<Pair<Integer, Integer>, Order> {
    public OrderXMLRepository(Validator<Pair<Integer, Integer>, Order> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Method for getting the class of the entities the repo is working with
     * @return {@code Class<T>}
     */
    @Override
    protected Class<Order> getEntityClass() {
        return Order.class;
    }
}
