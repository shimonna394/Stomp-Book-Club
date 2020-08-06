package bgu.spl.net.srv;

import bgu.spl.net.Messages.DisconnectMessageReceived;
import bgu.spl.net.Messages.ErrorMessage;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class ConnectionsImpl<T> implements Connections<T> {
    private ConcurrentHashMap<Integer,ConnectionHandler<T>> connectionHandlers = new ConcurrentHashMap<Integer, ConnectionHandler<T>>();//map for the connectionHandlers
    private  ConcurrentHashMap<String, LinkedBlockingQueue<User>> topics = new  ConcurrentHashMap<String, LinkedBlockingQueue<User>>();//map to know for each topic who are the subscribers who subscribed for it
    private  ConcurrentHashMap<String,User> usersByName = new  ConcurrentHashMap<String, User>();//map of all the users bt names include those who are non active
    private ConcurrentHashMap<Integer,User> activeUsersById = new  ConcurrentHashMap<Integer, User>();//map for the active users by id
    private ConcurrentHashMap<Integer,User> activeUsersByName = new  ConcurrentHashMap<Integer, User>();//map for the active users by bookName
    private AtomicInteger numOfUsers= new AtomicInteger(0);//num of users for giving id
    private AtomicInteger numOfReceipts=new AtomicInteger(0);//num of receipts for giving receipt id
    private AtomicInteger numOfMessages=new AtomicInteger(0);//num of messages for giving message id
    private static class SingletonHolder {//this class is singleton all the data in the server is here, and all the threads get the data from here
        private static ConnectionsImpl instance = new ConnectionsImpl();
    }
    public static ConnectionsImpl getInstance() {
        return ConnectionsImpl.SingletonHolder.instance;
    }
    /**
     * Sends a message T to client represented by the given connectionId
     *
     * @param connectionId
     * @param msg
     */
    @Override
    public boolean send(int connectionId, T msg) {
        ConnectionHandler connectionHandler=connectionHandlers.get(connectionId);
        if(connectionHandler!=null) {
            connectionHandler.send(msg);
            if(msg instanceof ErrorMessage)
                disconnect(connectionId);
            return true;
        }
        return false;
    }

    /**
     * Sends a message T to clients subscribed to channel
     *
     * @param channel
     * @param msg
     */
    @Override
    public void send(String channel, T msg) {
        if (topics.get(channel) != null) {//if there are subscribers for this topic
            for (User c : topics.get(channel)) {//send the msg to each subscriber
                connectionHandlers.get(c.getUserId()).send(msg);
            }
        }
    }

    /**
     * Removes an active client connectionId from the map
     *
     * @param connectionId
     */
    @Override
    public void disconnect(int connectionId) {
        this.connectionHandlers.remove(connectionId);
        if(activeUsersById.get(connectionId)!=null) {
            this.activeUsersById.get(connectionId).disconnect();//change the field isActive to false in the user
            this.activeUsersById.remove(connectionId);//remove from the active users map the element
        }
    }
    public ConcurrentHashMap<Integer, ConnectionHandler<T>> getConnectionHandlers() {
        return connectionHandlers;
    }

    public ConcurrentHashMap<String, LinkedBlockingQueue<User>> getTopics() {
        return topics;
    }

    public ConcurrentHashMap<Integer, User> getActiveUsersById() {
        return activeUsersById;
    }

    public ConcurrentHashMap<String, User> getUsersByName() {
        return usersByName;
    }
    public void addConnectionHandlers(ConnectionHandler connect,Integer id){
        connectionHandlers.put(id,connect);
    }
    public int getNumOfUsers(){
        return numOfUsers.intValue();
    }
    public int getNumOfReceipts(){
        return numOfReceipts.intValue();
    }
    public int getNumOfMessages(){
        return numOfMessages.getAndIncrement();
    }
    public void addReceipt(){
        numOfReceipts.getAndIncrement();
    }
    public void addMessages(){
        numOfMessages.getAndIncrement();
    }
    //methods for adding to the maps, should be used in the process in the protocol
    public void addTopics(String topic){
        topics.put(topic,new LinkedBlockingQueue<User>());
    }
    public void  addToTopic(String topic,User user,int id){
        if(topics.get(topic)==null)
            addTopics(topic);
        topics.get(topic).add(user);
        user.addTopic(id,topic);
    }
    public boolean removeTopic(String topic,User user,int id){
        if(topics.get(topic)!=null) {
            topics.get(topic).remove(user);
            user.removeTopic(id, topic);
            return true;
        }
        return false;
    }
    public void addUserByName(String bookName,User user){
        usersByName.put(bookName,user);
    }
    public void removeUserById(int id){
        activeUsersById.remove(id);
    }
    public void addActiveUsersById(int id,User user){
        activeUsersById.put(id,user);
    }
    public  Integer  incNumOfUsers(){
        return this.numOfUsers.getAndIncrement();
    }
    public void removeUserFromTopics(String topic,int id){
        LinkedBlockingQueue<User>users=topics.get(topic);
        for (User user:users) {
            if(user.getUserId()==id){
                users.remove(user);
                break;
            }
        }
    }
}
