package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when an invalid time is used. */
public class BadTimeException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Bad time. */
  private String _time;

  /**
   * @param time
   */
  public BadTimeException(String time) {
    _time = time;
  }

  /** @see pt.tecnico.po.ui.DialogException#getMessage() */
  @Override
  public String getMessage() {
    return Message.invalidTimeSpecification(_time);
  }

}
