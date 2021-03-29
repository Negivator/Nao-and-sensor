package controller;

import model.Fcommond;
import model.Finfo;
import model.Output;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@RestController
@RequestMapping(value = "/family",method = RequestMethod.POST)
public class FamilyAction extends BaseAction {
//    插入一个family
    @RequestMapping(value = "/insertfamily",method = RequestMethod.POST)
    public Output insertFamily(@RequestParam("fname")String fname){
        return getAllService().getFamilyService().insertFamily(fname);
    }
//    更新家中数据
    @RequestMapping(value = "/update")
    public Output update(@RequestBody Finfo finfo){
        return getAllService().getFamilyService().update(finfo);
    }
//    通过轮询实现实时交互
    @RequestMapping(value = "/getcommond")
    public Output<Fcommond> getCommond(@RequestParam(value = "fid")Integer fid){
        return getAllService().getFamilyService().getCommond(fid);
    }
//    恢复commond默认状态
    @RequestMapping(value = "/recommond")
    @ResponseBody
    public Output commond(@RequestParam(value = "fid")Integer fid){
        return getAllService().getUserService().conmmond(fid,-1);
}
//    上传图片
    @RequestMapping(value = "/uppic")
    public Output upPic(@RequestPart("up")MultipartFile file,@RequestParam(value = "fid")Integer fid)throws IOException{
        return getAllService().getFamilyService().upPic(fid,file.getBytes());

    }
//    获取图片
    @RequestMapping(value = "/downpic")
    public void downPic(@RequestParam("fid")Integer fid, HttpServletResponse response) throws IOException{
        String fileName="pic.png";
        response.setContentType("image/png");
        byte[] b=getAllService().getFamilyService().getPic(fid);
        response.getOutputStream().write(getAllService().getFamilyService().getPic(fid));

    }
}
