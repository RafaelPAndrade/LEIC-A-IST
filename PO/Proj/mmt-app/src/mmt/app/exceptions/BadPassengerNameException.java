package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when an invalid passenger name is used. */
public class BadPassengerNameException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Passenger name. */
  private String _name;

  /**
   * @param name
   */
  public BadPassengerNameException(String name) {
    _name = name;
  }

  /** @see pt.tecnico.po.ui.DialogException#getMessage() */
  @Override
  public String getMessage() {
    return Message.invalidPassengerName(_name);
  }

}
