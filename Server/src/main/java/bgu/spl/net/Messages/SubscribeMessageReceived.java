package bgu.spl.net.Messages;

import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.User;

import java.util.HashMap;
/**
 * This class will manage every Frame that should be sent with the SUBSCRIBE commend line
 */
public class SubscribeMessageReceived implements Message {
    private String command="SUBSCRIBE";
    private HashMap<String,String> headers;
    private int id;
    private String des;
    private String receipt;
    private int connectionId;
    public SubscribeMessageReceived(Frame frame,int connectionId){
        this.headers=frame.getHeaders();
        this.id=Integer.parseInt(headers.get("id"));
        this.des=headers.get("destination");
        this.receipt=headers.get("receipt");
        this.connectionId=connectionId;
    }

    @Override
    public Message process() {
        User user= (User) ConnectionsImpl.getInstance().getActiveUsersById().get(connectionId);
        ConnectionsImpl.getInstance().addToTopic(des,user,id);
        return new Receipt(receipt);
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
