package mmt.exceptions;

/** Exception thrown when a passenger name is invalid. */
public class InvalidPassengerNameException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Passenger name. */
  private String _name;

  /**
   * @param name
   */
  public InvalidPassengerNameException(String name) {
    _name = name;
  }

  /** @return name */
  public String getName() {
    return _name;
  }

}
