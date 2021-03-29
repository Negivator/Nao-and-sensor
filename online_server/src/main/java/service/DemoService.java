package service;

import dao.AllDao;
import model.Demo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
@Transactional
public class DemoService {
    @Autowired
    AllDao allDao;
    public List<Demo> getList(){
        return allDao.getDemoMapper().select();
    }
}
