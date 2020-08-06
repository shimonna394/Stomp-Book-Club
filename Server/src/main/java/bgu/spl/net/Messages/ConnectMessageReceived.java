package bgu.spl.net.Messages;

import bgu.spl.net.api.StompMessagingProtocolImpl;
import bgu.spl.net.srv.*;

import java.util.HashMap;
/**
 * This class will manage every Frame that should be sent with the CONNECTED commend line
 */
public class ConnectMessageReceived implements Message {
    private String command="CONNECT";
    private HashMap<String,String> headers;
    private String userName;
    private String password;
    private Integer id;
    public ConnectMessageReceived(Frame frame, int id){
        this.headers=frame.getHeaders();
        this.userName=headers.get("login");
        this.password=headers.get("passcode");
        this.id=id;
    }

    @Override
    public Message process() {
        if(ConnectionsImpl.getInstance().getUsersByName().containsKey(userName)){//if user exists
            User user= (User) ConnectionsImpl.getInstance().getUsersByName().get(userName);
            if(user.isActive()) {
                return new ErrorMessage("user "+userName+" is already connected");
            }
            else {
                if(user.getUserPassword().compareTo(password)!=0) {//password is wrong
                    return new ErrorMessage("passcode for user " + userName + " is incorrect");

                }
                else{
                    user.connect();
                    user.setUserId(id);
                    ConnectionsImpl.getInstance().addActiveUsersById(id,user);
                    return new ConnectedMessageToSend();
                }
            }
        }
        else{
           User user=new User(userName,id,password);
           ConnectionsImpl.getInstance().addUserByName(userName,user);
           ConnectionsImpl.getInstance().addActiveUsersById(id,user);
           return new ConnectedMessageToSend();
        }
    }

    @Override
    public boolean isLegal() {
        return false;
    }

    @Override
    public String getMsg() {
        return null;
    }
}
