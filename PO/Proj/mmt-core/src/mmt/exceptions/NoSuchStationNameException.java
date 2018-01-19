package mmt.exceptions;

/** Exception thrown when the requested station does not exist. */
public class NoSuchStationNameException extends Exception {

  /** Serial number for serialization. */
  private static final long serialVersionUID = 201709021324L;

  /** Station name. */
  private String _name;

  /**
   * @param name
   */
  public NoSuchStationNameException(String name) {
    _name = name;
  }

  /** @return name */
  public String getName() {
    return _name;
  }

}
