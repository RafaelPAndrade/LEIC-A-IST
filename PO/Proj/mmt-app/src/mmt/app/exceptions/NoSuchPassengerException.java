package mmt.app.exceptions;

import mmt.app.passenger.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when the requested passenger does not exist. */
public class NoSuchPassengerException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Passenger id. */
  private int _id;

  /**
   * @param id
   */
  public NoSuchPassengerException(int id) {
    _id = id;
  }

  /** @return message */
  @Override
  public String getMessage() {
    return Message.noSuchPassengerId(_id);
  }

}
