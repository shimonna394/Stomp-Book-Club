package bgu.spl.net.api;

import bgu.spl.net.Messages.*;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;

public class StompMessagingProtocolImpl implements StompMessagingProtocol {
    /**
     * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
     *
     * @param connectionId
     * @param connections
     */
    int connectionId;
   Connections<Message> connections= ConnectionsImpl.getInstance();
    private boolean shouldTerminate=false;
    Message m;//message to process
    @Override
    public void start(int connectionId, Connections<String> connections) {//start the protocol with the connection id we want to work with
        this.connectionId=connectionId;
    }

    /**
     * As in MessagingProtocol, processes a given message.
     * Unlike MessagingProtocol, responses are sent via the connections object send functions if needed
     *
     * @param message
     */
    @Override
    public void process(String message) {
        boolean shouldDisconnect=false;
        Frame frame=new Frame(message);
        if(frame.getCommand().equalsIgnoreCase("connect"))
            m=new ConnectMessageReceived(frame,this.connectionId);
        else if(frame.getCommand().equalsIgnoreCase("disconnect")) {
            m = new DisconnectMessageReceived(frame, connectionId);
            shouldDisconnect=true;
        }
        else if(frame.getCommand().equalsIgnoreCase("send"))
            m=new SendMessageReceived(frame,connectionId);
        else if(frame.getCommand().equalsIgnoreCase("subscribe"))
            m=new SubscribeMessageReceived(frame,connectionId);
        else if(frame.getCommand().equalsIgnoreCase("unsubscribe"))
            m=new UnsubscribeMessageReceived(frame,connectionId);
        Message msg=m.process();
        if(msg!=null)
            connections.send(connectionId,msg);//process the message and send it by the connection handler related to the client
        if(msg instanceof ErrorMessage|shouldDisconnect) {
            System.out.println(m + " WE GOT AN ERROR");
            shouldTerminate = true;
        }
    }

    /**
     * @return true if the connection should be terminated
     */
    @Override
    public boolean shouldTerminate() {
        return shouldTerminate;
    }
}
