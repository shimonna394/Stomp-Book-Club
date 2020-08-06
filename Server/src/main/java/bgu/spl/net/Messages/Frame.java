package bgu.spl.net.Messages;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
/**
 * This class will break down the clients messages to the form of a FRAME
 */
public class Frame {
    String command;
    HashMap<String,String> headers = new HashMap<String, String>();
    String frameBody;
    public Frame(String message){//take a string from decoder and change it to a frame format
        String [] msg =message.split("\n",message.length());
        command=msg[0];
        List<String> headerLines=new LinkedList<String>();
        int i=1;
        while(msg[i].length()!=0){
            headerLines.add(msg[i]);
            i++;
        }
        createHeaders(headerLines);
        frameBody=msg[msg.length-2];
    }
    private void createHeaders(List<String> headerLines){
        for (String h:headerLines) {
            headers.put(h.substring(0,h.indexOf(':')),h.substring(h.indexOf(':')+1));
        }
    }

    public String getCommand() {
        return command;
    }

    public String getFrameBody() {
        return frameBody;
    }

    public HashMap<String, String> getHeaders() {
        return headers;
    }
}
