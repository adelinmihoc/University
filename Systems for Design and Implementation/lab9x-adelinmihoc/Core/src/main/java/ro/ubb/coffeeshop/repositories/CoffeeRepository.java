package ro.ubb.coffeeshop.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;
import ro.ubb.coffeeshop.model.Coffee;

import java.util.List;

@Repository
public interface CoffeeRepository extends JpaRepository<Coffee, Integer> {
    @Query("select c from Coffee c where c.name like %:name%")
    List<Coffee> findAllByNameContaining(String name);
    @Query("select c from Coffee c where c.details.origin like %:origin%")
    List<Coffee> findAllByOriginContaining(String origin);
}
