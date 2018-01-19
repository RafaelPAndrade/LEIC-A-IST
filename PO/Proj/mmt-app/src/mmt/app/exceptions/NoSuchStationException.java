package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when the requested station does not exist. */
public class NoSuchStationException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Station name. */
  private String _name;

  /**
   * @param name
   */
  public NoSuchStationException(String name) {
    _name = name;
  }

  /** @see pt.tecnico.po.ui.DialogException#getMessage() */
  @Override
  public String getMessage() {
    return Message.noSuchStationName(_name);
  }

}
