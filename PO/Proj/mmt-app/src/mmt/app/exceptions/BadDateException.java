package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when an invalid date is used. */
public class BadDateException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Bad date. */
  private String _date;

  /**
   * @param date
   */
  public BadDateException(String date) {
    _date = date;
  }

  /** @see pt.tecnico.po.ui.DialogException#getMessage() */
  @Override
  public String getMessage() {
    return Message.invalidDateSpecification(_date);
  }

}
