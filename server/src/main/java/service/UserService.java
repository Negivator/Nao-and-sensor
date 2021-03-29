package service;

import dao.AllDao;
import model.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Transactional
@Service
public class UserService {
    @Autowired
    private AllDao allDao;
//    注册
    public Output<String> register(String name,String pass){
        User user=new User();
        user.setUsername(name);
        user.setPassword(new BCryptPasswordEncoder().encode(pass));
        user.setEnable(1);
        Userpermission userpermission=new Userpermission();
        Output output=new Output();
        if(allDao.getUserMapper().selectByPrimaryKey(name)==null){
            allDao.getUserMapper().insert(user);
            userpermission.setUsername(name);
            userpermission.setPermission("user");
            allDao.getUserpermissionMapper().insert(userpermission);
            output.setCode(200);
        }
        else
        {
            output.setResult("该用户已存在");
        }
        return  output;
    }

//    登陆
    public Output login(String name,String pass){
        Output output=new Output();
        return output;
    }
//    创建和family的联系
    public Output<String> uf(String name,int fid){
        Output output=new Output();
        Familyuser familyuser=new Familyuser();
        familyuser.setFid(fid);
        familyuser.setUsername(name);
        if(allDao.getFamilyuserMapper().select(familyuser)==null){
            if(allDao.getFamilyuserMapper().insert(familyuser)==1)
                output.setCode(200);

        }
        else{
            output.setResult("不能绑定多个family");
        }

        return output;
    }
//    获取家中数据
    public Output<Finfo> getData(Integer fid){
        Output output=new Output();
        Finfo finfo=new Finfo();
        finfo.setFid(fid);
        finfo=allDao.getFinfoMapper().select(finfo);
        if(finfo!=null){
            output.setCode(200);
            output.setResult(finfo);
        }
        return  output;
    }
//    控制
    public Output conmmond(Integer fid,Integer cid){
        Output output=new Output();
        Fcommond fcommond=new Fcommond();
        fcommond.setFid(fid);
        fcommond.setFlag(cid);
        if(allDao.getFcommondMapper().select(fcommond)!=null){
            if(allDao.getFcommondMapper().update(fcommond)==1)
                output.setCode(200);
        }
        else
        {
            if(allDao.getFcommondMapper().insert(fcommond)==1){
                output.setCode(200);
            }
        }
        return output;
    }
//    获取family列表
    public Output<List<Family>> getFamily(){
        Output<List<Family>> output=new Output<>();
        List<Family> list=allDao.getFamilyMapper().selectAll();
        output.setCode(200);
        output.setResult(list);
        return  output;
    }
//    获取family关系
    public Output<Family> getFu(String name){
        Output<Family> output=new Output<>();
        Familyuser familyuser=new Familyuser();
        familyuser.setUsername(name);
        if((familyuser=allDao.getFamilyuserMapper().select(familyuser))!=null){
            Family family=new Family();
            family.setFid(familyuser.getFid());
            family=allDao.getFamilyMapper().selectByPrimaryKey(familyuser.getFid());
            output.setCode(200);
            output.setResult(family);
        }
        else{
            output.setCode(201);
        }
        return  output;
    }

//    创建f-u关系

    public Output fu(String name,Integer fid){
        Output output=new Output();
        Familyuser familyuser=new Familyuser();
        familyuser.setUsername(name);
        familyuser.setFid(fid);
//        先判断用户是否已经存在与family的关系
        if(allDao.getFamilyuserMapper().select(familyuser)==null){
            int i=allDao.getFamilyuserMapper().insert(familyuser);
            if(i==1){
                output.setCode(200);
            }
            else{
                output.setCode(201);
//                关系已经存在
            }

        }
        return output;
    }
//    修改密码
    public Output resetPass(String opass,String npass){

//        暂时没写
        Output output=new Output();
        return output;
    }
}
