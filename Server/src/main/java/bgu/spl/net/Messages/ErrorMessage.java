package bgu.spl.net.Messages;
/**
 * This class will manage every Frame that should be sent with the ERROR commend line
 */
public class ErrorMessage implements Message {
    String msg;
    String messageError;
    public ErrorMessage(String messageError){//constructor for error message without anything related
        this.messageError=messageError;
        msg="ERROR"+'\n'+"message:"+messageError+'\n'+'\n'+'\u0000';

    }
    public ErrorMessage(String messageError,int id){
        this.messageError=messageError;
        msg="ERROR"+'\n'+"receipt-id:"+id+"\nmessage:"+messageError+'\n'+'\n'+'\u0000';
    }

    public String getMsg() {
        return msg;
    }

    public String getMessageError() {
        return messageError;
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
