package controller;

import model.Family;
import model.Output;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.List;

@Controller
@RequestMapping(value = "/user",method = RequestMethod.POST)
public class UserAction extends BaseAction {
//    注册
    @RequestMapping(value = "/register")
    @ResponseBody
    public Output register(@RequestParam(value = "name")String name,@RequestParam(value = "pass")String pass){
        return getAllService().getUserService().register(name,pass);
    }
//    登陆
    @RequestMapping(value = "/login",method = RequestMethod.GET)
    public String login(){
        return "../public/login.html";
    }
//    创建family联系
    @RequestMapping(value = "/createfu")
    @ResponseBody
    public Output<String> cfu(@RequestParam(value = "fid")Integer fid,@RequestParam(value = "name")String name){
        return getAllService().getUserService().uf(name,fid);

    }
//    获取家中数据
    @RequestMapping(value = "/getData")
    @ResponseBody
    public Output getData(@RequestParam(value = "fid")Integer fid){
        return getAllService().getUserService().getData(fid);
    }
//    控制
    @RequestMapping(value = "/commond")
    @ResponseBody
    public Output commond(@RequestParam(value = "cid")Integer cid,@RequestParam(value = "fid")Integer fid){
        return getAllService().getUserService().conmmond(fid,cid);
    }
//    获取family列表
    @RequestMapping(value="/getFamily")
    @ResponseBody
    public Output<List<Family>> getFamily(){
        return  getAllService().getUserService().getFamily();
    }
//    获取family关系
    @RequestMapping(value = "/getFu")
    @ResponseBody
    public Output<Family> getFu(@RequestParam(value = "uid")String  name){
        return getAllService().getUserService().getFu(name);
    }
//    绑定family
    @RequestMapping(value = "/fu")
    @ResponseBody
    public Output fu(@RequestParam(value = "fid")Integer fid,@RequestParam(value = "uid")String name){
        return getAllService().getUserService().uf(name,fid);
    }
//    修改密码
    @RequestMapping(value = "/resetpass")
    @ResponseBody
    public Output reSetPass(@RequestParam(value = "opass")String opass,@RequestParam(value = "npass")String npass){
        return getAllService().getUserService().resetPass(opass,npass);
    }
//    登陆成功
    @RequestMapping(value = "/loginsuccess",method = RequestMethod.GET)
    @ResponseBody
    public Output loginSuccess(){
        Output output=new Output();
        output.setCode(200);
        return output;
    }
//    登陆失败
    @RequestMapping(value = "/loginfail")
    @ResponseBody
    public Output loginFail(){
        Output output=new Output();
        output.setCode(201);

        output.setResult(getSession().getAttributeNames());
        return output;
    }



    public static HttpSession getSession() {
        HttpSession session = null;
        try {
            session = getRequest().getSession();
        } catch (Exception e) {}
        return session;
    }

    public static HttpServletRequest getRequest() {
        ServletRequestAttributes attrs =(ServletRequestAttributes) RequestContextHolder.getRequestAttributes();
        return attrs.getRequest();
    }


}
