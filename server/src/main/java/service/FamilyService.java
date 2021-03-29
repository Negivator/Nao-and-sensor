package service;

import dao.AllDao;
import model.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.Date;

@Transactional
@Service
public class FamilyService {
    @Autowired
    private AllDao allDao;
//    增加family
    public Output insertFamily(String fname){
        Family family=new Family();
        family.setFname(fname);
        int i=allDao.getFamilyMapper().insert(family);
        Output output=new Output();
        if(i==1){
            output.setCode(200);
        }
        return  output;
    }
//    更新家中数据
    public Output update(Finfo finfo){
        int i;
        if(allDao.getFinfoMapper().select(finfo)!=null){
            i=allDao.getFinfoMapper().update(finfo);
        }
        else
        {
            i=allDao.getFinfoMapper().insertSelective(finfo);
        }

        Output output=new Output();
        if(i==1)
            output.setCode(200);
        return output;
    }
//    轮询命令
    public Output<Fcommond> getCommond(Integer fid){
        Output<Fcommond> output=new Output<>();
        Fcommond fcommond=new Fcommond();
        fcommond.setFid(fid);
        if((fcommond=allDao.getFcommondMapper().select(fcommond))!=null){
            output.setCode(200);
            output.setResult(fcommond);
        }
        else{
            output.setCode(201);

        }
        return  output;
    }

//    上传图片
    public Output upPic(int fid,byte[] bytes){
        Fpic fpic=new Fpic();
        fpic.setFid(fid);
        fpic.setPic(bytes);
        fpic.setTime(new Date());
        int i=allDao.getFpicMapper().insert(fpic);
        Output output=new Output();
        if(i>0)
            output.setCode(200);
        return  output;
    }
//    获取图片
    public byte[] getPic(int fid){
        Fpic fpic=new Fpic();
        fpic.setFid(fid);
        return allDao.getFpicMapper().select(fpic).getPic();

    }

}
