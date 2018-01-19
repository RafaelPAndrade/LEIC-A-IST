package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when the requested service does not exist. */
public class NoSuchServiceException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Service id. */
  private int _id;

  /**
   * @param id
   */
  public NoSuchServiceException(int id) {
    _id = id;
  }

  /** @return message */
  @Override
  public String getMessage() {
    return Message.noSuchServiceId(_id);
  }

}
