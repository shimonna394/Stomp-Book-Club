package bgu.spl.net.Messages;
/**
 * This class will manage every Frame that should be sent with the RECEIPT commend line
 */
public class Receipt implements Message {
    String msg;
    String id;
    public Receipt(String id){//building a receipt
        msg="RECEIPT"+'\n'+"receipt-id:"+id+'\n'+'\n'+'\u0000';
    }

    public String getId() {
        return id;
    }

    public String getMsg() {
        return msg;
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
