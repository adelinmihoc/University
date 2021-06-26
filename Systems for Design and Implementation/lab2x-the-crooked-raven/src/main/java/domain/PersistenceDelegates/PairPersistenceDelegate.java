package domain.PersistenceDelegates;

import org.apache.commons.lang3.tuple.ImmutablePair;
import java.beans.Encoder;
import java.beans.Expression;
import java.beans.PersistenceDelegate;

public class PairPersistenceDelegate extends PersistenceDelegate {
    @Override
    @SuppressWarnings("unchecked")
    protected Expression instantiate(Object oldInstance, Encoder out) {
        ImmutablePair<Integer, Integer> idPair = (ImmutablePair<Integer, Integer>) oldInstance;
        return new Expression(idPair,
                ImmutablePair.class,
                "new",
                new Object[] {idPair.getLeft(), idPair.getRight()});
    }
}
