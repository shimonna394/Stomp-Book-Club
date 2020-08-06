package bgu.spl.net.Messages;

import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.User;

import java.util.HashMap;
import java.util.concurrent.LinkedBlockingQueue;
/**
 * This class will manage every Frame that should be sent with the SEND commend line
 */
public class SendMessageReceived implements Message {
    private String command="SEND";
    private HashMap<String,String> headers;
    private String framebody;
    private String topic;
    private int id;
    public SendMessageReceived(Frame frame,int connectionId){
       this.headers=frame.getHeaders();
       this.framebody=frame.getFrameBody();//contains the message to be sent
       this.id=connectionId;
       this.topic=headers.get("destination");
}

    @Override
    public Message process() {
        User user=(User)ConnectionsImpl.getInstance().getActiveUsersById().get(id);
        if(user.getTopics().get(topic)!=null)
            ConnectionsImpl.getInstance().send(topic,new MessageImpl(user.getTopics().get(topic).intValue(),ConnectionsImpl.getInstance().getNumOfMessages(),topic,framebody));
        else
            ConnectionsImpl.getInstance().send(topic,new MessageImpl(-1,ConnectionsImpl.getInstance().getNumOfMessages(),topic,framebody));
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
