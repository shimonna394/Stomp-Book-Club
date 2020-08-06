package bgu.spl.net.srv;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

/**
 * This class holds all the information that we need about our users
 * @perm topics holds for each topic save the id for subscribe and unsubscribed
 */
public class User {
    private String userName;
    private int userId;
    private String userPassword;
    private boolean isActive;
    private HashMap<String,Integer> topics;
    public User(String userName,int Id, String Password){
        this.userName=userName;
        this.userId=Id;
        this.userPassword=Password;
        this.isActive=true;
        this.topics=new HashMap<String,Integer>();
    }
    public void connect(){
        this.isActive=true;
    }
    public void disconnect(){
        this.isActive=false;
    }
    public void removeTopic(int id,String topic){
        this.topics.remove(topic,id);
    }
    public void addTopic(int id,String topic){
        this.topics.put(topic,id);
    }

    public String getUserName() {
        return userName;
    }

    public int getUserId() {
        return userId;
    }

    public String getUserPassword() {
        return userPassword;
    }

    public HashMap<String,Integer> getTopics() {
        return topics;
    }

    public void setUserId(int userId) {
        this.userId = userId;
    }
    public boolean isActive(){
        return isActive;
    }
    public void deleteTopics(){
        topics.clear();
    }
    public String getTopic(int subId){
        Set<String> genre=topics.keySet();
        for (String s:genre) {
            if(topics.get(s)==subId)
                return s;
        }
        return "";
    }
}
