package bgu.spl.net.Messages;

import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.User;

import java.util.HashMap;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.LinkedBlockingQueue;
/**
 * This class will manage every Frame that should be sent with the DISCONNECT commend line
 */
public class DisconnectMessageReceived implements Message {
    private String command="DISCONNECT";
    private String receipt;
    private HashMap<String,String> headers;
    private int connectionId;
    public DisconnectMessageReceived(Frame frame,int connectionId){
        this.headers=frame.getHeaders();
        this.receipt=headers.get("receipt");
        this.connectionId=connectionId;
    }

    @Override
    public Message process() {
        ConnectionsImpl.getInstance().send(connectionId,new Receipt(receipt));
        User user=(User)ConnectionsImpl.getInstance().getActiveUsersById().get(connectionId);
        HashMap<String,Integer> topics=user.getTopics();
        Set<String>keysTopics= topics.keySet();//here we have all the topics the user subscribed to
        for (String topic:keysTopics) {
            ConnectionsImpl.getInstance().removeUserFromTopics(topic,connectionId);
        }
        user.deleteTopics();
        ConnectionsImpl.getInstance().disconnect(connectionId);
        return null;
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
