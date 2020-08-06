package bgu.spl.net.Messages;

public interface Message {//all the messages will implement this
public Message process();// the process on a message we have got from the client, we do what we have to do, and as a response we will return one of the above: connected,message,receipt,error
public boolean isLegal();//checking if the format of the message is legal, if not, should return an error message
public String getMsg();
}
