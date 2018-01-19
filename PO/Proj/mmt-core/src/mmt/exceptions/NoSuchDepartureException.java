package mmt.exceptions;

/** Exception thrown when the requested departure does not exist. */
public class NoSuchDepartureException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Departure time. */
  private String _time;

  /**
   * @param time
   */
  public NoSuchDepartureException(String time) {
    _time = time;
  }

  /** @return time */
  public String getTime() {
    return _time;
  }

}
