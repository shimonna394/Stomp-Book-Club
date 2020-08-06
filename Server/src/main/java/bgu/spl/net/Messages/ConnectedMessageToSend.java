package bgu.spl.net.Messages;

public class ConnectedMessageToSend implements Message {
    String msg;
    public ConnectedMessageToSend(){//building the connections
        msg="CONNECTED"+"\n"+"version:1.2"+'\n'+'\n'+'\u0000';
    }

    public String getMsg() {
        return msg;
    }

    public Message process() {
        return null;
    }

    @Override
    public boolean isLegal() {
        return false;
    }
}
