package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when a passenger name is duplicated. */
public class DuplicatePassengerNameException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Passenger name. */
  private String _name;

  /**
   * @param name
   */
  public DuplicatePassengerNameException(String name) {
    _name = name;
  }

  /** @see pt.tecnico.po.ui.DialogException#getMessage() */
  @Override
  public String getMessage() {
    return Message.duplicatePassengerName(_name);
  }

}
