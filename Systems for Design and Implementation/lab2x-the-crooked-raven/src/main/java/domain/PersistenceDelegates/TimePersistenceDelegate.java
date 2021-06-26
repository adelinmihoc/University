package domain.PersistenceDelegates;

import java.beans.Encoder;
import java.beans.Expression;
import java.beans.PersistenceDelegate;
import java.time.LocalDateTime;

public class TimePersistenceDelegate extends PersistenceDelegate {
    @Override
    protected Expression instantiate(Object oldInstance, Encoder out) {
        LocalDateTime localDate = (LocalDateTime) oldInstance;
        return new Expression(localDate,
                LocalDateTime.class,
                "of",
                new Object[] {localDate.getYear(), localDate.getMonth(), localDate.getDayOfMonth(), localDate.getHour(),
                localDate.getMinute(), localDate.getSecond()});
    }
}
