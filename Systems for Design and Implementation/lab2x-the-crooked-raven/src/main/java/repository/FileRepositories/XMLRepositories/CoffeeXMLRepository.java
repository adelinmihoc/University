package repository.FileRepositories.XMLRepositories;

import domain.Coffee;
import domain.Validators.Validator;

public class CoffeeXMLRepository extends XMLRepository<Integer, Coffee>{

    public CoffeeXMLRepository(Validator<Integer, Coffee> validator, String fileName) {
        super(validator, fileName);
    }

    /**
     * Method for getting the class of the entities the repo is working with
     * @return {@code Class<T>}
     */
    @Override
    protected Class<Coffee> getEntityClass() {
        return Coffee.class;
    }

}
