package dao;

import model.Demo;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface DemoMapper {
    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table demo
     *
     * @mbggenerated
     */
    int insert(Demo record);

    /**
     * This method was generated by MyBatis Generator.
     * This method corresponds to the database table demo
     *
     * @mbggenerated
     */
    int insertSelective(Demo record);

    List<Demo> select();
}