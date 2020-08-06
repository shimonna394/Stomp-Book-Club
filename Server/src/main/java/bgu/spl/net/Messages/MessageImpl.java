package bgu.spl.net.Messages;
/**
 * This class will manage every Frame that should be sent with the MESSAGE commend line
 */
public class MessageImpl implements Message {
    String msg;
    int subscription;
    int messageId;
    String destination;
    String frameBody;
    public MessageImpl(int sub, int message, String des, String frm){//building the message
        this.subscription=sub;
        this.messageId=message;
        this.destination=des;
        this.frameBody=frm;
        msg="MESSAGE"+'\n'+"subscription:"+this.subscription+'\n'+"Message-id:"+messageId+'\n'+"destination:"+destination+'\n'+'\n'+frameBody+'\n'+'\u0000';
    }

    public String getMsg() {
        return msg;
    }

    public String getFrameBody() {
        return frameBody;
    }

    public int getMessageId() {
        return messageId;
    }

    public int getSubscription() {
        return subscription;
    }

    public String getDestination() {
        return destination;
    }

    @Override
    public Message process() {
        return null;
    }

    @Override
    public boolean isLegal() {
        return false;
    }
}
