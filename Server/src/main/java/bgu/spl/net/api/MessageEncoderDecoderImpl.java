package bgu.spl.net.api;
import bgu.spl.net.Messages.Message;

import java.awt.*;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
public class MessageEncoderDecoderImpl implements MessageEncoderDecoder {

    private byte[] bytes = new byte[1 << 10]; //start with 1k
    private int len = 0;

/************************************************************Encoder****************************************************************/
    /**
     * encodes the given message to bytes array
     *
     * @param message the message to encode
     * @return the encoded bytes
     */
    @Override
    public byte[] encode(Object message) {
        Message msg=(Message) message;
        return (msg.getMsg()).getBytes();
    }

/*************************************************Decoder*******************************/
    /**
     * add the next byte to the decoding process
     *
     * @param nextByte the next byte to consider for the currently decoded
     *                 message
     * @return a message if this byte completes one or null if it doesnt.
     */
@Override
public String decode(byte nextByte) {
    if (nextByte == '\u0000') {
        return popString();
    }
    pushByte(nextByte);
    return null;
    }

    /**
     * adds the next byte of the message to the array
     * @param nextByte holds the next byte to be added
     */
    private void pushByte(byte nextByte) {
        if (len >= bytes.length) {
            bytes = Arrays.copyOf(bytes, len * 2);
        }
        bytes[len++] = nextByte;
    }

    /**
     * creates the message as a string
     * @return the string we created aka the message
     */
    private String popString() {
        String result = new String(bytes, 0, len);
        result=result+'\u0000';
        len = 0;
        return result;
    }
}