package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessageEncoderDecoderImpl;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocolImpl;
import bgu.spl.net.srv.BaseServer;
import bgu.spl.net.srv.Server;

import java.util.function.Supplier;

public class StompServer {

    public static void main(String[] args) {
        if(args.length<2){
            System.out.println("please enter a port and a server mode");
        }
        else {
            int port = Integer.parseInt(args[0]);
            if(args[1].equalsIgnoreCase("tpc")) {
                System.out.println("thread per client mode");
                Server.threadPerClient(port, StompMessagingProtocolImpl::new, MessageEncoderDecoderImpl::new).serve();
            }
            if(args[1].equalsIgnoreCase("reactor")) {
                System.out.println("reactor  mode");
                int nThreads = Runtime.getRuntime().availableProcessors();
                Server.reactor(nThreads, port, StompMessagingProtocolImpl::new, MessageEncoderDecoderImpl::new).serve();
            }
        }
    }


}
