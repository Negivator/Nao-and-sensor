package dao;

import model.Userpermission;
import org.springframework.stereotype.Repository;

@Repository
public interface UserpermissionMapper {
    int insert(Userpermission record);

    int insertSelective(Userpermission record);
}