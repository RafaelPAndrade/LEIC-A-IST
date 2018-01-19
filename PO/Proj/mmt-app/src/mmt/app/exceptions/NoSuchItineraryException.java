package mmt.app.exceptions;

import mmt.app.service.Message;
import pt.tecnico.po.ui.DialogException;

/** Exception thrown when the requested itinerary does not exist. */
public class NoSuchItineraryException extends DialogException {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Passenger id. */
  private int _passengerId;

  /** Stored itinerary id. */
  private int _storedItineraryId;

  /**
   * @param pid
   * @param iid
   */
  public NoSuchItineraryException(int pid, int iid) {
    _passengerId = pid;
    _storedItineraryId = iid;
  }

  /** @return message */
  @Override
  public String getMessage() {
    return Message.noSuchItineraryChoiceForPassanger(_passengerId, _storedItineraryId);
  }

}
