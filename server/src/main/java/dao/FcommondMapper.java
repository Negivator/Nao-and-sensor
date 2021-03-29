package dao;

import model.Fcommond;
import org.springframework.stereotype.Repository;

@Repository
public interface FcommondMapper {
    int insert(Fcommond record);

    int insertSelective(Fcommond record);
    int update(Fcommond record);
    Fcommond select(Fcommond record);
}