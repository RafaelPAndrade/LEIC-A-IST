package mmt.exceptions;

/** Exception thrown when the requested stored itinerary does not exist. */
public class NoSuchItineraryChoiceException extends Exception {

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
  public NoSuchItineraryChoiceException(int pid, int iid) {
    _passengerId = pid;
    _storedItineraryId = iid;
  }

  /** @return passenger id */
  public int getPassengerId() {
    return _passengerId;
  }

  /** @return itinerary id */
  public int getItineraryId() {
    return _storedItineraryId;
  }

}
