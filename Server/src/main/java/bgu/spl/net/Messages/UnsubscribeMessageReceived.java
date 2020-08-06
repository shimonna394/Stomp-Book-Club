package bgu.spl.net.Messages;

import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.User;

import java.util.HashMap;
/**
 * This class will manage every Frame that should be sent with the UNSUBSCRIBE commend line
 */
public class UnsubscribeMessageReceived implements Message {
    private String command="UNSUBSCRIBE";
    private HashMap<String,String> headers;
    private int id;
    private String receipt;
    private int connectionId;
    public UnsubscribeMessageReceived(Frame frame,int connectionId){
        this.headers=frame.getHeaders();
        this.id=Integer.parseInt(headers.get("id"));
        this.receipt=headers.get("receipt");
        this.connectionId=connectionId;
    }

    @Override
    public Message process() {
        User user= (User) ConnectionsImpl.getInstance().getActiveUsersById().get(connectionId);
        boolean isSubscribed=ConnectionsImpl.getInstance().removeTopic(user.getTopic(id),user,id);
        if(isSubscribed)
            return new Receipt(receipt);
        else{
            return null;
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
